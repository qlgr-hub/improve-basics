#include <cstddef>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <boost/container_hash/hash.hpp>


struct Point {
    int x;
    int y;

    Point(int x, int y) : x{ x }, y{ y } {
    }

    friend size_t hash_value(const Point& obj) {
        size_t seed{ 0x725C686F };
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        return seed;
    }
};


struct Line {
    Point start;
    Point end;

    Line(const Point& start, const Point& end) 
        : start{ start }, end{ end } {
    }

    friend size_t hash_value(const Line& obj) {
        size_t seed{ 0x719E6B16 };
        boost::hash_combine(seed, obj.start);
        boost::hash_combine(seed, obj.end);
        return seed;
    }
};


struct VectorObject {
    virtual std::vector<Line>::iterator begin() = 0;
    virtual std::vector<Line>::iterator end() = 0;
};


class VectorRectangle : public VectorObject {
    std::vector<Line> lines;

public:
    VectorRectangle(int x, int y, int width, int height) {
        lines.emplace_back(Line{ Point{x, y}, Point{x + width, y} });
        lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y + height} });
        lines.emplace_back(Line{ Point{x, y}, Point{x + width, y + height} });
        lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y = height} });
    }

    std::vector<Line>::iterator begin() override {
        return lines.begin();
    }

    std::vector<Line>::iterator end() override {
        return lines.end();
    }
};


// std::vector<Line>::iterator and std::vector<Point>::iterator Mismatch
// void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
//     for (auto i = start; i != end; ++i) {
//         dc.SetPixel(i->x, i->y, 0);
//     }
// }
// A stand-in for MFC CPaintDC.
struct CPaintDC {
    void SetPixel(int x, int y, int z) {
    }
};

void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end) {
    for (auto i = start; i != end; ++i) {
        dc.SetPixel(i->x, i->y, 0);
    }
}




std::vector<std::shared_ptr<VectorObject>> vectorObjects {
    std::make_shared<VectorRectangle>(10, 10, 100, 100),
    std::make_shared<VectorRectangle>(30, 30, 60, 60)
};


class LineToPointAdapter {
    using Points = std::vector<Point>;

    Points points;

public:
    LineToPointAdapter(const Line& line) {
        int left{ std::min(line.start.x, line.end.x) };
        int right{ std::max(line.start.x, line.end.x) };
        int top{ std::min(line.start.y, line.end.y) };
        int bottom{ std::max(line.start.y, line.end.y) };

        int dx = right - left;
        int dy = line.end.y - line.start.y;

        if (dx == 0) {
            for (int y{ top }; y <= bottom; ++y) {
                points.emplace_back(Point{ left, y });
            }
        }
        else if (dy == 0) {
            for (int x{ left }; x < right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }
    }

    virtual Points::iterator begin() { return points.begin(); }
    virtual Points::iterator end() { return points.end(); }
};


int main1() {
    for (const auto& obj : vectorObjects) {
        for (const auto& line : *obj) {
            LineToPointAdapter lpo{ line };

            CPaintDC dc;
            DrawPoints(dc, lpo.begin(), lpo.end());
        }
    }

    return 0;
}


int main2() {
    std::vector<Point> points;

    for (const auto& o : vectorObjects) {
        for (const auto& l : *o) {
            LineToPointAdapter lpo{ l };
            for (const auto& p : lpo) {
                points.push_back(p);
            }
        }
    }

    CPaintDC dc;
    DrawPoints(dc, points.begin(), points.end());

    return 0;
}



class LineToPointCachingAdapter {
    using Points = std::vector<Point>;

    static std::map<size_t, Points> cache;
    size_t line_hash;

public:
    LineToPointCachingAdapter(const Line& line) {
        static boost::hash<Line> hash;
        line_hash = hash(line);
        if (cache.find(line_hash) != cache.end())
            return;

        int left{ std::min(line.start.x, line.end.x) };
        int right{ std::max(line.start.x, line.end.x) };
        int top{ std::min(line.start.y, line.end.y) };
        int bottom{ std::max(line.start.y, line.end.y) };

        int dx = right - left;
        int dy = line.end.y - line.start.y;

        Points points;
        if (dx == 0) {
            for (int y{ top }; y <= bottom; ++y) {
                points.emplace_back(Point{ left, y });
            }
        }
        else if (dy == 0) {
            for (int x{ left }; x < right; ++x) {
                points.emplace_back(Point{ x, top });
            }
        }
        cache[line_hash] = points;
    }

    virtual Points::iterator begin() { return cache[line_hash].begin(); }
    virtual Points::iterator end() { return cache[line_hash].end(); }
};
std::map<size_t, LineToPointCachingAdapter::Points> LineToPointCachingAdapter::cache;



template <typename TFrom, typename TTo>
struct Converter {
    virtual TTo Convert(const TFrom& from) = 0;
    virtual TFrom ConvertBack(const TTo& to) = 0;
};


struct IntToStringConverter : Converter<int, std::string> {
    std::string Convert(const int& from) override {
        return std::to_string(from);
    }

    int ConvertBack(const std::string& to) override {
        int result;
        try {
            result = std::stoi(to);
        }
        catch (...) {
            return std::numeric_limits<int>::min();
        }

        return result;
    }
};
