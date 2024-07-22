#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <optional>
#include <set>
#include <string>
#include <vector>



struct Generator {
    virtual std::vector<int> generate(int count) const {
        std::vector<int> res(count);
        
        std::generate(res.begin(), res.end(), [&]() {
            return 1 + rand() % 9;
        });

        return res;
    }
};


struct Splitter {
    std::vector<std::vector<int>> split(const std::vector<std::vector<int>>& array) const {
        auto rowCount{ array.size() };
        auto colCount{ array[0].size() };
        std::vector<std::vector<int>> result{};

        // get the rows
        for (auto r{ 0 }; r < rowCount; ++r) {
            auto theRow{ std::vector<int>{} };

            for (auto c{ 0 }; c < colCount; ++c)  {
                theRow.push_back(array[r][c]);
            }

            result.emplace_back(theRow);
        }

        // get the columns
        for (auto c{ 0 }; c < colCount; ++c) {
            auto theCol{ std::vector<int>{} };

            for (auto r{ 0 }; r < rowCount; ++r)  {
                theCol.push_back(array[r][c]);
            }

            result.emplace_back(theCol);
        }

        // get the diagonals
        auto diag1{ std::vector<int>{} };
        auto diag2{ std::vector<int>{} };
        for (auto c{ 0 }; c < colCount; ++c) {
            for (auto r{ 0 }; r < rowCount; ++r)  {
                if (r == c)
                    diag1.push_back(array[r][c]);

                auto r2 { rowCount - r - 1 };
                if (r2 == c)
                    diag2.push_back(array[r][c]);
            }
        }
        result.emplace_back(diag1);
        result.emplace_back(diag2);

        return result;
    }
};


struct Verifier {
    bool verify(const std::vector<std::vector<int>>& array) const {
        if (array.empty())
            return false;

        auto expected{ std::accumulate(array[0].begin(), array[0].end(), 0) };

        return std::all_of(array.begin(), array.end(), [=](auto& inner) {
            return std::accumulate(inner.begin(), inner.end(), 0) == expected;
        });
    }
};


template <typename G = Generator, typename S = Splitter, typename V = Verifier>
struct MagicSquareGenerator {
    std::vector<std::vector<int>> generate(int size) {
        G g;
        S s;
        V v;

        std::vector<std::vector<int>> square;

        do {
            square.clear();
            for (int i{ 0 }; i < size; ++i)
                square.emplace_back(g.generate(size));
        } while (!v.verify(s.split(square)));

        return square;
    }
};


struct UniqueGenerator : Generator {
    std::vector<int> generate(int count) const override {
        std::vector<int> res;

        do {
            res = Generator::generate(count);
        } while (std::set<int>(res.begin(), res.end()).size() != res.size());

        return res;
    }
};


int main1() {
    // MagicSquareGenerator gen;
    MagicSquareGenerator<UniqueGenerator> gen;
    auto square{ gen.generate(3) };
    for (const auto& r : square) {
        for (auto v : r) {
            std::cout << v << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}




//////////////////////////////////////////////////////////////////////////////////////////
struct Size {
    int x;
    int y;
};

struct Buffer{};
struct TableBuffer : Buffer {
    struct TableColumnSpec;
    
    TableBuffer(const std::vector<TableColumnSpec>& spec, int totalHight) {
        /* ... */
    }
    
    /* ... */

    struct TableColumnSpec {
        std::string header;
        int width;
        enum class TableColumnAlignment {
             Left, Center, Right 
        } alignment;
    };
};

struct ConsoleCreationParameters {
    std::optional<Size> client_size;
    int character_width{ 10 };
    int character_height{ 14 };
    int width{ 20 };
    int height{ 30 };
    bool fullscreen{ false };
    bool create_default_view_and_buffer{ true };
};

struct Viewport;
struct Console {
    std::vector<Viewport*> viewports;
    Size charSize;
    Size gridSize;
    /* ... */


    // Console(bool fullscreen, int char_width, int char_height, int width, int height, std::optional<Size> client_size) {
    //     // single buffer and viewport created here
    //     // linked togather and added to appropriate collections
    //     // image textures generated
    //     // grid size calculated depending on whether we want fullscreen mode
    // }

    Console(const ConsoleCreationParameters& ccp) {
        /* ... */
    }
};