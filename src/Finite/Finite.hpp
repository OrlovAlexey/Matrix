#pragma once
#include <iostream>

using std::ostream;
using std::istream;


template <int N>
struct Finite {
    long long num;
    Finite() : num(0) {};
    Finite(long long n) {
        if (n >= 0) {
            num = n % N;
        }
        else {
            num = abs(n) % N;
            num = N - num;
        }
    }
    Finite<N> operator- () {
        Finite<N> copy = *this;
        copy.num = N - copy.num;
        return copy;
    }
    Finite<N>& operator++ () {
        num += 1;
        if (num == N) num = 0;
        return *this;
    }
    Finite<N> operator++ (int) {
        Finite<N> copy = *this;
        ++(copy);
        return copy;
    }
    Finite<N>& operator-- () {
        num -= 1;
        if (num == -1) num = N-1;
        return *this;
    }
    Finite<N> operator-- (int) {
        Finite<N> copy = *this;
        --(copy);
        return copy;
    }
    Finite<N> operator+= (Finite<N> a) {
        num += a.num;
        num %= N;
        return *this;
    }
    Finite<N> operator-= (Finite<N> a) {
        num -= a.num;
        num = (num + N) % N;
        return *this;
    }
    Finite<N> operator*= (Finite<N> a) {
        num *= a.num;
        num %= N;
        return *this;
    }
    operator long long() {
        return num;
    }
};

template <int N>
bool operator== (Finite<N> a, Finite<N> b) {
    return (a.num == b.num);
}

template <int N>
bool operator!= (Finite<N> a, Finite<N> b) {
    return !(a == b);
}

template <int N>
Finite<N> operator+ (Finite<N> a, Finite<N> b) {
    return Finite<N>(a.num + b.num);
}

template <int N>
Finite<N> operator- (Finite<N> a, Finite<N> b) {
    return Finite<N>(a.num - b.num);
}

template <int N>
Finite<N> operator* (Finite<N> a, Finite<N> b) {
    return Finite<N>(a.num * b.num);
}

bool constexpr is_prime(int n) {
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

long long bin_pow_mod(long long a, long long degree, int N) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 != 0) {
        long long c = (bin_pow_mod(a, degree - 1, N) * a) % N;
        return c;
    }
    else {
        long long b = bin_pow_mod(a, degree / 2, N) % N;
        return (b * b) % N;
    }
}

template <int N>
Finite<N> Finiteinverse(Finite<N> a) {
    static_assert(is_prime(N), "Base is not prime!");
    assert(a.num != 0 && "No inverse for 0!");
    long long result = bin_pow_mod(a.num, N-2, N);
    result %= N;
    return Finite<N>(result);
}

template <int N>
Finite<N> operator/ (Finite<N> a, Finite<N> b) {
    static_assert(is_prime(N), "Base is not prime!");
    return a * Finiteinverse(b);
}

template <int N>
istream& operator>> (istream& in, Finite<N>& a) {
    in >> a.num;
    return in;
}

template <int N>
ostream& operator<< (ostream& out, const Finite<N>& a) {
    out << a.num;
    return out;
}