#include <iostream>

template<class T>
class SharedPtr {
    T* data;
    size_t* count;
public:
    SharedPtr() : data(nullptr), count(nullptr)
    {
    }

    SharedPtr(T* data_) : data(data_), count(new size_t(1))
    {
    }
    
    SharedPtr(SharedPtr<T>& other) : data(other.data), count(other.count)
    {
        ++(*count);
    }

    SharedPtr(SharedPtr<T>&& other) : data(std::move(other.data)), count(std::move(other.count))
    {
        other.data = nullptr;
        other.count = nullptr;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& other)
    {
        if (this == &other) {
            return *this;
        }
        data = std::move(other.data);
        count = std::move(other.count);
        other.data = nullptr;
        other.count = nullptr;
        return *this;
    }

    SharedPtr<T>& operator=(SharedPtr<T>& other)
    {
        if (this == &other) {
            return *this;
        }
        if (count != nullptr) {
            if (*count == 1) {
                delete data;
                delete count;
            } else {
                --(*count);
            }
        }
        data = other.data;
        count = other.count;
        ++(*count);
        return *this;
    }    

    T* operator->() const {
        return data;
    }

    T* get() const {
        return data;
    }

    void reset(T* new_data) {
        if (--(*count) == 0) {
            delete data;
            delete count;
        }
        data = new_data;
        count = new size_t(1);
    }
    
    ~SharedPtr() {
        if (count != nullptr) {
            if (--(*count) == 0) {
                delete data;
                delete count;
            }
        }
    }
};
