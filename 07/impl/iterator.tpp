template<class T>
Iterator<T>::Iterator(typename Iterator<T>::pointer ptr, bool reverse)
        : p(ptr), is_reverse(reverse)
{
}

template<class T>
Iterator<T>& Iterator<T>::operator++()
{
    if (is_reverse) {
        --p;
    } else {
        ++p;
    }
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator tmp(*this);
    if (is_reverse) {
        --p;
    } else {
        ++p;
    }
    return tmp;
}

template<class T>
Iterator<T>& Iterator<T>::operator--()
{
    if (is_reverse) {
        ++p;
    } else {
        --p;
    }
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator tmp(*this);
    if (is_reverse) {
        ++p;
    } else {
        --p;
    }
    return tmp;
}

template<class T>
typename Iterator<T>::reference
Iterator<T>::operator[](size_type idx)
{
    return p[idx];
}

template<class T>
typename Iterator<T>::const_reference
Iterator<T>::operator[](size_type idx) const
{
    return p[idx];
}

template<class T>
bool Iterator<T>::operator==(const Iterator& other) const noexcept
{
    return p == other.p && is_reverse == other.is_reverse;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator& other) const noexcept
{
    return p != other.p || is_reverse != other.is_reverse;
}

template<class T>
typename Iterator<T>::reference Iterator<T>::operator*()
{
    return *p;
}

template<class T>
typename Iterator<T>::const_reference Iterator<T>::operator*() const
{
    return *p;
}

template<class T>
Iterator<T>& Iterator<T>::operator+=(difference_type shift)
{
    p += is_reverse ? -shift : shift;
    return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator-=(difference_type shift)
{
    p -= is_reverse ? -shift : shift;
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator+(difference_type shift) const
{
    return Iterator(p + is_reverse ? -shift : shift, is_reverse);
}

template<class T>
Iterator<T> Iterator<T>::operator-(difference_type shift) const
{
    return Iterator(p - is_reverse ? -shift : shift, is_reverse);
}

template <class T>
typename Iterator<T>::difference_type
Iterator<T>::operator-(const Iterator<T>& other) const
{
    return is_reverse ? other.p - this->p : this->p - other.p;
}

template<class T>
Iterator<T> operator+(typename Iterator<T>::difference_type shift, const Iterator<T>& iter)
{
    Iterator<T> tmp(iter);
    tmp += shift;
    return tmp;
}

template<class T>
Iterator<T> operator-(typename Iterator<T>::difference_type shift, const Iterator<T>& iter)
{
    Iterator<T> tmp(iter);
    tmp -= shift;
    return tmp;
}

template<class T>
bool Iterator<T>::operator<(const Iterator& other) const noexcept
{
    return is_reverse ? p > other.p : p < other.p;
}

template<class T>
bool Iterator<T>::operator>(const Iterator& other) const noexcept
{
    return is_reverse ? p < other.p : p > other.p;
}

template<class T>
bool Iterator<T>::operator<=(const Iterator& other) const noexcept
{
    return is_reverse ? p >= other.p : p <= other.p;
}

template<class T>
bool Iterator<T>::operator>=(const Iterator& other) const noexcept
{
    return is_reverse ? p <= other.p : p >= other.p;
}