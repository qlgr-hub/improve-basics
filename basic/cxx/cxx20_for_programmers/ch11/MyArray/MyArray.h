#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <istream>
#include <memory>

class MyArray final {
    friend std::istream& operator>>(std::istream& in, MyArray& a);
    friend std::ostream& operator<<(std::ostream& out, const MyArray& a);
    friend void swap(MyArray& a, MyArray& b) noexcept;

public:
    explicit MyArray(size_t size);
    explicit MyArray(std::initializer_list<int> list);

    MyArray(const MyArray& original);
    MyArray& operator=(const MyArray& right);

    MyArray(MyArray&& original) noexcept;
    MyArray& operator=(MyArray&& right) noexcept;

    ~MyArray();

    size_t size() const noexcept {return m_size;}
    std::string toString() const;

    bool operator==(const MyArray& right) const noexcept;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    explicit operator bool() const noexcept {return size() != 0;}

    MyArray& operator++();
    MyArray operator++(int);

    MyArray& operator+=(int value);

private:
    size_t m_size;
    std::unique_ptr<int[]> m_ptr;
};

std::istream& operator>>(std::istream& in, MyArray& a);
std::ostream& operator<<(std::ostream& out, const MyArray& a);

void swap(MyArray& a, MyArray& b) noexcept;
