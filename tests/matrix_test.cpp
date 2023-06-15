#include <vector>
#include <fstream>
#include <gtest/gtest.h>

#include "BigInteger/BigInteger.h"
#include "Rational/Rational.h"
#include "Finite/Finite.hpp"
#include "Matrix/Matrix.hpp"
#include "Matrix/SquareMatrix.hpp"

using std::vector;


TEST(FiniteTestCase, testArithmetic) {
    Finite<433494437> x = 1279;
    std::cout << (x == 1279);
    x *= x += x *= ++x;
    for (int i = 0; i < 1000000; ++i)
        ++x;
    auto y = Finite<433494437>(1) / x;
    ASSERT_EQ(y*x, Finite<433494437>(1)) << "Finite Finite arithmetic failed.";
}

TEST(MatrixFiniteTestCase, testMatrix) {
    vector<vector<int>> a = {
            {8,-4,-5,5,9},
            {1,-3,-5,0,-7},
            {7,-5,1,4,1},
            {3,-1,3,2,5}
    };
    vector<vector<int>> b = {
            {4,0,3,2},
            {1,-7,4,5},
            {7,1,5,3},
            {-5,-3,-3,-1},
            {1,-5,2,3}
    };
    const Matrix<4, 5, Finite<17>> am = a;
    const Matrix<5, 4, Finite<17>> bm = b;

    ASSERT_EQ(am.rank(), 4) << "rank() method failed.";
    ASSERT_EQ(bm.rank(), 3) << "rank() method failed.";

    vector<vector<int>> ab = {
            {-23, -37, -14, 3},
            {-41, 51, -48, -49},
            {11, 19, -4, -9},
            {27, -21, 24, 23}
    };

    const auto abm = am * bm;
    const auto expected_abm = SquareMatrix<4, Finite<17>>(ab);
    ASSERT_EQ(abm, expected_abm) << "matrix multiplication or constructors failed.";

    const auto aminusb = am - bm.transposed();
    vector<vector<int>> diff = {
            {4, -5, -12, 10, 8},
            {1, 4, -6, 3, -2},
            {4, -9, -4, 7, -1},
            {1, -6, 0, 3, 2}
    };
    auto expected_aminusb = Matrix<4, 5, Finite<17>>(diff);
    ASSERT_EQ(aminusb, expected_aminusb) << "Addition or subtraction failed.";

    auto newMatrix = Finite<17>(2) * aminusb * bm;
    newMatrix[2][2] = 1;

    auto expected_det = Finite<17>(14420160);
    ASSERT_EQ(newMatrix.det(), expected_det) << "Determinant is wrong.";

    auto expected_trace = Finite<17>(-345);
    ASSERT_EQ(newMatrix.trace(), expected_trace) << "Trace is wrong.";

    Matrix<4, 4, Finite<17>> F = newMatrix.inverted();
    Matrix<4, 4, Finite<17>> G = F * newMatrix;
    auto expected_unity = Matrix<4, 4, Finite<17>>::unity();
    ASSERT_EQ(F * newMatrix, expected_unity) << "A*A^(-1) must be equal to unity matrix.";

    std::cerr << "Tests over the finite field passed!\n";
}

TEST(MatrixTestCase, testBigMatrix) {
    std::ifstream in("big_matrix.txt");
    SquareMatrix<20> bigMatrix;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            BigInteger input;
            in >> input;
            bigMatrix[i][j] = input;
        }
    }

    vector<vector<double>> bigInvertedMatrix(20, vector<double>(20));
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            in >> bigInvertedMatrix[i][j];
        }
    }

    auto anotherMatrix = bigMatrix;
    //bigMatrix.inverted();
    bigMatrix.invert();
    std::cerr << "Big matrix inverted!\n";
    for (int i = 0; i < 20; ++i) {
        auto row = bigMatrix.getRow(i);
        auto anotherRow = bigInvertedMatrix[i];
        for (int j = 0; j < 20; ++j) {
            ASSERT_LE(abs(static_cast<double>(row[j]) - anotherRow[j]), 1e-6) << "Inverted matrix is incorrect!";
        }
    }
    std::cerr << "Inverted matrix is correct!\n";
    bigMatrix *= anotherMatrix;
    std::cerr << "Matrix multiplied by its inverted matrix!\n";
    SquareMatrix<20> unity = SquareMatrix<20>::unity();
    for (int j = 0; j < 20; ++j) {
        auto column = bigMatrix.getColumn(j);
        auto unityColumn = unity.getColumn(j);
        for (int i = 0; i < 20; ++i) {
            ASSERT_EQ(column[i], unityColumn[i]) << "Product of A and A^(-1) must be equal to unity matrix.";
        }
    }

    std::cerr << "Result of A*A^(-1) is correct!\n";

    auto det = anotherMatrix.det();
    std::cerr << "Determinant is computed!\n";
    //det /= 20;
    for (int i = 0; i < 20; ++i)
        anotherMatrix[0][i] /= det;
    // now anotherMatrix is orthogonal matrix
    ASSERT_EQ(anotherMatrix.det(), 1) << "Dividing a row by det must make the determinant equal to 1.";

    auto transposedMatrix = anotherMatrix.transposed();
    auto unity_det = (anotherMatrix *= transposedMatrix).det();
    ASSERT_EQ(unity_det, 1) << "Product of two matrices with det=1 must give the matrix with same determinant.";
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}