cmake_minimum_required(VERSION 3.17)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix BigInteger/BigInteger.cpp Rational/Rational.cpp Finite/Finite.cpp Matrix/Matrix.cpp Matrix/SquareMatrix.cpp main.cpp)