template<class T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_type size) const
{
    if (size == 0) {
        return nullptr;
    }
    return new T[size];
}

template<class T>
void Allocator<T>::deallocate(pointer p) const
{
    if (p != nullptr) {
        delete [] p;
    }
}