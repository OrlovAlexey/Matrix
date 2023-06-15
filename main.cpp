#include <iostream>
#include "src/Matrix/SquareMatrix.hpp"


BigInteger bin_pow(BigInteger a, BigInteger degree) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 != 0) {
        BigInteger c = bin_pow(a, degree - 1) * a;
        return c;
    }
    else {
        BigInteger b = bin_pow(a, degree / 2);
        return b * b;
    }
}

int main() {
//    Matrix<3,3,double> m1;
//    cin >> m1;
//    cout << m1;

    SquareMatrix<3, double> s;
    cout << s;

    return 0;
}
