#include <boost/flyweight/flyweight_fwd.hpp>
#include <cctype>
#include <cstdint>
#include <ios>
#include <iostream>
#include <ostream>
#include <string_view>
#include <string>
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <vector>


using key = uint16_t;

class User {
protected:
    key first_name;
    key last_name;
    static boost::bimap<key, std::string> names;
    static key seed;
    static key add(std::string_view s) {
        auto it{ names.right.find(s.data()) };
        if (it == names.right.end()) {
            names.insert({++seed, s.data()});
            return seed;
        }
        return it->second;
    }

public:
    User(std::string_view first_name, std::string_view last_name) 
        : first_name{ add(first_name) }, last_name{ add(last_name) } {
    }

public:
    const std::string& get_first_name() const {
        return names.left.find(first_name)->second;
    }

    const std::string& get_last_name() const {
        return names.left.find(last_name)->second;
    }


public:
    friend std::ostream& operator<<(std::ostream& os, const User& obj) {
        return os << "first name: " << obj.get_first_name() << " last name: " << obj.get_last_name();
    }
};
boost::bimap<key, std::string> User::names{};
key User::seed{ 0 };


struct User2 {
    boost::flyweight<std::string> first_name;
    boost::flyweight<std::string> last_name;

    User2(std::string_view first_name, std::string_view last_name) 
        : first_name{ first_name }, last_name{ last_name } {
    }
};

int main1() {
    User2 john_doe{ "John", "Doe" };
    User2 jane_doe{ "Jane", "Doe" };
    std::cout << std::boolalpha << (&(john_doe.last_name.get()) == &(jane_doe.last_name.get())) << '\n';
    return 0;
}


class FormattedText {
    std::string plainText;
    bool *caps;

public:
    explicit FormattedText(std::string_view plainText) 
        : plainText{ plainText } {
        caps = new bool[plainText.length()]{ false };
    }

    ~FormattedText() {
        delete []  caps;
    }

    void capitalize(int start, int end) {
        for (int i{ start }; i <= end; ++i)
            caps[i] = true;
    }

    friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj) {
        std::string s;
        for (int i{ 0 }; i < obj.plainText.length(); ++i) {
            auto c{ obj.plainText[i] };
            s += (obj.caps[i] ? std::toupper(c) : c);
        }
        return os << s;
    }
};

int main2() {
    FormattedText ft{ "This is a brave new world" };
    ft.capitalize(10, 15);
    std::cout << ft << '\n';
    return 0;
}


struct BetterFormattedText {
    explicit BetterFormattedText(std::string_view plain_text) 
        : plain_text{ plain_text } {
    }

    struct TextRange {
        int start;
        int end;
        bool capitalize{ false };

        bool covers(int position) const {
            return position >= start && position <= end;
        }
    };

    TextRange& get_range(int start, int end) {
        formatting.emplace_back(TextRange{ start, end });
        return *formatting.rbegin();
    }

private:
    std::string plain_text;
    std::vector<TextRange> formatting;

public:
    friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj) {
        std::string s;
        for (int i{ 0 }; i < obj.plain_text.length(); ++i) {
            auto c{ obj.plain_text[i] };
            for (const auto& rng : obj.formatting) {
                if (rng.covers(i) && rng.capitalize)
                    c = std::toupper(c);
                s += c;
            }
        }
        return os << s;
    }
};

int main() {
    BetterFormattedText ft{ "This is a brave new world" };
    ft.get_range(10, 15).capitalize = true;
    std::cout << ft << '\n';
    return 0;
}
