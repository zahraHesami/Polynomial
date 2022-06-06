#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include"Term.h"
#include <vector>

class Polynomial
{
public:
    Polynomial();
        Polynomial(vector<Term> first);
        Polynomial(Term first);
        Polynomial(float sample);
        int  get_size() const;
        vector<Term>get_Terms();
        int get_maxpower() const;
        Polynomial &check_equal_powers();
        Polynomial &operator+=(const Polynomial &first);
        Polynomial &operator-=(const Polynomial &first);
        Polynomial &operator*=(const Polynomial &first);
        Polynomial &operator/=(const Polynomial &first);
        Polynomial &operator=(const Polynomial &first);
        friend istream &operator>>(istream &in, Polynomial &);
        friend ostream &operator<<(ostream &output, const Polynomial &one);
        friend Polynomial operator*(const Polynomial &first, const Polynomial &second);
        friend Polynomial operator+(const Polynomial &first, const Polynomial &second);
        friend Polynomial operator-(const Polynomial &first, const Polynomial &second);
        friend bool operator>(const Polynomial &first, const Polynomial &second);
        friend bool operator<(const Polynomial &first, const Polynomial &second);
        friend bool operator>=(const Polynomial &first, const Polynomial &second);
        friend bool operator<=(const Polynomial &first, const Polynomial &second);
        friend bool operator==(const Polynomial &first, const Polynomial &second);
        friend bool operator!=(const Polynomial &first, const Polynomial &second);
        Polynomial operator~();
        long double operator()(float num);
        Term operator[](int index) const;
        Term &operator[](int index);
        void sort_poly();
private:
    vector<Term>Terms;
};

#endif // POLYNOMIAL_H
