#include "bigint.hpp"

BigInt::BigInt() noexcept : negative(false), size(0), data(nullptr)
{
}

BigInt::BigInt(int num) : negative(num < 0)
{
    std::string str = std::to_string(num);
    if (negative) {
        str = str.substr(1);
    }
    size = str.length();
    data = new char[size];
    std::copy(str.c_str(), str.c_str() + size, data);
}

BigInt::BigInt(const std::string& str)
{
    size_t str_size = str.size();
    if (str_size == 0) {
        negative = false;
        size = 0;
        data = nullptr;
        return;
    }
    if (str_size == 1 && str[0] == '-') {
        throw std::invalid_argument("Invalid argument in constructor from string");
    }
    size_t start = 0;
    if (str[0] == '-') {
        negative = true;
        ++start;
    } else {
        negative = false;
    }
    //A special string format designed in arithmetic operators
    if (std::count(str.begin(), str.end(), '\0') != static_cast<int>(str_size)) {
        for (size_t cnt = start; cnt < str_size; ++cnt) {
            if (str[cnt] < '0' || str[cnt] > '9') {
                throw std::invalid_argument("Invalid argument in constructor from string");
            }
        }
    }
    size = str.length() - start;
    data = new char[size + 1u];
    std::copy(str.c_str() + start, str.c_str() + (size + start + 1u), data);
    remove_insignificant_zeros();
}

BigInt::BigInt(const BigInt& other)
        : negative(other.negative),
        size(other.size),
        data(new char[size])
{
    std::copy(other.data, other.data + size, data);
}

BigInt::BigInt(BigInt&& other) noexcept
        : negative(other.negative),
        size(other.size),
        data(other.data)
{
    other.negative = false;
    other.size = 0;
    other.data = nullptr;
}

BigInt::~BigInt() noexcept
{
    if (data) {
        delete []data;
    }
}

BigInt& BigInt::operator=(const BigInt& other)
{
    if (this == &other) {
        return *this;
    }
    negative = other.negative;
    size = other.size;
    if (data) {
        delete []data;
    }
    data = new char[size];
    std::copy(other.data, other.data + size, data);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other)
{
    if (this == &other) {
        return *this;
    }
    negative = other.negative;
    size = other.size;
    if (data) {
        delete []data;
    }
    data = other.data;
    other.negative = false;
    other.size = 0;
    other.data = nullptr;
    return *this;
}

bool BigInt::operator==(const BigInt& other) const noexcept
{
    if (this == &other) {
        return true;
    }
    if (negative != other.negative || size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const noexcept
{
    if (this == &other) {
        return false;
    }
    if (negative != other.negative || size != other.size) {
        return true;
    }
    for (size_t i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return true;
        }
    }
    return false;
}

bool BigInt::operator<(const BigInt& other) const noexcept
{
    if (*this == other) {
        return false;
    }
    if (negative && other.negative) {
        return -(other) < -(*this);
    } else if (negative && !other.negative) {
        return true;
    } else if (!negative && other.negative) {
        return false;
    } else {
        if (size != other.size) {
            return size < other.size;
        } else {
            for (int i = size - 1; i >= 0; --i) {
                if (data[i] != other.data[i]) {
                    return data[i] < other.data[i];
                }
            }
            return false;
        }
    }
}

bool BigInt::operator>(const BigInt& other) const noexcept
{
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const noexcept
{
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const noexcept
{
    return !(*this < other);
}

BigInt BigInt::operator-() const
{
    BigInt other(*this);
    other.negative = !negative;
    return other;
}

BigInt BigInt::operator+(const BigInt& other) const
{
    if (negative && !other.negative) {
        BigInt tmp(*this);
        tmp.negative = !negative;
        return other - tmp;
    } else if (!negative && other.negative) {
        BigInt tmp(other);
        tmp.negative = !other.negative;
        return *this - tmp;
    }
    std::string tmp(std::max(size, other.size) + 1, '\0');
    BigInt res(tmp);
    res.negative = negative;
    size_t left_diff = res.size - size;
    size_t right_diff = res.size - other.size;
    size_t summand2 = 0;
    for (size_t i = res.size - 1; i >= 1; --i) {
        size_t summand1 = (i >= left_diff) ? (data[i - left_diff] - '0') : 0;
        summand1 += (i >= right_diff) ? (other.data[i - right_diff] - '0') : 0;
        res.data[i] = (summand1 + summand2) % 10 + '0';
        if (i - 1) {
            summand2 = (summand1 + summand2) / 10;
        } else {
            res.data[0] = (summand1 + summand2) / 10 + '0';
        }
    }
    res.remove_insignificant_zeros();
    return res;
}

BigInt BigInt::operator-(const BigInt& other) const
{
    if (negative && !other.negative) {
        return -((-*this) + other);
    } else if (!negative && other.negative) {
        return *this + (-other);
    } else if (negative && other.negative) {
        return (-other) - (-*this);
    } else if (*this < other) {
        return -(other - *this);
    }
    std::string str(std::max(size, other.size), '\0');
    BigInt res(str);
    size_t left = res.size - size;
    size_t right = res.size - other.size;
    size_t summand3 = 0;
    for (int cnt = res.size - 1; cnt >= 0 ; --cnt) {
        size_t i = cnt;
        size_t summand1 = (i >= left) ? data[i - left] - '0' : 0;
        size_t summand2 = (i >= right) ? other.data[i - right] - '0' : 0;
        size_t diff = summand1 - summand2 - summand3;
        if (summand1 - summand2 >= summand3) {
            summand3 = 0;
        } else {
            summand3 = 1;
            diff += 10;
        }
        res.data[i] = diff + '0';
    }
    res.remove_insignificant_zeros();
    return res;
}

BigInt BigInt::operator*(const BigInt& other) const
{
    std::string str(size + other.size, '\0');
    BigInt res(str);
    res.negative = negative != other.negative;
    for (size_t i = 0; i < size; ++i) {
        size_t remainder = 0;
        for (size_t j = 0; j < other.size; ++j) {
            size_t product = data[size - i - 1] - '0';
            product *= other.data[other.size - j - 1] - '0';
            res.data[res.size - i - j - 1] += product + remainder;
            remainder = res.data[res.size - i - j - 1] / 10;
            res.data[res.size - i - j - 1] %= 10;
        }
        res.data[res.size - i - other.size - 1] += remainder;
    }
    for (size_t i = 0; i < res.size; ++i) {
        res.data[i] += '0';
    }
    res.remove_insignificant_zeros();
    if (res.size == 1 && res.data[0] == '0') {
        res.negative = false;
    }
    return res;
}

std::ostream& operator<<(std::ostream& out, const BigInt& bigint) noexcept
{
    if (bigint.negative) {
        out << '-';
    }
    for (size_t i = 0; i < bigint.size; ++i) {
        out << bigint.data[i];
    }
    return out;
}

void BigInt::remove_insignificant_zeros()
{
    size_t i = 0;
    for (; i < size && data[i] == '0'; ++i);
    if (i == 0) {
        return;
    } else if (i == size) {
        delete []data;
        size = 1;
        data = new char[size];
        data[0] = '0';
        return;
    }
    char* new_data = new char[size - i + 1];
    size_t j = 0;
    for (; i <= size; ++i, ++j) {
        new_data[j] = data[i];
    }
    delete []data;
    data = new_data;
    size = j - 1;
    std::copy(new_data, new_data + size + 1, data);
}
