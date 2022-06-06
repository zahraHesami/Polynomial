#include "Polynomial.h"
#include <cmath>

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(vector<Term> first)
{
    int size = first.size();
    Terms.resize(size);
    for (int i = 0; i < size; i++)
    {
        Terms.at(i) = first.at(i);
    }
}

Polynomial::Polynomial(float sample)
{
    Term one(sample);
    Terms.push_back(one);
}

Polynomial::Polynomial(Term first)
{
    Terms.push_back(first);
}

Polynomial &Polynomial::operator+=(const Polynomial &first)
{
    *this = *this + first;
    this->sort_poly();
    this->check_equal_powers();
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &first)
{
    *this = *this - first;
    this->sort_poly();
    this->check_equal_powers();
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &first)
{
    *this = *this * first;
    this->sort_poly();
    this->check_equal_powers();
    return *this;
}

Polynomial &Polynomial::operator=(const Polynomial &first)
{
    Terms.clear();
    for (int i = 0; i < first.Terms.size(); i++)
    {
        this->Terms.push_back(first.Terms[i]);
    }
    return *this;
}

Term Polynomial::operator[](int index) const
{
    // returning the index of chosen sentence
    float coefficient;
    int power;
    coefficient = Terms[index].get_coefficient();
    power = Terms[index].get_power();

    return Term(coefficient, power);
}

Term &Polynomial::operator[](int index)
{
    return this->Terms[index];
}

Polynomial &Polynomial::check_equal_powers()
{
    // checking if the powers of two sentences are equal
    for (int i = 0; i < Terms.size() - 1; ++i)
    {
        if (Terms[i].get_power() == Terms[i + 1].get_power())
        {
            int index = i + 1;
            Terms[i] += Terms[i + 1];
            Terms.erase(Terms.begin() + index);
        }
    }
    return *this;
}

void Polynomial::sort_poly()
{
    // function sorts the polynomial sentences based on bigger power
    for (int i = 1; i < Terms.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (Terms[i].get_power() > Terms[j].get_power() ||
                (Terms[i].get_power() == Terms[j].get_power() && Terms[i].get_coefficient() > Terms[j].get_coefficient()))
            {
                Term temp;
                temp = Terms[i];
                Terms[i] = Terms[j];
                Terms[j] = temp;
            }
        }
    }
}

bool operator>(const Polynomial &first,const Polynomial &second)
{

    bool flag = false;
    if (first[0].get_power() > second[0].get_power())
    {
        flag = true;
    }

        if (first[0].get_power() == second[0].get_power())
        {    for (int i = 1; i < first.Terms.size(); i++)
            {
            if (first[i].get_coefficient() > second[i].get_coefficient())
            {
                flag = true;
                break;
            }
             }
         }
        if (first[0].get_power() < second[0].get_power())
        {
            flag = false;
        }
    return flag;
}

bool operator<(const Polynomial &first,const Polynomial &second)
{

    bool flag = false;
    if (first[0].get_power() < second[0].get_power())
    {
        flag = true;
    }
    if (first[0].get_power() == second[0].get_power())
    {
        for (int i = 1; i < first.Terms.size(); i++)
        {
            if (first[i].get_coefficient() < second[i].get_coefficient())
            {
                flag = true;
                break;
            }
        }
    }
    if (first[0].get_power() > second[0].get_power())
    {
        flag = false;
    }
    return flag;
}

bool operator>=(const Polynomial& first, const Polynomial &second)
{
    bool flag = false;
    if(first>second)
    {
        flag=true;
    }
   if(first==second)
     {

        flag=true;
     }
   if(!(first>second))
   {
        flag = false;
    }
    return flag;
}

bool operator<=(const Polynomial &first,const Polynomial &second)
{

    bool flag = false;
    if(first<second)
    {
        flag=true;
    }
   if(first==second)
     {

        flag=true;
     }
   if(!(first<second))
   {
        flag = false;
    }


    return flag;
}

bool operator==(const Polynomial &first,const Polynomial& second)
{
    bool flag = false;
    int count=0;
    for (int i = 0; i < first.Terms.size(); i++)
    {
        if (first.Terms.size() == second.Terms.size())
        {
            if (first.Terms.at(i) != second.Terms.at(i))
            {
                return flag;
                break;
            }
            else if (first.Terms.at(i) == second.Terms.at(i))
            {
              ++ count;
            }
        }
        else
        {
            return flag;
        }
    }
    if(count==first.get_size())
    {
        return true;
    }
}

bool operator!=(const Polynomial &first,const Polynomial &second)
{
    bool flag = true;

    if (first.Terms.size() != second.Terms.size())
    {
        return flag;
    }
    else
    {
        for (int i = 0; i < first.Terms.size(); i++)
        {
            if (first.Terms.at(i) == second.Terms.at(i))
            {
                return false;
            }
        }
    }
}

Polynomial  Polynomial::operator~()
{
    Polynomial dif;
    for (int i = 0; i < Terms.size(); i++)
    {
        Term temp;
        temp = ~Terms[i]; // calculating the differencial of polynomial with ~ operator
        dif.Terms.push_back(temp);
    }
    return dif;
}

long double Polynomial::operator()(float num)
{
    long double result = 0.0;
    long double temp;
    for (int i = 0; i < Terms.size(); i++)
    {
        temp = Terms[i](num); // using operator () from cass Term
        result += temp;
    }
    return result;
}

int Polynomial:: get_size()const
{
    int size;
    size=Terms.size();
    return size;
}

std::vector<Term> Polynomial::get_Terms()

{
    return Terms;
}

int Polynomial::get_maxpower() const
{

   int maxdegree=0;
    for(int i=0;i<Terms.size();i++)
    {
        if(Terms[i].get_power()>maxdegree)

        {
           maxdegree=Terms[i].get_power();
        }

    }
  return maxdegree;

}
Polynomial& Polynomial::operator++()
{

    if(this->get_maxpower()==0)
    {
       ++ Terms[0];
    }
    return *this;
}
Polynomial&Polynomial:: operator --()
{
    if(this->get_maxpower()==0)
    {
       -- Terms[0];
    }
    return *this;
}

Polynomial Polynomial::operator++(int )
{
   Polynomial temp=*this;
   if(this->get_maxpower()==0)
   {
       ++(*this);
   }


    return temp;
}
Polynomial Polynomial::operator--(int )
{
    Polynomial temp=*this;
    if(this->get_maxpower()==0)
    {
        --(*this);
    }


     return temp;
}
