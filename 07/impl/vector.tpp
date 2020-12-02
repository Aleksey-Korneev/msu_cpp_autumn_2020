#include <algorithm>
#include <exception>

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::realloc()
{
    size_type new_capacity_ = capacity_ ? 2 * capacity_ : 1;
    pointer new_data_ = alloc.allocate(new_capacity_);
    capacity_ = new_capacity_;
    std::move(this->begin(), this->end(), new_data_);
    delete [] data_;
    data_ = new_data_;
}
// Constructors
// 1 Vector()
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector() noexcept
        : size_(0), capacity_(0), data_(nullptr)
{
}
// 2 Vector(size_t v_size)
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(
        typename Vector<T, V_Allocator>::size_type v_size)
        : size_(v_size), capacity_(v_size),
        data_(alloc.allocate(size_))
{
    const_reference val{};
    std::fill(this->begin(), this->end(), val);
}
// 3 Vector(size_t v_size, const T& val)
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(
        typename Vector<T, V_Allocator>::size_type v_size,
        typename Vector<T, V_Allocator>::const_reference val)
        : size_(v_size), capacity_(v_size),
        data_(alloc.allocate(size_))
{
    std::fill(this->begin(), this->end(), val);
}
// 4 Vector(const Vector& other)
// Для корректной работы требуется доопределить iterator_traits (?)
namespace std {
    template<class T>
    struct iterator_traits<Iterator<T>> {
        using value_type = T;
        using iterator_category = random_access_iterator_tag;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
    };
}

template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(const Vector<T, V_Allocator>& other)
        : size_(other.size_), capacity_(other.capacity_),
        data_(alloc.allocate(size_))
{
    for (size_type i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}
// 5 Vector(Vector&& other)
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(Vector<T, V_Allocator>&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_),
        data_(std::move(other.data_))
{
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}
// 6 Vector(iterator begin, iterator end)
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(
        typename Vector<T, V_Allocator>::iterator begin,
        typename Vector<T, V_Allocator>::iterator end)
        : size_(end - begin), capacity_(size_),
        data_(alloc.allocate(size_))
{
    std::copy(begin, end, this->begin());
}
// 7 Vector(std::initializer_list<T> init_list)
template<class T, class V_Allocator>
Vector<T, V_Allocator>::Vector(std::initializer_list<T> init_list)
        : size_(init_list.size()), capacity_(init_list.size()),
        data_(alloc.allocate(size_))
{
    std::copy(init_list.begin(), init_list.end(), this->begin());
}
// Destructor
template<class T, class V_Allocator>
Vector<T, V_Allocator>::~Vector() noexcept
{
    alloc.deallocate(data_);
}
//Operators and access to elements
template<class T, class V_Allocator>
Vector<T, V_Allocator>&
Vector<T, V_Allocator>::operator=(const Vector<T, V_Allocator>& other)
{
    if (this == &other) {
        return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    alloc.deallocate(data_);
    data_ = alloc.allocate(size_);
    for (size_type i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

template<class T, class V_Allocator>
Vector<T, V_Allocator>&
Vector<T, V_Allocator>::operator=(Vector<T, V_Allocator>&& other)
{
    if (this == &other) {
        return *this;
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    alloc.deallocate(data_);
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
    return *this;
}

template<class T, class V_Allocator>
bool Vector<T, V_Allocator>::operator==(const Vector<T, V_Allocator>& other)
{
    if (size_ != other.size_) {
        return false;
    }
    for (size_type i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

template<class T, class V_Allocator>
bool Vector<T, V_Allocator>::operator!=(const Vector<T, V_Allocator>& other)
{
    if (size_ != other.size_) {
        return true;
    }
    for (size_type i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return true;
        }
    }
    return false;
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::reference
Vector<T, V_Allocator>::operator[](typename Vector<T, V_Allocator>::size_type i)
{
    return data_[i];
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::const_reference
Vector<T, V_Allocator>::operator[](typename Vector<T, V_Allocator>::size_type i) const
{
    return data_[i];
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::reference
Vector<T, V_Allocator>::at(typename Vector<T, V_Allocator>::size_type i)
{
    if (i >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[i];
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::const_reference
Vector<T, V_Allocator>::at(typename Vector<T, V_Allocator>::size_type i) const
{
    if (i >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return data_[i];
}

// Capacity
template<class T, class V_Allocator>
bool Vector<T, V_Allocator>::empty() const noexcept
{
    return this->size_ == 0;
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::size_type
Vector<T, V_Allocator>::size() const noexcept
{
    return this->size_;
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::size_type
Vector<T, V_Allocator>::capacity() const noexcept
{
    return this->capacity_;
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::reserve(typename Vector<T, V_Allocator>::size_type new_capacity_)
{
    if (new_capacity_ > capacity_) {
        pointer new_data_ = alloc.allocate(new_capacity_);
        for (size_type i = 0; i < size_; ++i) {
            new_data_[i] = std::move(data_[i]);
        }
        alloc.deallocate(data_);
        data_ = new_data_;
        capacity_ = new_capacity_;
    }
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::shrink_to_fit()
{
    capacity_ = size_;
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::resize(
        typename Vector<T, V_Allocator>::size_type new_size_,
        typename Vector<T, V_Allocator>::const_reference val)
{
    if (new_size_ >= capacity_) {
        reserve(capacity_ ? 2 * capacity_ : 1);
    }
    for (size_type i = size_; i < new_size_; ++i) {
        data_[i] = val;
    }
    size_ = new_size_;
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::clear() noexcept
{
    for (size_type i = 0; i < size_; ++i) {
        (data_ + i)->~T();
    }
    size_ = 0;
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::push_back(
        typename Vector<T, V_Allocator>::const_reference val)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    data_[size_++] = val;
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::push_back(
        typename Vector<T, V_Allocator>::rvalue_reference val)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ * 2 : 1);
    }
    data_[size_++] = std::move(val);
}

template<class T, class V_Allocator>
void Vector<T, V_Allocator>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("No elements to pop.");
    }
    (data_ + (size_-- - 1))->~T();
}

template<class T, class V_Allocator>
template<class... Args>
void Vector<T, V_Allocator>::emplace_back(Args&&... args)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? 2 * capacity_ : 1);
    }
    data_[size_++] = value_type(std::forward<Args>(args)...);
}

//Iterators
template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::iterator
Vector<T, V_Allocator>::begin() noexcept
{
    return iterator(data_);
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::iterator
Vector<T, V_Allocator>::end() noexcept
{
    return iterator(data_ + size_);
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::iterator
Vector<T, V_Allocator>::rbegin() noexcept
{
    return iterator(data_ + (size_ - 1), true);
}

template<class T, class V_Allocator>
typename Vector<T, V_Allocator>::iterator
Vector<T, V_Allocator>::rend() noexcept
{
    return iterator(data_ - 1, true);
}