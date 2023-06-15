# Matrix
Template C++ Matrix implementation over arbitrary Field

## Implementation
The Matrix class is based on std::vector of type Field, which is my self-written Rational by default. <br>
There also implemented class Finite field (numbers from 0 to N) to show other type of non-trivial Field in matrices. <br>
SquareMatrix is an alias for Matrix<N, N> and extends amount of methods, which are special for squared matrices.

## Possibilities
**Finite Field:**
  - some constuctors
  - basic operations (+,-,*,/)
  - their equal-versions (+=, -=, *=)
  - unary minus (-)
  - post-increment and pre-increment (++, --)
  - comparison operation (==, !=)
  - input and output operators (<<, >>)
  - inverse of a number
  - binary power

**Matrix:**
  - constructors (default and from vector)
  - basic operations (+,-,*)
  - their equal-versions (+=, -=, *=)
  - trasposing
  - rank of a matrix
  - braces operators [] (by reference and not)
  - comparison operation (==, !=)
  - input and output operators (<<, >>)
  - left and right multiplication on an element of the Field

**SquareMatrix:**
  - everything that matrix can
  - determinant computing (N^3)
  - trace computing
  - inverse matrix computing (N^3)
