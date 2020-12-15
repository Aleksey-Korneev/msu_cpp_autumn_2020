#pragma once
#include <iostream>
#include <algorithm>

class BigInt {
    bool negative;
    size_t size;
    char* data;

    void remove_insignificant_zeros();
public:
    BigInt() noexcept;
    BigInt(int);
    BigInt(const std::string&);
    BigInt(const BigInt&);
    BigInt(BigInt&&) noexcept;
    ~BigInt() noexcept;

    BigInt& operator=(const BigInt&);
    BigInt& operator=(BigInt&&);

    bool operator==(const BigInt&) const noexcept;
    bool operator!=(const BigInt&) const noexcept;
    bool operator<(const BigInt&) const noexcept;
    bool operator>(const BigInt&) const noexcept;
    bool operator<=(const BigInt&) const noexcept;
    bool operator>=(const BigInt&) const noexcept;

    BigInt operator-() const;
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;

    friend inline BigInt operator+(const int lhs, const BigInt& rhs)
    {
        return rhs + lhs;
    }
    friend inline BigInt operator-(const int lhs, const BigInt& rhs)
    {
        return -(rhs - lhs);
    }
    friend inline BigInt operator*(const int lhs, const BigInt& rhs)
    {
        return rhs * lhs;
    }

    friend std::ostream& operator<<(std::ostream&, const BigInt&) noexcept;
};
