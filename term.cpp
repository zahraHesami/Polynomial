#include <cstring>
#include <cmath>
#include "divide_zero.h"
#include "power_ex.h"
#include "Term.h"
Term::Term()
{
}

Term::Term(float _coefficient, int _power)
{
    coefficient = _coefficient;
    power = _power;
}

Term::Term(float sample)
{
    coefficient = sample;
    power = 0;
}

bool check(const Term &one, const Term &two)
{
    // this function checks if the power of two terms are equal
    if (one.get_power() == 0 || two.get_power() == 0)
    {
        return (one.get_power() == two.get_power());
    }
    else
    {
        return true;
    }
}

void Term::set_term(string temp)
{
    // thi function sets the coefficient and power of a term and turns string to int
    int index_x = temp.find('x');
    int index_power = temp.find('^');
    if (index_x == 0 && index_power == -1)
    {
        this->coefficient = 1;
        this->power = 1;
    }
    else if (index_x >= 0 && index_power == -1)
    {
        if (temp[0] == '-' && index_x == 1)
        {
            this->coefficient = -1;
            this->power = 1;
        }
        else
        {
            this->coefficient = stof(temp.substr(0, index_x));
            this->power = 1;
        }
    }
    else if (index_x >= 0 && index_power >= 0)
    {
        if (index_x == 0)
        {
            this->coefficient = 1;
            this->power = stoi(temp.substr(index_power + 1, temp.size()));
        }
        else if (temp[0] == '-' && index_x == 1)
        {
            this->coefficient = -1;
            this->power = stoi(temp.substr(index_power + 1, temp.size()));
        }
        else if (index_x >= 1)
        {
            this->coefficient = stof(temp.substr(0, index_x));
            this->power = stoi(temp.substr(index_power + 1, temp.size()));
        }
    }
    else if (index_x == -1 && index_power == -1)
    {
        this->coefficient = stof(temp.substr(0, temp.size()));
        this->power = 0;
    }
}

Term Term::operator+(const Term &sum)
{
    if (power != sum.power)
    {
        throw power_ex(); // throwing exception if powers are not equal
    }
    return Term(coefficient + sum.coefficient, power);
}

Term Term::operator+(float number)
{
    if (power != 0)
    {
        throw power_ex();
    }
    return Term(coefficient + number, power);
}

Term Term::operator-(const Term &one)
{
    if (power != one.power)
    {
        throw power_ex();
    }
    return Term(coefficient - one.coefficient, power);
}

Term Term ::operator-(float number)
{
    if (power != 0)
    {
        throw power_ex();
    }
    return Term(coefficient - number, power);
}

Term Term::operator*(const Term &one)
{
    return Term(coefficient * one.coefficient, power + one.power);
}

Term Term::operator*(float number)
{
    return Term(coefficient * number, power);
}

Term Term::operator/(const Term &one)
{
    if (one.coefficient == 0)
    {
        throw Divide_zero(); // throwing exception if denominator is zero
    }
    return Term(coefficient / one.coefficient, power - one.power);
}

Term Term ::operator/(float number)
{
    if (number == 0)
    {
        throw Divide_zero();
    }
    return Term(coefficient / number, power);
}

Term &Term::operator+=(const Term &one)
{
    if (power != one.power)
    {
        throw power_ex();
    }
    coefficient += one.coefficient;
    return *this;
}
Term &Term::operator-=(const Term &one)
{
    if (power != one.power)
    {
        throw power_ex();
    }
    coefficient -= one.coefficient;
    return *this;
}

Term &Term::operator*=(const Term &one)
{
    coefficient *= one.coefficient;
    power += one.power;
    return *this;
}

Term &Term::operator/=(const Term &one)
{
    if (one.coefficient == 0)
    {
        throw Divide_zero();
    }
    coefficient /= one.coefficient;
    power -= one.power;
    return *this;
}

Term &Term::operator=(const Term &one)
{
    this->coefficient = one.coefficient;
    this->power = one.power;
    return *this;
}

bool operator<(const Term &one, const Term &two)
{
    bool flag = false;
    if (!check(one, two))
    {
        throw power_ex();
    }

    else
    {
        if (one.power < two.power)
        {
            flag = true;
        }
        else if (one.power == two.power)
        {
            if (one.coefficient < two.coefficient)
            {
                flag = true;
            }
            if (one.coefficient > two.coefficient)
            {
                flag = false;
            }
        }
        else if (one.power > two.power)
        {
            flag = false;
        }
    }

    return flag;
}

bool operator>(const Term &one, const Term &two)
{
    bool flag;
    if (!check(one, two))
    {
        throw power_ex();
    }
    else
    {
        if (one.power > two.power)
        {
            flag = true;
        }
        else if (one.power == two.power)
        {
            if (one.coefficient > two.coefficient)
            {
                flag = true;
            }
            if (one.coefficient < two.coefficient)
            {
                flag = false;
            }
        }
        else if (one.power < two.power)
        {
            flag = false;
        }
    }

    return flag;
}

bool operator==(const Term &one, const Term &two)
{
    return (one.coefficient == two.coefficient && one.power == two.power);
}

bool operator>=(const Term &one, const Term &two)
{
    bool flag;
    if (!check(one, two))
    {
        throw power_ex();
    }
    else
    {
        if (one.power > two.power)
        {
            flag = true;
        }
        else if (one.power == two.power)
        {
            if (one.coefficient >= two.coefficient)
            {
                flag = true;
            }
            if (one.coefficient < two.coefficient)
            {
                flag = false;
            }
        }
        if (one.power < two.power)
        {
            flag = false;
        }
    }

    return flag;
}

bool operator<=(const Term &one, const Term &two)
{
    bool flag;
    if (!check(one, two))
    {
        throw power_ex();
    }
    else
    {
        if (one.power < two.power)
        {
            flag = true;
        }
        else if (one.power == two.power)
        {
            if (one.coefficient <= two.coefficient)
            {
                flag = true;
            }
            if (one.coefficient > two.coefficient)
            {
                flag = false;
            }
        }
        if (one.power > two.power)
        {
            flag = false;
        }
    }

    return flag;
}

bool operator!=(const Term &one, const Term &two)
{
    return (one.coefficient != two.coefficient || one.power != two.power);
}

Term Term::operator~()
{
    // this operator shows the differencial of term
    if (power == 0)
    {
        return Term(0, 0);
    }
    else if (power == 1)
    {
        return Term(coefficient, 0);
    }
    else if (power > 1)
    {
        return Term(coefficient * power, power - 1);
    }
}

Term &Term::operator++()
{
    if (power != 0)
    {
        throw power_ex();
    }
    ++coefficient;
    return *this;
}

Term &Term::operator--()
{
    if (power != 0)
    {
        throw power_ex();
    }
    --coefficient;
    return *this;
}

Term Term::operator++(int)
{
    Term temp(coefficient, power);
    if (power != 0)
    {
        throw power_ex();
    }

    ++(*this);
    return temp;
}

Term Term::operator--(int)
{
    Term temp(coefficient, power);
    if (power != 0)
    {
        throw power_ex();
    }
    --(*this);
    return temp;
}

long double Term::operator()(float number)
{
    long double result = 0.0;
    long double temp = pow(number, power); // operating of the term for a specific amount
    result = coefficient * temp;

    return result;
}

float Term::get_coefficient() const
{
    return coefficient;
}

int Term::get_power() const
{
    return power;
}
