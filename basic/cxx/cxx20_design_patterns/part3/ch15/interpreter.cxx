#include <cctype>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <boost/lexical_cast.hpp>



int better_atoi(const char* str) {
    int val{ 0 };
    while (*str) {
        val = val * 10 + (*str++ - '0');
    }
    return val;
}



struct Token {
    enum Type { integer, plus, minus, lparen, rparen } type;
    std::string text;

    explicit Token(Type type, std::string_view text) 
        : type{ type }, text{ text } {
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
        return os << '`' << obj.text << '`';
    }
};


std::vector<Token> lex(std::string_view input) {
    std::vector<Token> res;

    for (int i{ 0 }; i < input.size(); ++i) {
        switch (input[i]) {
        case '+':
            res.emplace_back(Token::plus, "+");
            break;
        case '-':
            res.emplace_back(Token::minus, "-");
            break;
        case '(':
            res.emplace_back(Token::lparen, "(");
            break;
        case ')':
            res.emplace_back(Token::rparen, ")");
            break;
        default:
            {
                std::ostringstream buffer;
                buffer << input[i];
                for (int j{ i + 1 }; j < input.size(); ++j) {
                    if (std::isdigit(input[j])) {
                        buffer << input[j];
                        ++i;
                    }
                    else {
                        res.emplace_back(Token::integer, buffer.str());
                        buffer.str("");
                        break;
                    }
                }

                if (auto str{ buffer.str() }; str.length() > 0) {
                    res.emplace_back(Token::integer, str);
                }
            }
        }
    }

    return res;
}


struct Element {
    virtual int eval() const = 0;
};

struct Integer final : Element {
    int value;

    explicit Integer(int value) 
        : value{ value } {
    }

    int eval() const override {
        return value;
    }
};

struct BinaryOperation final : Element {
    enum Type { addition, subtraction } type;
    std::shared_ptr<Element> lhs;
    std::shared_ptr<Element> rhs;

    int eval() const override {
        if (type == addition)
            return lhs->eval() + rhs->eval();
        return lhs->eval() - rhs->eval();
    }
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens) {
    auto res{ std::make_unique<BinaryOperation>() };

    bool have_lhs{ false };
    for (size_t i{ 0 }; i < tokens.size(); ++i) {
        auto& token{ tokens[i] };

        switch (token.type) {
        case Token::integer:
            {
                auto value{ boost::lexical_cast<int>(token.text) };
                auto integer_element{ std::make_shared<Integer>(value) };
                if (!have_lhs) {
                    res->lhs = integer_element;
                    have_lhs = true;
                }
                else {
                    res->rhs = integer_element;
                }
            }
            break;

        case Token::plus:
            res->type = BinaryOperation::addition;
            break;

        case Token::minus:
            res->type = BinaryOperation::subtraction;
            break;

        case Token::lparen:
            {
                auto j{ i };
                for ( ; j < tokens.size(); ++j)
                    if (tokens[j].type == Token::rparen)
                        break;

                std::vector<Token> subexpression{ &tokens[i + 1], &tokens[j] };
                auto element{ parse(subexpression) };
                if (!have_lhs) {
                    res->lhs = element;
                    have_lhs = true;
                }
                else {
                    res->rhs = element;
                    i = j; // advence
                }
            }
            break;

        default: break;
        }
    }

    return res;
}


int main1() {
    std::string input{ "(13-4)-(12+1)" };
    auto tokens{ lex(input) };
    auto parsed{ parse(tokens) };
    std::cout << input << " = " << parsed->eval() << '\n';
    return 0;
}


//////////////////////////// code ref: https://github.com/nesteruk/tlon /////////////////////////////////////////
