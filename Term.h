#ifndef TERM_H
#define TERM_H
#include<iostream>
using namespace std;
class Term
{
public:
    Term();
    Term(float _coefficient,int _power);
    Term(float sample);
    void set_term(string temp);
    Term operator+(const Term& sum);
    Term operator+(float number);
    Term operator-(const Term & one);
    Term operator-(float number);
    Term operator*(const Term& one);
    Term operator*(float number);
    Term operator /(const Term& one);
    Term operator /(float number);
    Term& operator+=(const Term &one);
    Term&operator-=(const Term &one);
    Term& operator*=(const Term &one);
    Term& operator/=(const Term &one);
    Term& operator=(const Term& one);
    Term  operator ~();
    Term& operator++();
    Term& operator --();
    Term operator++(int );
    Term operator--(int );
    long double operator()(float number);
    friend  istream &operator >>(istream &in,Term &);
    friend  ostream &operator<<(ostream &output,const Term &one);
    friend  bool operator<(const Term &one,const Term &two);
    friend  bool operator>(const Term&one,const Term &two);
    friend  bool operator==(const Term &one,const Term &two);
    friend  bool operator>=(const Term &one,const Term &two);
    friend  bool operator<=(const Term &one,const Term &two);
    friend  bool operator!=(const Term & one,const Term &two);
    int get_power() const;
    float get_coefficient() const;
private:
    float  coefficient;
    int power;
};

#endif // TERM_H
