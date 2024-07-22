#include <cstdio>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>


void htmlHelloWorld1() {
    std::string words[] = { "hello", "world" };
    std::ostringstream oss;
    oss << "<ul>";
    for (const auto& w : words)
        oss << " <li>" << w << "</li>";
    oss << "</ul>";
    printf("%s", oss.str().c_str());
}


struct HtmlElement {
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(std::string_view name, std::string_view text)
        : name{ name }, text{ text } {
    }

    std::string str(int indent = 0) const {
        // pretty-print the contents
        // (implpementation amitted)
    }
};


void htmlHelloWorld2() {
    std::string words[] = { "hello", "world" };
    HtmlElement list{ "ul", "" };
    for (const auto& w : words)
        list.elements.emplace_back("li", w);
    printf("%s", list.str().c_str());
}


struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder(std::string_view root_name) {
        root.name = root_name;
    }

    void add_child(std::string_view child_name, std::string_view child_text) {
        root.elements.emplace_back(child_name, child_text);
    }

    std::string str() { return root.str(); }
};


void htmlHelloWorld3() {
    HtmlBuilder builder{ "url" };
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    printf("%s", builder.str().c_str());
}


struct HtmlBuilder1 {
    HtmlElement root;

    HtmlBuilder1(std::string_view root_name) {
        root.name = root_name;
    }

    HtmlBuilder1& add_child(std::string_view child_name, std::string_view child_text) {
        root.elements.emplace_back(child_name, child_text);
        return *this;
    }

    // HtmlBuilder1* add_child(std::string_view child_name, std::string_view child_text) {
    //     root.elements.emplace_back(child_name, child_text);
    //     return this;
    // }

    std::string str() { return root.str(); }
};


void htmlHelloWorld4() {
    HtmlBuilder1 builder{ "url" };
    builder.add_child("li", "hello").add_child("li", "world");
    printf("%s", builder.str().c_str());
}

struct HtmlBuilder2;
struct HtmlElement1 {
    friend struct HtmlBuilder2;

    std::string name;
    std::string text;
    std::vector<HtmlElement1> elements;
    const size_t indent_size{ 2 };

public:
    static std::unique_ptr<HtmlBuilder2> create(std::string_view root_name);

public:
    std::string str(int indent = 0) const {
        // pretty-print the contents
        // (implpementation amitted)
    }

protected:
    HtmlElement1() {}
    HtmlElement1(std::string_view name, std::string_view text)
        : name{ name }, text{ text } {
    }
};


struct HtmlBuilder2 {
    HtmlElement1 root;

    HtmlBuilder2(std::string_view root_name) {
        root.name = root_name;
    }

    HtmlBuilder2* add_child(std::string_view child_name, std::string_view child_text) {
        root.elements.emplace_back(HtmlElement1{ child_name, child_text });
        return this;
    }

    std::string str() { return root.str(); }
};

std::unique_ptr<HtmlBuilder2> HtmlElement1::create(std::string_view root_name) {
    return std::make_unique<HtmlBuilder2>(root_name);
}

void htmlHelloWorld5() {
    auto builder = HtmlElement1::create("ul");
    builder->add_child("li", "hello")->add_child("li", "world");
    printf("%s", builder->str().c_str());
}


struct HtmlBuilder3;
struct HtmlElement2 {
    friend struct HtmlBuilder3;

    std::string name;
    std::string text;
    std::vector<HtmlElement2> elements;
    const size_t indent_size{ 2 };

public:
    static HtmlBuilder3& build(std::string_view root_name);

public:
    std::string str(int indent = 0) const {
        // pretty-print the contents
        // (implpementation amitted)
    }


protected:
    HtmlElement2() {}
    HtmlElement2(std::string_view name, std::string_view text)
        : name{ name }, text{ text } {
    }
};

struct HtmlBuilder3 {
    HtmlElement2 root;

    HtmlBuilder3(std::string_view root_name) {
        root.name = root_name;
    }

    HtmlBuilder3& add_child(std::string_view child_name, std::string_view child_text) {
        root.elements.emplace_back(HtmlElement2{ child_name, child_text });
        return *this;
    }

    operator HtmlElement2() const {
        return root;
    }

    std::string str() { return root.str(); }
};

HtmlBuilder3& HtmlElement2::build(std::string_view root_name) {
    static HtmlBuilder3 builder{ root_name };
    return builder;
}


void htmlHelloWorld6() {
    HtmlElement2 e = HtmlElement2::build("ul").add_child("li", "hello").add_child("li", "world");
    printf("%s", e.str().c_str());
}