#pragma once
#include "../BigInteger/BigInteger.h"


class Rational{
private:
    BigInteger num;
    BigInteger den;
    bool is_positive = true;

public:
    Rational() = default;
    Rational(const BigInteger b1, const BigInteger b2);
    Rational(const BigInteger& b);
    Rational(int a);

    Rational operator-() const;
    Rational& operator+= (const Rational& r);
    Rational& operator-= (const Rational& r);

    bool operator== (const Rational& r) const;
    bool operator!= (const Rational& r) const;
    bool operator<= (const Rational& r) const;
    bool operator>= (const Rational& r) const;

    Rational& operator*= (const Rational& r);
    Rational& operator/= (const Rational& r);

    string toString() const;
    string asDecimal(size_t precision = 0) const;
    explicit operator double();

    friend bool operator< (const Rational&, const Rational&); // bad implementation
    friend bool operator> (const Rational&, const Rational&);
private:
    Rational& changessign(); // unary minus without creating a copy
    BigInteger gcd(BigInteger a, BigInteger b);
};

bool operator< (const Rational& a, const Rational& b);
bool operator> (const Rational& a, const Rational& b);

Rational operator+ (const Rational& r1, const Rational& r2);
Rational operator- (const Rational& r1, const Rational& r2);
Rational operator* (const Rational& r1, const Rational& r2);
Rational operator/ (const Rational& r1, const Rational& r2);
