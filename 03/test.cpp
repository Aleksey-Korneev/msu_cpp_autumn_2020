#include "matrix.hpp"

void RunTests()
{
    std::cout << __func__ << std::endl << std::endl;
    const size_t rows = 3;
    const size_t columns = 6;
    Matrix m(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            m[i][j] = i + j;
        }
    }
    std::cout << "Matrix m:" << std::endl << m << std::endl << std::endl;
    assert(m.GetRows() == rows);
    assert(m.GetColumns() == columns);

    m[0][0] = m[0][1] = -1;
    assert(m[0][0] = -1);
    assert(m[0][1] = -1);

    double x = m[0][1];
    assert(x == -1.);

    Matrix m1(m);
    assert(m == m1);
    m1[0][0] = 0;
    m1[0][1] = 1;
    assert(m != m1);

    Matrix m2(rows, columns);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            m2[i][j] = 2 * (i + j);
        }
    }

    assert(m1 != m2);
    m1 *= 2;
    assert(m1 == m2);
    
    try {
        m[rows][0];
    } catch (const std::out_of_range& e) {
        std::cout << "Caught a planned exception: " << e.what() << std::endl;
    }

    try {
        m[0][columns];
    } catch (const std::out_of_range& e) {
        std::cout << "Caught a planned exception: " << e.what() << std::endl;
    }

    try {
        m[-1][0] = 0;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught a planned exception: " << e.what() << std::endl;
    }

    try {
        m[0][-1] = 0;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught a planned exception: " << e.what() << std::endl;
    }

    Matrix m3 = m1 + m2;
    std::cout << std::endl << "Matrix m1:" << std::endl << m1 << std::endl;
    std::cout << std::endl << "Matrix m2:" << std::endl << m2 << std::endl;
    std::cout << std::endl << "Matrix m3 = m1 + m2:" << std::endl << m3 << std::endl;
    m3 += (m2 *= -1);
    assert(m1 == m3);    
}

int main()
{
    RunTests();
    std::cout << std::endl << "All tests passed." << std::endl;
    return 0;
}
