#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string_view>
#include <vector>



int main1() {
    std::vector<int> values{ 3, 1, 5, 2, 4 };
    std::sort(values.begin(), values.end(), std::less<>{});
    for (int x : values)
        std::cout << x << ' ';
    std::cout << '\n';

    std::sort(values.begin(), values.end(), [=](int a, int b) {
        return a > b;
    });
    for (int x : values)
        std::cout << x << ' ';
    std::cout << '\n';

    return 0;
}


enum class OutputFormat {
    markdown,
    html
};

struct ListStrategy {
    virtual ~ListStrategy() = default;
    virtual void start(std::ostringstream& oss) {}
    virtual void add_list_item(std::ostringstream& oss, std::string_view item) {}
    virtual void end(std::ostringstream& oss) {}
};

struct HtmlListStrategy final : ListStrategy {
    void start(std::ostringstream& oss) override {
        oss << "<ul>\n";
    }

    void add_list_item(std::ostringstream& oss, std::string_view item) override {
        oss << "\t<li>" << item.data() << "</li>\n";
    }

    void end(std::ostringstream& oss) override {
        oss << "</ul>\n";
    }
};

struct MarkdownListStrategy final : ListStrategy {
    void add_list_item(std::ostringstream& oss, std::string_view item) override {
        oss << " * " << item.data() << '\n';
    }
};


class TextProcesser {
    std::ostringstream oss;
    std::unique_ptr<ListStrategy> list_strategy;

public:
    TextProcesser(OutputFormat ofmt) : list_strategy{ nullptr } {
        switch (ofmt) {
        case OutputFormat::markdown: list_strategy = std::make_unique<MarkdownListStrategy>(); break;
        case OutputFormat::html: list_strategy = std::make_unique<HtmlListStrategy>(); break;
        default: break;
        }
    }

public:
    void set_output_format(OutputFormat ofmt) {
        switch (ofmt) {
        case OutputFormat::markdown: list_strategy = std::make_unique<MarkdownListStrategy>(); break;
        case OutputFormat::html: list_strategy = std::make_unique<HtmlListStrategy>(); break;
        default: break;
        }
    }

    void append_list(const std::vector<std::string>& items) {
        list_strategy->start(oss);
        for (auto& item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }

    void clear() {
        oss.str("");
        // oss.clear() // This is to clear error flags rather than clear content
    }

    std::string str() const {
        return oss.str();
    }
};


int main2() {
    TextProcesser tp{ OutputFormat::markdown };
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << '\n';

    tp.clear();
    tp.set_output_format(OutputFormat::html);
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << '\n';
    return 0;
}


template <typename LS>
class TextProcesser1 {
    std::ostringstream oss;
    LS list_strategy;

public:
    void append_list(const std::vector<std::string>& items) {
        list_strategy.start(oss);
        for (auto& item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }

    void clear() {
        oss.str("");
        // oss.clear() // This is to clear error flags rather than clear content
    }

    std::string str() const {
        return oss.str();
    }
};

int main() {
    TextProcesser1<MarkdownListStrategy> tpm{};
    tpm.append_list({ "foo", "bar", "baz" });
    std::cout << tpm.str() << '\n';

    TextProcesser1<HtmlListStrategy> tph{};
    tph.append_list({ "foo", "bar", "baz" });
    std::cout << tph.str() << '\n';
    return 0;
}