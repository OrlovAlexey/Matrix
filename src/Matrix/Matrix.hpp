#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "../../Rational/Rational.h"

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;
using std::ostream;
using std::istream;


template <unsigned N, unsigned M, typename Field = Rational>
struct Matrix{
    vector<vector<Field>> mat;
    Matrix() {
        mat.resize(N);
        for (size_t i = 0; i < N; ++i) {
            mat[i].resize(M);
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] = (Field)0;
            }
        }
    }
    template <typename F = int>
    Matrix(const vector<vector<F>>& vec) {
        mat.resize(vec.size());
        for (size_t i = 0; i < vec.size(); ++i) {
            for (size_t j = 0; j < vec[i].size(); ++j) {
                mat[i].resize(vec[i].size());
                mat[i][j] = vec[i][j];
            }
        }
    }
    Matrix<N, M, Field> operator+= (const Matrix<N, M, Field>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] += m.mat[i][j];
            }
        }
        return *this;
    }
    Matrix<N, M, Field> operator-= (const Matrix<N, M, Field>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                mat[i][j] -= m.mat[i][j];
            }
        }
        return *this;
    }
    Matrix<M, N, Field> transposed() const {
        Matrix<M, N, Field> transposed;
        transposed.mat.resize(M);
        for (size_t i = 0; i < M; ++i) {
            transposed.mat[i].resize(N);
            for (size_t j = 0; j < N; ++j) {
                transposed.mat[i][j] = mat[j][i];
            }
        }
        return transposed;
    }
    size_t rank() const {
        size_t rank = min(N, M);
        vector<bool> line(M);
        Matrix<N, M, Field> copy = *this;
        for (size_t i = 0; i < N; ++i) {
            size_t j;
            for (j = 0; j < M; ++j)
                if (!line[j] && copy.mat[i][j] != Field(0)) {
                    break;
                }// находим лидера в строке i
            if (j == M) {
                --rank;
            }
            else {
                line[j] = true;
                Field temp = copy.mat[i][j];
                for (size_t m = j; m < M; ++m) {
                    copy.mat[i][m]= copy.mat[i][m] / temp;
                }
                for (size_t k = 0; k < N; ++k) {
                    if (k != j && copy.mat[i][j] != Field(0)) {
                        for (size_t p = j; p < M; ++p) {
                            copy.mat[k][p] -= copy.mat[i][p] * copy.mat[k][j];
                        }
                    }
                }
            }
        }
        return rank;
    }
    vector<Field> getRow(unsigned i) {
        return mat[i];
    }
    vector<Field> getColumn(unsigned j) {
        vector<Field> column(M);
        for (size_t i = 0; i < N; ++i) {
            column[i] = mat[i][j];
        }
        return column;
    }
    vector<Field>& operator[] (unsigned i) {
        return mat[i];
    }
    vector<Field> operator[] (unsigned i) const {
        return mat[i];
    }
};

template <unsigned N, unsigned M, typename Field = Rational>
bool operator== (const Matrix<N, M, Field>& m1, const Matrix<N, M, Field>& m2) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (m1.mat[i][j] != m2.mat[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <unsigned N, unsigned M, typename Field = Rational>
bool operator!= (const Matrix<N, M, Field>& m1, const Matrix<N, M, Field>& m2) {
    return !(m1 == m2);
}

template <unsigned N, unsigned M, typename Field = Rational>
Matrix<N, M, Field> operator+ (const Matrix<N, M, Field>& m1, const Matrix<N, M, Field>& m2) {
    Matrix<N, M, Field> copy = m1;
    copy += m2;
    return copy;
}

template <unsigned N, unsigned M, typename Field = Rational>
Matrix<N, M, Field> operator- (const Matrix<N, M, Field>& m1, const Matrix<N, M, Field>& m2) {
    Matrix<N, M, Field> copy = m1;
    copy -= m2;
    return copy;
}

template <unsigned N, unsigned M, unsigned K, typename Field = Rational>
Matrix<N, K, Field> operator* (const Matrix<N, M, Field>& m1, const Matrix<M, K, Field>& m2) {
    Matrix<N, K, Field> m3;
    m3.mat.resize(N);
    for (size_t i = 0; i < N; ++i) {
        m3.mat[i].resize(K);
        for (size_t j = 0; j < K; ++j) {
            m3.mat[i][j] = 0;
            for (size_t k = 0; k < M; ++k) {
                m3.mat[i][j] += m1.mat[i][k] * m2.mat[k][j];
            }
        }
    }
    return m3;
}

template <unsigned N, unsigned M, typename Field = Rational>
Matrix<N, M, Field> operator* (const Matrix<N, M, Field>& m, Field a) {
    Matrix<N, M, Field> copy = m;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            copy.mat[i][j] *= a;
        }
    }
    return copy;
}

template <unsigned N, unsigned M, typename Field = Rational>
Matrix<N, M, Field> operator* (Field a, const Matrix<N, M, Field>& m) {
    Matrix<N, M, Field> copy = m;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            copy.mat[i][j] *= a;
        }
    }
    return copy;
}


template <unsigned N, unsigned M, typename Field = Rational>
istream& operator>> (istream& in, Matrix<N, M, Field>& matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            in >> matrix.mat[i][j];
        }
    }
    return in;
}

template <unsigned N, unsigned M, typename Field = Rational>
ostream& operator<< (ostream& out, const Matrix<N, M, Field>& matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            out << matrix.mat[i][j] << " ";
        }
        cout << '\n';
    }
    return out;
}