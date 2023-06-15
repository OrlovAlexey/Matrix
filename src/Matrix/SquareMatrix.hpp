#include "Matrix.hpp"


template <unsigned N, typename Field>
struct Matrix<N,N,Field>{
    vector<vector<Field>> mat;
    Matrix() {
        mat.resize(N);
        for (size_t i = 0; i < N; ++i) {
            mat[i].resize(N);
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = ((i == j) ? 1 : 0);
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
    Matrix<N, N, Field> operator+= (const Matrix<N, N, Field>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] += m.mat[i][j];
            }
        }
        return *this;
    }
    Matrix<N, N, Field> operator-= (const Matrix<N, N, Field>& m) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] -= m.mat[i][j];
            }
        }
        return *this;
    }
    Matrix<N, N, Field> transposed() const {
        Matrix<N, N, Field> transposed;
        transposed.mat.resize(N);
        for (size_t i = 0; i < N; ++i) {
            transposed.mat[i].resize(N);
            for (size_t j = 0; j < N; ++j) {
                transposed.mat[i][j] = mat[j][i];
            }
        }
        return transposed;
    }
    Matrix<N, N, Field> operator*= (const Matrix<N, N, Field>& m) {
        Matrix<N, N, Field> copy = *this;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = 0;
                for (size_t k = 0; k < N; ++k) {
                    mat[i][j] += copy.mat[i][k] * m.mat[k][j];
                }
            }
        }
        return *this;
    }
    Field det() const {
        Matrix<N, N, Field> copy = *this;
        Field temp;
        for (size_t k = 0; k < N; ++k) {
            for (size_t i = k + 1; i < N; ++i) {
                temp = -copy.mat[i][k] / copy.mat[k][k];
                for (size_t j = 0; j < N; ++j) {
                    copy.mat[i][j] += copy.mat[k][j] * temp;
                }
            }
        }
        Field det = 1;
        for (size_t i = 0; i < N; i++) {
            det = det * copy.mat[i][i];
        }
        return det;
    }
    size_t rank() const {
        size_t rank = N;
        vector<bool> line(N);
        Matrix<N, N, Field> copy = *this;
        for (size_t i = 0; i < N; ++i) {
            size_t j;
            for (j = 0; j < N; ++j)
                if (!line[j] && copy.mat[i][j] != Field(0)) {
                    break;
                }
            if (j == N) {
                --rank;
            }
            else {
                line[j] = true;
                Field temp = copy.mat[i][j];
                for (size_t m = j; m < N; ++m) {
                    copy.mat[i][m]= copy.mat[i][m] / temp;
                }
                for (size_t k = 0; k < N; ++k) {
                    if (k != j && copy.mat[i][j] != Field(0)) {
                        for (size_t p = j; p < N; ++p) {
                            copy.mat[k][p] -= copy.mat[i][p] * copy.mat[k][j];
                        }
                    }
                }
            }
        }
        return rank;
    }
    Field trace() {
        Field trace = 0;
        for (size_t i = 0; i < N; ++i) {
            trace += mat[i][i];
        }
        return trace;
    }
    void invert() {
        Matrix<N, N, Field> unit = Matrix<N, N, Field>();
        Field temp;
        for (size_t i = 0; i < N; ++i) {
            temp = mat[i][i];
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = mat[i][j] / temp;
                unit[i][j] = unit[i][j] / temp;
            }//2N^2
            for (size_t j = i + 1; j < N; ++j) {
                temp = mat[j][i];
                for (size_t k = 0; k < N; ++k) {
                    mat[j][k] -= (mat[i][k] * temp);
                    unit[j][k] -= (unit[i][k] * temp);
                }
            }//4N^3
        }
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < i; ++j) {
                temp = mat[j][i];
                for (size_t k = 0; k < N; ++k) {
                    mat[j][k] -= (mat[i][k] * temp);
                    unit[j][k] -= (unit[i][k] * temp);
                }
            }
        }//~4N^3
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                mat[i][j] = unit[i][j];
            }
        }
    }
    Matrix<N, N, Field> inverted() const {
        Matrix<N, N, Field> copy = *this;
        copy.invert();
        return copy;
    }
    vector<Field> getRow(unsigned i) {
        return mat[i];
    }
    vector<Field> getColumn(unsigned j) {
        vector<Field> column(N);
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

template <size_t N, typename Field = Rational>
using SquareMatrix = Matrix<N, N, Field>;