#pragma once
#include <iterator>

template<class T>
class Iterator
{
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;

    pointer p;
    bool is_reverse;
public:
    Iterator(pointer, bool = false);
    
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    Iterator<T>& operator--();
    Iterator<T> operator--(int);

    reference operator[](size_t);
    const_reference operator[](size_t) const;

    bool operator==(const Iterator&) const noexcept;
    bool operator!=(const Iterator&) const noexcept;

    reference operator*();
    const_reference operator*() const;

    Iterator<T>& operator+=(difference_type);
    Iterator<T>& operator-=(difference_type);
    Iterator<T> operator+(difference_type) const;
    Iterator<T> operator-(difference_type) const;
    difference_type operator-(const Iterator&) const;
    template<class U>
    friend Iterator<U> operator+(difference_type, const Iterator<U>&);
    template<class U>
    friend Iterator<U> operator-(difference_type, const Iterator<U>&);

    bool operator<(const Iterator& other) const noexcept;
    bool operator>(const Iterator& other) const noexcept;
    bool operator<=(const Iterator& other) const noexcept;
    bool operator>=(const Iterator& other) const noexcept;
};

#include "impl/iterator.tpp"