#include "Rational.h"


Rational::Rational(const BigInteger b1, const BigInteger b2) {
    if (b1 != 0) is_positive = ((b1.sgn() && b2.sgn()) || (!b1.sgn() && !b2.sgn()));
    BigInteger g = gcd(b1.big_abs(), b2.big_abs());
    num = b1.big_abs() / g;
    den = b2.big_abs() / g;
}

Rational::Rational(const BigInteger &b) {
    if (b != 0) is_positive = b.sgn();
    num = b.big_abs();
    den = 1;
}

Rational::Rational(int a) {
    num = abs(a);
    den = 1;
    is_positive = (a >= 0);
}

Rational Rational::operator-() const {
    Rational copy = *this;
    if (copy != 0) copy.is_positive = !copy.is_positive;
    return copy;
}

Rational &Rational::operator+=(const Rational &r) {
    if (!is_positive) {
        if (!r.is_positive) {
            BigInteger n1 = (r.den * num + den * r.num).big_abs();
            BigInteger d1 = (den * r.den).big_abs();
            BigInteger g1 = gcd(n1, d1);
            num = n1 / g1;
            den = d1 / g1;
            return *this;
        } else {
            return (this->changessign() -= r).changessign();
        }
    }
    else if (!r.is_positive) {
        is_positive = !is_positive;
        *this -= r;
        is_positive = !is_positive;
        return *this;
    } else {
        BigInteger n1 = (r.den * num + den * r.num).big_abs();
        BigInteger d1 = (den * r.den).big_abs();
        BigInteger g1 = gcd(n1, d1);
        num = n1 / g1;
        den = d1 / g1;
        return *this;
    }
}

Rational &Rational::operator-=(const Rational &r) {
    if (!this->is_positive) {
        if (!r.is_positive) {
            if (*this > r) {
                Rational temp = *this;
                *this = r;
                return (*this -= temp).changessign();
            } else {
                BigInteger n1 = (r.den * num - den * r.num).big_abs();
                BigInteger d1 = (den * r.den).big_abs();
                BigInteger g1 = gcd(n1, d1);
                num = n1 / g1;
                den = d1 / g1;
                return *this;
            }
        } else {
            return (this->changessign() += r).changessign();
        }
    } else if (!r.is_positive) {
        is_positive = !is_positive;
        *this += r;
        is_positive = !is_positive;
        return *this;
    } else {
        if (*this < r) {
            Rational temp = *this;
            *this = r;
            return (*this -= temp).changessign();
        } else {
            BigInteger n1 = (r.den * num - den * r.num).big_abs();
            BigInteger d1 = (den * r.den).big_abs();
            BigInteger g1 = gcd(n1, d1);
            num = n1 / g1;
            den = d1 / g1;
            return *this;
        }
    }
}

bool Rational::operator==(const Rational &r) const {
    if (num == 0 && r.num == 0) {
        return true;
    }
    if (is_positive != r.is_positive) {
        return false;
    }
    if (num == r.num && den == r.den) {
        return true;
    }
    return false;
}

bool Rational::operator!=(const Rational &r) const {
    return !(*this == r);
}

bool Rational::operator<=(const Rational &r) const {
    return ((*this < r) || (*this == r));
}

bool Rational::operator>=(const Rational &r) const {
    return ((*this > r) || (*this == r));
}

Rational &Rational::operator*=(const Rational &r) {
    is_positive = ((is_positive && r.is_positive) || (!is_positive && !r.is_positive));
    num *= r.num;
    den *= r.den;
    BigInteger g = gcd(num.big_abs(), den.big_abs());
    num /= g;
    den /= g;
    return *this;
}

Rational &Rational::operator/=(const Rational &r) {
    is_positive = ((is_positive && r.is_positive) || (!is_positive && !r.is_positive));
    num *= r.den;
    den *= r.num;
    BigInteger g = gcd(num.big_abs(), den.big_abs());
    num /= g;
    den /= g;
    return *this;
}

string Rational::toString() const {
    string s = "";
    if (!is_positive) s += "-";
    if (den != 1) {
        s += num.toString();
        s += '/';
        s += den.toString();
    } else {
        s += num.toString();
    }
    if (num == 0) {
        s.clear();
        s += '0';
    }
    return s;
}

string Rational::asDecimal(size_t precision) const {
    string s = "";
    if (!is_positive) s += "-";
    s += asDecimal_helper(num, den, precision);
    return s;
}

Rational::operator double() {
    string s = this->asDecimal(64);
    double d = std::stod(s);
    return d;
}

Rational &Rational::changessign() {
    is_positive = !is_positive;
    return *this;
}

BigInteger Rational::gcd(BigInteger a, BigInteger b) {
    if (a == 1) {
        return 1;
    }
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}


bool operator<(const Rational &a, const Rational &b) {
    if (!a.is_positive && b.is_positive) {
        return true;
    }
    if (a.is_positive && !b.is_positive) {
        return false;
    }
    if (a.is_positive && b.is_positive) {
        return a.num * b.den < b.num * a.den;
    }
    if (!a.is_positive && !b.is_positive) {
        return a.num * b.den > b.num * a.den;
    }
    return false;
}

bool operator>(const Rational &a, const Rational &b) {
    return !(a <= b);
}

Rational operator+(const Rational &r1, const Rational &r2) {
    Rational copy = r1;
    copy += r2;
    return copy;
}

Rational operator-(const Rational &r1, const Rational &r2) {
    Rational copy = r1;
    copy -= r2;
    return copy;
}

Rational operator*(const Rational &r1, const Rational &r2) {
    Rational copy = r1;
    copy *= r2;
    return copy;
}

Rational operator/(const Rational &r1, const Rational &r2) {
    Rational copy = r1;
    copy /= r2;
    return copy;
}
