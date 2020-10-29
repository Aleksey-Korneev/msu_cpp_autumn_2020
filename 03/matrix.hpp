#pragma once

#include <iostream>
#include <cstddef>
#include <cassert>

class MatrixRow
{
    size_t length;
    int *array;
public:
    MatrixRow();
    void SetArraySize(const size_t columns);
    int& operator[](const size_t index);
    const int& operator[](const size_t index) const;
};

class Matrix
{
    const size_t rows, columns;
    MatrixRow *matrix;
public:
    Matrix(size_t row, size_t col);
    Matrix(const Matrix& other);
    size_t GetRows() const;
    size_t GetColumns() const;

    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
    Matrix& operator*=(const int value);
    Matrix& operator+=(const Matrix& other);
    MatrixRow& operator[](const size_t row);
    const MatrixRow& operator[](const size_t row) const;
    ~Matrix();
};
