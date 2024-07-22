#pragma once
#include <cstddef>
#include <iterator>
#include <stdexcept>

template<typename T>
class ConstIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = const value_type*;
    using reference = const value_type&;

    ConstIterator() = default;

    ConstIterator(pointer p) : m_ptr{p} {}

    ConstIterator& operator++() noexcept {
        ++m_ptr;
        return *this;
    }

    ConstIterator operator++(int) noexcept {
        ConstIterator temp{*this};
        ++(*this);
        return temp;
    }

    reference operator*() const noexcept {return *m_ptr;}
    pointer operator->() const noexcept {return m_ptr;}

    auto operator<=>(const ConstIterator& other) const = default;

    ConstIterator& operator--() noexcept {
        --m_ptr;
        return *this;
    }

    ConstIterator operator--(int) noexcept {
        ConstIterator temp{*this};
        --(*this);
        return temp;
    }

private:
    pointer m_ptr{nullptr};
};


template<typename T>
class Iterator : public ConstIterator<T> {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

    using ConstIterator<T>::ConstIterator;

    Iterator& operator++() noexcept {
        ConstIterator<T>::operator++();
        return *this;
    }

    Iterator operator++(int) noexcept {
        Iterator temp{*this};
        ConstIterator<T>::operator++();
        return temp;
    }

    reference operator*() const noexcept {
        return const_cast<reference>(ConstIterator<T>::operator*());
    }

    pointer operator->() const noexcept {
        return const_cast<pointer>(ConstIterator<T>::operator->());
    }

    Iterator& operator--() noexcept {
        ConstIterator<T>::operator--();
        return *this;
    }

    Iterator operator--(int) noexcept {
        ConstIterator temp{*this};
        ConstIterator<T>::operator--();
        return temp;
    }
};


template <typename T, size_t SIZE>
struct MyArray {
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr size_type size() const noexcept {return SIZE;}

    iterator begin() {return iterator{&m_data[0]};}
    iterator end() {return iterator{&m_data[0] + size()};}
    const_iterator begin() const {return const_iterator{&m_data[0]};}
    const_iterator end() const {return const_iterator{&m_data[0] + size()};}

    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}

    reverse_iterator rbegin() {return reverse_iterator{end()};}
    reverse_iterator rend() {return reverse_iterator{begin()};}
    const_reverse_iterator rbegin() const {return const_reverse_iterator{end()};}
    const_reverse_iterator rend() const {return const_reverse_iterator{begin()};}

    const_reverse_iterator crbegin() const {return rbegin();}
    const_reverse_iterator crend() const {return rend();}

    auto operator<=>(const MyArray& t) const noexcept = default;

    T& operator[](size_type index) {
        if (index >= size()) {
            throw std::out_of_range{"Index out of range"};
        }

        return m_data[index];
    }

    const T& operator[](size_type index) const {
        if (index >= size()) {
            throw std::out_of_range{"Index out of range"};
        }

        return m_data[index];
    }

    T m_data[SIZE];
};

// 推到指引
template<typename T, std::same_as<T>... Us>
MyArray(T first, Us... rest) -> MyArray<T, 1 + sizeof...(Us)>;