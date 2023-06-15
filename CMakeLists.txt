cmake_minimum_required(VERSION 3.17)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        googletest
)

# Main target
add_executable(matrix src/BigInteger/BigInteger.cpp src/BigInteger/BigInteger.h src/Rational/Rational.cpp src/Rational/Rational.h src/Finite/Finite.hpp src/Matrix/Matrix.hpp src/Matrix/SquareMatrix.hpp main.cpp )

# Test target
add_executable(test_matrix src/BigInteger/BigInteger.cpp src/BigInteger/BigInteger.h src/Rational/Rational.cpp src/Rational/Rational.h src/Finite/Finite.hpp src/Matrix/Matrix.hpp src/Matrix/SquareMatrix.hpp tests/matrix_test.cpp)

target_include_directories(
        test_matrix PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
        test_matrix PRIVATE
        gtest gtest_main
)

target_compile_options(
        matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
)

target_compile_options(
        test_matrix PRIVATE
        -Wall -Wextra -pedantic -Werror
)