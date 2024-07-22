#include "MyArray.h"
#include <array>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <algorithm>
#include <span>
#include <sstream>
#include <stdexcept>
#include <utility>


std::istream& operator>>(std::istream& in, MyArray& a) {
    std::span<int> items{a.m_ptr.get(), a.size()};
    for (auto& item : items) {
        in >> item;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const MyArray& a) {
    out << a.toString();
    return out;
}

void swap(MyArray& a, MyArray& b) noexcept {
    std::swap(a.m_size, b.m_size);
    a.m_ptr.swap(b.m_ptr);
}

MyArray::MyArray(size_t size) : m_size{size}
    , m_ptr{std::make_unique<int[]>(size)} {
    std::cout << "MyArray(size_t) constructor\n";
}

MyArray::MyArray(std::initializer_list<int> list)
    : m_size{list.size()}, m_ptr{std::make_unique<int[]>(list.size())} {
    std::cout << "MyArray(initializer_list) constructor\n";

    std::copy(std::begin(list), std::end(list), m_ptr.get());
}

MyArray::MyArray(const MyArray& original)
    : m_size{original.size()}
    , m_ptr{std::make_unique<int[]>(original.size())} {
    std::cout << "MyArray copy constructor\n";

    const std::span<const int> source {
        original.m_ptr.get(), original.size()};
    std::copy(std::begin(source), std::end(source), m_ptr.get());
}

MyArray& MyArray::operator=(const MyArray& right) {
    std::cout << "MyArray copy assignment operator\n";
    MyArray temp{right};
    swap(*this, temp);
    return *this;
}

MyArray::MyArray(MyArray&& original) noexcept
    : m_size{std::exchange(original.m_size, 0)}
    , m_ptr{std::move(original.m_ptr)} {
    std::cout << "MyArray move constructor\n";
}

MyArray& MyArray::operator=(MyArray&& right) noexcept {
    std::cout << "MyArray move assignment operator\n";

    if (this != &right) {
        m_size = std::exchange(right.m_size, 0);
        m_ptr = std::move(right.m_ptr);
    }

    return *this;
}

MyArray::~MyArray() {
    std::cout << "MyArray destructor\n";
}

std::string MyArray::toString() const {
    const std::span<const int> items{m_ptr.get(), size()};
    std::ostringstream out;
    out << "{";

    for (size_t count{0}; const auto& item : items) {
        ++count;
        out << item << (count < size() ? ", " : "");
    }
    out << "}";
    return out.str();
}

bool MyArray::operator==(const MyArray& right) const noexcept {
    const std::span<const int> lhs{m_ptr.get(), size()};
    const std::span<const int> rhs{right.m_ptr.get(), size()};
    return std::equal(std::begin(lhs), std::end(lhs),
        std::begin(rhs), std::end(rhs));
}

int& MyArray::operator[](size_t index) {
    if (index >= size()) {
        throw std::out_of_range{"Index out of range"};
    }

    return m_ptr[index];
}

const int& MyArray::operator[](size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range{"Index out of range"};
    }

    return m_ptr[index];
}

MyArray& MyArray::operator++() {
    const std::span<int> items{m_ptr.get(), size()};
    std::for_each(std::begin(items), std::end(items),
        [](auto& item){++item;});
    return *this;
}

MyArray MyArray::operator++(int) {
    MyArray temp{*this};
    ++(*this);
    return temp;
}

MyArray& MyArray::operator+=(int value) {
    const std::span<int> items{m_ptr.get(), size()};
    std::for_each(std::begin(items), std::end(items),
        [value](auto& item){item += value;});
    return *this;
}