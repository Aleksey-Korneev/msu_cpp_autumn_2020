#include "matrix.hpp"

MatrixRow::MatrixRow()
{
}

void MatrixRow::SetArraySize(const size_t columns)
{
    length = columns;
    array = new int[length];
}

int& MatrixRow::operator[](const size_t index)
{
    if (index >= length) {
        throw std::out_of_range("Column index out of range.");
    }
    return array[index];
}

const int& MatrixRow::operator[](const size_t index) const
{
    if (index >= length) {
        throw std::out_of_range("Column index out of range.");
    }
    return array[index];
}



Matrix::Matrix(const size_t row, const size_t col) :
        rows(row),
        columns(col),
        matrix(new MatrixRow[rows])
{
    for (size_t i = 0; i < rows; ++i) {
        matrix[i].SetArraySize(columns);
    }
}

Matrix::Matrix(const Matrix& other) : Matrix::Matrix(other.rows, other.columns)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

size_t Matrix::GetRows() const
{
    return rows;
}

size_t Matrix::GetColumns() const
{
    return columns;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return false;
    }
    for (size_t i = 0; i < lhs.rows; ++i) {
        for (size_t j = 0; j < lhs.columns; ++j) {
            if (lhs.matrix[i][j] != rhs.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns) {
        return true;
    }
    bool is_equal = true;
    for (size_t i = 0; i < lhs.rows; ++i) {
        for (size_t j = 0; j < lhs.columns; ++j) {
            if (lhs.matrix[i][j] != rhs.matrix[i][j]) {
                is_equal = false;
            }
        }
    }
    return !is_equal;
}

Matrix operator+(const Matrix& lhs, const Matrix&rhs) {
    assert(lhs.rows == rhs.rows && lhs.columns == rhs.columns);
    Matrix m(lhs.rows, lhs.columns);
    for (size_t i = 0; i < lhs.rows; ++i) {
        for (size_t j = 0; j < lhs.columns; ++j) {
            m.matrix[i][j] = lhs.matrix[i][j] + rhs.matrix[i][j];
        }
    }
    return m;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.columns; ++j) {
            out << matrix.matrix[i][j] << ' ';
        }
        if (i + 1 != matrix.rows) {
            out << std::endl;
        }
    }
    return out;
}

Matrix& Matrix::operator*=(const int value)
{
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] *= value;
        }
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    assert(rows == other.rows && columns == other.columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    return *this;
}

MatrixRow& Matrix::operator[](const size_t row)
{
    if (row >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    return matrix[row];
}

const MatrixRow& Matrix::operator[](const size_t row) const
{
    if (row >= rows) {
        throw std::out_of_range("Row index out of range.");
    }
    return matrix[row];
}

Matrix::~Matrix()
{
    delete []matrix;
}
