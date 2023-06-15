#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::max;
using std::min;
using std::ostream;
using std::istream;

class BigInteger{
private:
    static const int base = 10000;
    vector<int> num;
    bool is_positive = true;

public:
    BigInteger();
    BigInteger(string s);
    BigInteger(int x);

    BigInteger operator- () const;
    BigInteger& operator+= (const BigInteger& b);
    BigInteger& operator-= (const BigInteger& b);

    bool operator== (const BigInteger& b) const;
    bool operator!= (const BigInteger& b) const;
    bool operator<= (const BigInteger& b) const;
    bool operator>= (const BigInteger& b) const;

    BigInteger& operator++ ();
    BigInteger operator++ (int);
    BigInteger& operator-- ();
    BigInteger operator-- (int);

    BigInteger& operator*= (const BigInteger& b);
    BigInteger& operator/= (const BigInteger& b);
    BigInteger& operator%= (const BigInteger& b);

    string toString() const;
    explicit operator bool();

    friend bool operator< (const BigInteger&, const BigInteger&); // bad implementation
    friend bool operator> (const BigInteger&, const BigInteger&);
    friend istream& operator>> (istream&, BigInteger&);
    friend string asDecimal_helper(const BigInteger&, const BigInteger&, long long);

private:
    BigInteger& changessign(); // unary minus without creating a copy
    void clearzeros(); // deletes zeros in the beginning of the number
    void pwr_4(); // multiplying on base of bigInt (left shift)
    BigInteger operator* (int a) const; // for convenience

public:
    bool sgn() const {
        return is_positive;
    } // returns the sign of the bigInt

    BigInteger big_abs() const {
        BigInteger copy = *this;
        copy.is_positive = true;
        return copy;
    } // bigInteger absolute value
};

istream& operator>> (istream& in, BigInteger& b);
ostream& operator<< (ostream& out, const BigInteger& b);

bool operator< (const BigInteger& a, const BigInteger& b);
bool operator> (const BigInteger& a, const BigInteger& b);

BigInteger operator+ (const BigInteger& a, const BigInteger& b);
BigInteger operator- (const BigInteger& a, const BigInteger& b);
BigInteger operator* (const BigInteger& a, const BigInteger& b);
BigInteger operator/ (const BigInteger& a, const BigInteger& b);
BigInteger operator% (const BigInteger& a, const BigInteger& b);

BigInteger operator""_bi(const char* x);
BigInteger operator""_bi(unsigned long long x);
BigInteger operator""_bi(char x);

BigInteger pow(BigInteger a, long long degree);
string asDecimal_helper(const BigInteger& a, const BigInteger& b, long long precision);

