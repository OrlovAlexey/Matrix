#pragma once
#include <cstdlib>


template <int N>
struct Finite {
    long long num;
    Finite();
    Finite(long long n);
    Finite<N> operator- ();
    Finite<N>& operator++ ();
    Finite<N> operator++ (int);
    Finite<N>& operator-- ();
    Finite<N> operator-- (int);
    Finite<N> operator+= (Finite<N> a);
    Finite<N> operator-= (Finite<N> a);
    Finite<N> operator*= (Finite<N> a);
    operator long long();
};

template <int N>
bool operator== (Finite<N> a, Finite<N> b);

template <int N>
bool operator!= (Finite<N> a, Finite<N> b);

template <int N>
Finite<N> operator+ (Finite<N> a, Finite<N> b);

template <int N>
Finite<N> operator- (Finite<N> a, Finite<N> b);

template <int N>
Finite<N> operator* (Finite<N> a, Finite<N> b);

bool constexpr is_prime(int n);
long long bin_pow_mod(long long a, long long degree, int N);

template <int N>
Finite<N> FiniteInverse(Finite<N> a);

template <int N>
Finite<N> operator/ (Finite<N> a, Finite<N> b);