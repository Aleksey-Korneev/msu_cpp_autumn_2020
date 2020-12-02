#pragma once
#include <cstddef>
#include <iterator>

template<
    class T,
    class V_Allocator = Allocator<T>
>
class Vector
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using rvalue_reference = T&&;

    V_Allocator alloc;
    size_type size_;
    size_type capacity_;
    pointer data_;

    void realloc();
public:
    using allocator_type = V_Allocator;
    using iterator = Iterator<T>;
    using const_iterator = Iterator<const T>;
    //Constructors
    explicit Vector() noexcept;
    explicit Vector(size_type);
    Vector(size_type, const_reference);
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(iterator, iterator);
    Vector(std::initializer_list<T>);
    ~Vector() noexcept;
    //Operators and access to elements
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);
    bool operator==(const Vector& other);
    bool operator!=(const Vector& other);
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    reference at(size_type);
    const_reference at(size_type) const;
    //Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type);
    void shrink_to_fit();
    //Modifiers
    void resize(size_type, const_reference = T());
    void clear() noexcept;
    void push_back(const_reference);
    void push_back(rvalue_reference);
    void pop_back();
    template<class... Args>
    void emplace_back(Args&&...);
    //Iterators
    iterator begin() noexcept;
    iterator end() noexcept;
    iterator rbegin() noexcept;
    iterator rend() noexcept;
};

#include "impl/vector.tpp"