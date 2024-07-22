#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>


struct Tag {
    std::string name;
    std::string text;

    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& obj) {
        // return os << ...
        return os;
    }

protected:
    Tag(std::string_view name, std::string_view text)
        : name{ name }, text{ text } {
    }

    Tag(std::string_view name, std::initializer_list<Tag>& children)
        : name { name }, children{ children } {
    }
};


struct P : public Tag {
    explicit P(std::string_view text)
        : Tag{ "P", text } {
    }

    P(std::initializer_list<Tag> children)
        : Tag{ "P", children } {
    }
};


struct IMG : public Tag {
    explicit IMG(std::string_view url)
        : Tag{ "img", url } {
    }
};


int main() {
    // Builder implemented by inheritance + constructor
    std::cout << P{ IMG{ "http://pokemon.com/pikachu.png" } } << '\n';
    return 0;
}