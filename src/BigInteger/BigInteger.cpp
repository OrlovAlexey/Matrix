#include "BigInteger.h"


BigInteger::BigInteger() {
    num.clear();
    num.push_back(0);
    is_positive = true;
}

BigInteger::BigInteger(string s) {
    if (s.length() == 0) {
        num.clear();
        num.push_back(0);
        is_positive = true;
    } else {
        if (s[0] == '-') {
            is_positive = false;
            s = s.substr(1);
        } else {
            is_positive = true;
        }
        for (long long i = s.length(); i > 0; i -= 4) {
            if (i < 4)
                num.push_back(atoi(s.substr(0, i).c_str()));
            else
                num.push_back(atoi(s.substr(i - 4, 4).c_str()));
        }
    }
    this->clearzeros();
}

BigInteger::BigInteger(int x) {
    if (x < 0) {
        x = -x;
        is_positive = false;
    }
    if (x == 0) {
        num.push_back(x);
    }

    while (x > 0) {
        num.push_back(x % base);
        x /= base;
    }

    this->clearzeros();
}

BigInteger BigInteger::operator-() const {
    BigInteger copy = *this;
    copy.is_positive = !copy.is_positive;
    return copy;
}

BigInteger &BigInteger::operator+=(const BigInteger &b) {
    if (!this->is_positive) {
        if (!b.is_positive) {
            int over_digit = 0;
            size_t n1 = num.size();
            size_t n2 = b.num.size();
            for (size_t i = 0; i < max(n1, n2); ++i) {
                if (n1 <= i && i < n2) {
                    num.push_back(0);
                } // lines up the number to which we add

                int copy = num[i];
                if (n2 <= i && i < n1) {
                    num[i] = (num[i] + over_digit) % base;
                    over_digit = (copy + over_digit) / base;
                } else {
                    num[i] = (num[i] + b.num[i] + over_digit) % base;
                    over_digit = (copy + b.num[i] + over_digit) / base;
                } // summing up

                if (i == max(n1, n2) - 1 && over_digit != 0) {
                    num.push_back(over_digit);
                } // last digit
            }
            return *this;
        } else {
            return (this->changessign() -= b).changessign();
        }
    }
    else if (!b.is_positive) {
        is_positive = !is_positive;
        *this -= b;
        is_positive = !is_positive;
        return *this;
    } else {
        int over_digit = 0;
        size_t n1 = num.size();
        size_t n2 = b.num.size();
        for (size_t i = 0; i < max(n1, n2); ++i) {
            if (n1 <= i && i < n2) {
                num.push_back(0);
            } // lines up the number to which we add

            int copy = num[i];
            if (n2 <= i && i < n1) {
                num[i] = (num[i] + over_digit) % base;
                over_digit = (copy + over_digit) / base;
            } else {
                num[i] = (num[i] + b.num[i] + over_digit) % base;
                over_digit = (copy + b.num[i] + over_digit) / base;
            } // summing up

            if (i == max(n1, n2) - 1 && over_digit != 0) {
                num.push_back(over_digit);
            } // last digit
        }
        return *this;
    }
}

BigInteger &BigInteger::operator-=(const BigInteger &b) {
    if (!this->is_positive) {
        if (!b.is_positive) {
            if (*this > b) {
                BigInteger temp = *this;
                *this = b;
                return (*this -= temp).changessign();
            } else {
                bool over_digit = 0;
                size_t n1 = num.size();
                size_t n2 = b.num.size();
                for (size_t i = 0; i < max(n1, n2); ++i) {
                    if (i < n2) {
                        num[i] -= static_cast<int>(over_digit) + b.num[i];
                    } else {
                        num[i] -= static_cast<int>(over_digit);
                    } // reducing the digit

                    if (num[i] < 0) {
                        over_digit = true;
                        num[i] += base;
                    } else {
                        over_digit = false;
                    } // avoiding negative digits
                }
                this->clearzeros();
                return *this;
            }
        } else {
            return (this->changessign() += b).changessign();
        }
    } else if (!b.is_positive) {
        is_positive = !is_positive;
        *this += b;
        is_positive = !is_positive;
        return *this;
    } else {
        if (*this < b) {
            BigInteger temp = *this;
            *this = b;
            return (*this -= temp).changessign();
        } else {
            bool over_digit = 0;
            size_t n1 = num.size();
            size_t n2 = b.num.size();
            for (size_t i = 0; i < max(n1, n2); ++i) {
                if (i < n2) {
                    num[i] -= static_cast<int>(over_digit) + b.num[i];
                } else {
                    num[i] -= static_cast<int>(over_digit);
                } // reducing the digit

                if (num[i] < 0) {
                    over_digit = true;
                    num[i] += base;
                } else {
                    over_digit = false;
                } // avoiding negative digits
            }
            this->clearzeros();
            return *this;
        }
    }
}

bool BigInteger::operator==(const BigInteger &b) const {
    if (b.num.size() != num.size()) return false;
    int sz = num.size();
    for (int i = 0; i < sz; ++i) {
        if (num[i] != b.num[i]) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger &b) const {
    return !(*this == b);
}

bool BigInteger::operator<=(const BigInteger &b) const {
    return ((*this < b) || (*this == b));
}

bool BigInteger::operator>=(const BigInteger &b) const {
    return ((*this > b) || (*this == b));
}

BigInteger &BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger copy = *this;
    ++(*this);
    return copy;
}

BigInteger &BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger copy = *this;
    --(*this);
    return copy;
}

BigInteger &BigInteger::operator*=(const BigInteger &b) {
    if ((is_positive && b.is_positive) || (!is_positive && !b.is_positive)) {
        is_positive = true;
    } else {
        is_positive = false;
    } // counting the sign of the result

    BigInteger copy = *this;
    num.clear();
    num.resize(copy.num.size() + b.num.size() + 1);

    for (size_t i = 0; i < copy.num.size(); ++i) {
        long long over_digit = 0;
        for (size_t j = 0; j < b.num.size() || over_digit != 0; ++j) {
            long long result;
            if (j < b.num.size()) {
                result = num[i + j] + copy.num[i] * b.num[j] + over_digit;
            } // multiplying each digit on each digit
            else {
                result = over_digit;
            }
            over_digit = result / base; // counting the carry
            num[i + j] = result % base;
        }
    }
    clearzeros();
    return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &b) {
    if (b == 0) {
        return *this; // deleting by ZERO
    }
    if (b.num.size() > num.size()) {
        *this = 0;
        is_positive = true;
        return *this;
    }
    if ((is_positive && b.is_positive) || (!is_positive && !b.is_positive)) {
        is_positive = true;
    } else {
        is_positive = false;
    } // counting the sign of the result
    BigInteger copy = *this;
    num.clear();
    BigInteger remainder = 0;
    remainder.is_positive = true;
    num.resize(copy.num.size());

    for (int i = copy.num.size() - 1; i >= 0; --i) {
        remainder.pwr_4();
        remainder.num[0] = copy.num[i];
        remainder.clearzeros();
        int find = 0;
        int left = 0;
        int right = base;
        while (left <= right) {
            int middle = (left + right) / 2;
            BigInteger temp = (b * middle);
            temp.is_positive = true;
            if (temp <= remainder) {
                find = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            } // finding the number less or equal than the partial residue
        }
        num[i] = find % base;
        remainder -= (b >= 0 ? (b * (find)) : -(b * (find)));
    } // long division (деление столбиком)
    clearzeros();
    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &b) {
    BigInteger copy = *this;
    num.clear();
    BigInteger remainder = 0;
    remainder.is_positive = true;
    num.resize(copy.num.size());

    for (int i = copy.num.size() - 1; i >= 0; --i) {
        remainder.pwr_4();
        remainder.num[0] = copy.num[i];
        remainder.clearzeros();
        int find = 0;
        int left = 0;
        int right = base;
        while (left <= right) {
            int middle = (left + right) / 2;
            BigInteger temp = (b * middle);
            temp.is_positive = true;
            if (temp <= remainder) {
                find = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            } // finding the number less or equal than the partial residue
        }
        num[i] = find % base;
        remainder -= (b >= 0 ? (b * (find)) : -(b * (find)));
    }
    *this = remainder;
    clearzeros();
    return *this;
}

string BigInteger::toString() const {
    string s = "";
    if (!is_positive) {
        s += "-";
    }
    if (num.size() == 1 && num[0] == 0) {
        s.clear();
    }
    if (num.size() != 0) {
        s += std::to_string(num[num.size() - 1]);
    }
    if (num.size() > 1) {
        for (int i = num.size() - 2; i >= 0; --i) {
            if (num[i] < 10) {
                s += "000";
            } else if (num[i] < 100) {
                s += "00";
            } else if (num[i] < 1000) {
                s += "0";
            }
            s += std::to_string(num[i]);
        }
    }
    if (num.size() == 0) {
        s.clear();
    }
    return s;
}

BigInteger::operator bool() {
    return (*this != (BigInteger) 0);
}

BigInteger &BigInteger::changessign() {
    is_positive = !is_positive;
    return *this;
}

void BigInteger::clearzeros() {
    while (num.size() > 1 && num.back() == 0) {
        num.pop_back();
    }
    if (num.size() == 1 && num[0] == 0) {
        is_positive = true;
    }
}

void BigInteger::pwr_4() {
    if (num.size() == 0) {
        num.push_back(0);
    }
    num.push_back(num[num.size() - 1]);
    for (int j = num.size() - 2; j > 0; --j) {
        num[j] = num[j - 1];
    }
    num[0] = 0;
}

BigInteger BigInteger::operator*(int a) const {
    BigInteger copy = *this;
    copy.num.clear();
    copy.num.resize(num.size() + 1);
    int over_digit = 0;
    for (int i = 0; i < (int) num.size() || over_digit != 0; ++i) {
        int temp;
        if (i < (int) num.size()) {
            temp = num[i] * a + over_digit;
        } else {
            temp = over_digit;
        }
        over_digit = temp / base;
        copy.num[i] = temp % base;
    }
    copy.clearzeros();
    return copy;
}


istream &operator>>(istream &in, BigInteger &b) {
    string s;
    in >> s;
    b.num.clear();
    if (s.length() == 0) {
        b.is_positive = true;
    } else {
        if (s[0] == '-') {
            b.is_positive = false;
            s = s.substr(1);
        } else {
            b.is_positive = true;
        }
        for (long long i = s.length(); i > 0; i -= 4) {
            if (i < 4) {
                b.num.push_back(std::stoi(s.substr(0, i)));
            } else {
                b.num.push_back(std::stoi(s.substr(i - 4, 4)));
            }
        }
    }
    b.clearzeros();
    return in;
}

ostream &operator<<(ostream &out, const BigInteger &b) {
    out << b.toString();
    return out;
}

bool operator<(const BigInteger &a, const BigInteger &b) {
    if (!a.is_positive && b.is_positive) {
        return true;
    }
    if (a.is_positive && !b.is_positive) {
        return false;
    }
    if (a.is_positive && b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() < b.num.size();
    }
    if (!a.is_positive && !b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() > b.num.size();
    }
    for (int i = a.num.size() - 1; i >= 0; --i) {
        if ((a.num[i] != b.num[i]) && (a.is_positive && b.is_positive)) {
            return a.num[i] < b.num[i];
        } else if ((a.num[i] != b.num[i]) && (!a.is_positive && !b.is_positive)) {
            return a.num[i] > b.num[i];
        }
    }
    return false;
}

bool operator>(const BigInteger &a, const BigInteger &b) {
    if (a.is_positive && !b.is_positive) {
        return true;
    }
    if (!a.is_positive && b.is_positive) {
        return false;
    }
    if (a.is_positive && b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() > b.num.size();
    }
    if (!a.is_positive && !b.is_positive && (a.num.size() != b.num.size())) {
        return a.num.size() < b.num.size();
    }
    for (int i = a.num.size() - 1; i >= 0; --i) {
        if ((a.num[i] != b.num[i]) && (a.is_positive && b.is_positive)) {
            return a.num[i] > b.num[i];
        } else if ((a.num[i] != b.num[i]) && (!a.is_positive && !b.is_positive)) {
            return a.num[i] < b.num[i];
        }
    }
    return false;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b) {
    BigInteger copy = a;
    copy += b;
    return copy;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b) {
    BigInteger copy = a;
    copy -= b;
    return copy;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
    BigInteger copy = a;
    copy *= b;
    return copy;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
    BigInteger copy = a;
    copy /= b;
    return copy;
}

BigInteger operator%(const BigInteger &a, const BigInteger &b) {
    BigInteger copy = a;
    copy %= b;
    return copy;
}


BigInteger operator ""_bi(const char *x) {
    return BigInteger(x);
}

BigInteger operator ""_bi(unsigned long long x) {
    return BigInteger(x);
}

BigInteger operator ""_bi(char x) {
    return BigInteger(x);
}

BigInteger pow(BigInteger a, long long degree) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 != 0) {
        return pow(a, degree - 1) * a;
    } else {
        BigInteger b = pow(a, degree / 2);
        return (b * b);
    }
}

string asDecimal_helper(const BigInteger &a, const BigInteger &b, long long precision) {
    BigInteger copy;
    copy = a / b;
    copy.is_positive = true;
    BigInteger remainder;
    remainder = (a * pow(BigInteger(10), precision)) / b;
    remainder.is_positive = true;

    string s = "";
    s += copy.toString();
    s += '.';
    int n = remainder.num[remainder.num.size() - 1];
    if (n < 10) {
        s += "000";
    } else if (n < 100) {
        s += "00";
    } else if (n < 1000) {
        s += "0";
    }
    s += remainder.toString();
    if (precision == 0) s.pop_back();
    return s;
}