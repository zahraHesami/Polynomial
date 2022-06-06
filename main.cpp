#include <iostream>
#include<vector>
#include<fstream>
#include "Invalid_item.h"
#include "divide_zero.h"
#include "Polynomial.h"
#include"Term.h"
#include "file_error.h"
#include "power_ex.h"

using namespace std;

istream & operator >>(istream &input, Term & one);

Term operator+(const float number, const Term& one);

Term operator-(const float number, const Term& one);

Term operator *(const float number,const Term& one);

Term operator/(const float number,const Term &one);

ostream &operator<<(ostream &output,const Term &one);


istream &operator >>(istream &input, Polynomial& first);

ostream &operator<<(ostream &output,const  Polynomial&one);

Polynomial operator*(const Polynomial &first,const Polynomial &second);

Polynomial operator+(const Polynomial &first,const Polynomial &second);

Polynomial operator-(const Polynomial &first,const Polynomial &second);

vector<Term>set_terms(string temp);

void save_textfile(Polynomial first);

Polynomial load_textfile(string namefile);

Polynomial load_binaryfile(string name);

void add_Poly(Polynomial &  currentPolynomial);

void subtract_poly(Polynomial &  currentPolynomial);

void multiply_poly(Polynomial &  currentPolynomial);

void derivative_poly(Polynomial &  currentPolynomial);

void find_degree(const Polynomial & currentPolynomial);

void find_valuex( Polynomial  currentPolynomial);

void compare_poly(Polynomial  currentPolynomial);

void text_file();

void binary_file();

int print_mainmenu();

int print_addmenu();

void switch_addmenu(Polynomial temp );

int main()
{

    bool showmenu=true;
    Polynomial temp=0;
    while (showmenu)
    {
        try
        {
            int itemmenu=print_mainmenu();
            switch (itemmenu)
            {
            case 1:
        switch_addmenu(temp);
                break;
            case 2:
               text_file();
                break;
            case 3:
             binary_file();
                break;
            case 4:
               showmenu=false;
                break;
            default:
                break;
            }
        }
        catch (invalid_item error)
        {
          cout<<error.get_error();
        }

    }
    return 0;
}

istream & operator >>(istream &input, Term & one){
    string ch;

    input>>ch;
    one.set_term(ch);

     return input;
}

Term operator+(const float number, const Term& one)
{
    if(one.get_power()!=0)
    {
        throw power_ex();
    }
    return  Term(one.get_coefficient()+number,one.get_power());
}

Term operator-(const float number, const Term& one)
{

    if(one.get_power()!=0)
    {
        throw power_ex();
    }
    return  Term(one.get_coefficient()-number,one.get_power());


}

Term operator *(const float number,const Term& one)
{
    return Term(one.get_coefficient()*number,one.get_power());
}

Term operator/(const float number,const Term &one)
{
    if(one.get_coefficient()==0)
    {
       throw Divide_zero();
    }
     return Term(number/one.get_coefficient(),one.get_power());
}

ostream &operator<<(ostream &output,const Term &one)
{
    if(one.coefficient==1)
    {
        if(one.power==1)
        {
            output<<"x";
        }
        else if(one.power==0)
            {
             output<<one.coefficient;
            }
        else
        {
            output<<"x^"<<one.power;
        }

    }
    else if(one.coefficient!=1 && one.power==1)
        {
            output<<one.coefficient;
            output<<"x";
        }
    else if(one.coefficient!=1 && (one.power<0 || one.power>1))
        {
        output<<one.coefficient;
        output<<"x^"<<one.power;
        }
    else if(one.power==0)
        {
         output<<one.coefficient;

        }
return output;
}

istream &operator >>(istream &input, Polynomial& first){
    string temp;
    string temp2;
    vector<int> index;
    input>>temp;
        for(int i=0;i<temp.size();i++)
    {
        if(temp[i]=='+'||temp[i]=='-')
        {
            int index2;
            index2=i;
           index.push_back(index2);
        }
    }
        for(int i=0;i<index.size()-1;i++)
        {
            Term sample;
          temp2=temp.substr(index.at(i),index.at(i+1));
          sample.set_term(temp2);
          first.Terms.push_back(sample);
        }

    return input;
}

ostream &operator<<(ostream &output,const  Polynomial&one)
{
    output<<one.Terms[0];
   for(int i=1;i<one.get_size();i++)
   {

      if(one.Terms[i].get_coefficient()>0)
      {
          output<<"+"<<one.Terms[i];
      }
      if(one.Terms[i].get_coefficient()<0)
      {
          output<<one.Terms[i];
      }
   }
   return output;
}

Polynomial operator*(const Polynomial &first,const Polynomial &second)
{
    Polynomial sample;

    for(int i=0;i<first.get_size();i++)
    {
        for(int j=0;j<second.get_size();j++)
        {
           Term temp1,temp;
           Term temp2;
           temp1=first.Terms[i];
           temp2=second.Terms[j];
           temp=temp1*temp2;
            sample.Terms.push_back(temp);
        }
    }
    sample.sort_poly();
    sample.check_equal_powers();
    return sample;
}

Polynomial operator+(const Polynomial &first,const Polynomial &second)
{
    Polynomial temp;
    temp=first;
    for(int i=0;i<second.get_size();i++)
    {
        temp.Terms.push_back(second.Terms[i]);
    }
    temp.sort_poly();
    temp.check_equal_powers();
       return temp;
}

Polynomial operator-(const Polynomial &first,const Polynomial &second)
{
    Polynomial temp;
    temp=first;
    for(int i=0;i<second.get_size();i++)
    {
        int power;
        float coeffitient;
        power=second.Terms[i].get_power();
        coeffitient=-1*second.Terms[i].get_coefficient();
        Term one(coeffitient,power);
        temp.Terms.push_back(one);
    }
    temp.sort_poly();
    temp.check_equal_powers();
       return temp;
}

vector<Term>set_terms(string temp)
{
    string temp2;
    vector<int> index;
   vector<Term> Terms;
        for(int i=0;i<temp.size();i++)
    {
        if(temp[i]=='+'||temp[i]=='-')
        {
            int index2;
            index2=i;
           index.push_back(index2);
        }
    }
        for(int i=0;i<index.size()-1;i++)
        {
            Term sample;
          temp2=temp.substr(index.at(i),index.at(i+1));
          sample.set_term(temp2);
          Terms.push_back(sample);
        }
        return Terms;
}

void save_textfile(Polynomial first)
{
    string namefile;
    cout<<"\nenter file name \n";
    cin>>namefile;
    first.sort_poly();
    first.check_equal_powers();
    namefile+=".txt";

    ofstream myfile(namefile,ios::trunc);
    if(myfile.is_open())
    {
       if (first.get_Terms()[1].get_coefficient()>0)
        {
           myfile<<"+";
           myfile<<first;
           myfile<<"+";
         }
       else
        {
          myfile<<first;
          myfile<<"+";
        }
       myfile.close();
   }
    else
    {
        cout<<"Unable to open file\n";
    }
}

Polynomial load_textfile(string namefile)
{
    string temp;

     vector<Term> Terms;
     namefile+=".txt";
     ifstream myfile;
     myfile.open(namefile,ios::in);
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            myfile>>temp;
            Terms=set_terms(temp);

        }

        myfile.close();
    }
   if(myfile.fail())
    {

        throw file_error();
    }
    Polynomial currentPolynomial(Terms);
return  currentPolynomial;
}

void save_binaryfile(Polynomial first)
{
    ofstream outfile;
    string namefile;
    cout<<"\nenter file name \n";
    cin>>namefile;
    namefile+=".dat";
    outfile.open(namefile,ios::binary|ios::trunc);
    for(int i=0;i<first.get_size();++i)
    {
        outfile.write((char*)&first.get_Terms()[i],sizeof(first.get_Terms()[i]));
    }

    outfile.close();
}

Polynomial load_binaryfile(string name)
{
    ifstream infile;
     Term temp;
    vector<Term> temp2;
    name+=".dat";
    infile.open(name,ios::binary);

    if(infile.is_open())
    {
        while(infile.read((char*)&temp,sizeof(temp)))
        {
           temp2.push_back(temp);
        }

        infile.close();
    }

   if(infile.fail())
    {
        throw file_error();
    }

     Polynomial currentPolynomial(temp2);

    return currentPolynomial;
}

int print_mainmenu()
{
     int itemMenu;
     cout<<"1- New Polynomial \n";
     cout<<"2- Load from text file \n";
     cout<<"3- Load from binary file\n";
     cout<<"4- Quit \n";
    cin>>itemMenu;
    if(itemMenu>4 || itemMenu<=0)
    {
        throw invalid_item();
    }
     return itemMenu;
}

int print_addmenu()
{
    int itemMenu;
    cout<<"1- Add \n";
    cout<<"2- Subtract\n";
    cout<<"3- Multiply\n";
    cout<<"4- Derivative\n";
    cout<<"5- Find Degree\n";
    cout<<"6- Find Value for specific x\n";
    cout<<"7- Compare\n";
    cout<<"8- Save to a text file\n";
    cout<<"9- Save to a binary file\n";
    cout<<"10- Back to Main Menu\n";
   cin>>itemMenu;
   if(itemMenu>10 || itemMenu<=0)
   {
       throw invalid_item();
   }
    return itemMenu;
}

void switch_addmenu(Polynomial temp)
{

   Polynomial currentPolynomial=temp;

    bool showmenu=true;
    while (showmenu)
    {
        cout<<"Current Polynomial ="<<currentPolynomial<<'\n';
         int itemMenu=print_addmenu();

        if(itemMenu==1)
        {
          add_Poly(currentPolynomial);

        }
        else if(itemMenu==2)
        {
           subtract_poly(currentPolynomial);

        }
        else if(itemMenu==3)
        {
           multiply_poly(currentPolynomial);
        }

        else if(itemMenu==4)
        {
            derivative_poly(currentPolynomial);
        }

        else if(itemMenu==5)
        {
           find_degree(currentPolynomial);
        }
        else if(itemMenu==6)
        {
           find_valuex(currentPolynomial);
        }

        else if(itemMenu==7)
        {
           compare_poly(currentPolynomial);
        }

        else if(itemMenu==8)
        {
             save_textfile(currentPolynomial);
        }

        else if(itemMenu==9)
        {
           save_binaryfile(currentPolynomial);
        }

        else if(itemMenu==10)
        {
           showmenu=false;
        }
    }
}

void add_Poly(Polynomial &  currentPolynomial)
{
  string temp;
  vector<Term>Terms;
  cout<<"Enter Polynomial\n";
  cin>>temp;
  Terms=set_terms(temp);
  Polynomial other(Terms);
  currentPolynomial=currentPolynomial+other;
  currentPolynomial.sort_poly();
  currentPolynomial.check_equal_powers();
}

void subtract_poly(Polynomial &  currentPolynomial)
{
    string temp;
    vector<Term>Terms;
    cout<<"Enter Polynomial\n";
    cin>>temp;
    Terms=set_terms(temp);
    Polynomial other(Terms);
    other.sort_poly();
    other.check_equal_powers();
    currentPolynomial=(currentPolynomial-other);
     currentPolynomial.sort_poly();
    currentPolynomial.check_equal_powers();
}

void multiply_poly(Polynomial &  currentPolynomial)
{
    string temp;
    vector<Term>Terms;
    cout<<"Enter Polynomial\n";
    cin>>temp;
    Terms=set_terms(temp);
    Polynomial other(Terms);
    other.sort_poly();
    other.check_equal_powers();
    currentPolynomial=(currentPolynomial*other);
    currentPolynomial.sort_poly();
    currentPolynomial.check_equal_powers();
}

void derivative_poly(Polynomial &  currentPolynomial)
{
   currentPolynomial=~currentPolynomial;
}

void find_degree(const Polynomial & currentPolynomial)
{
   int degree=currentPolynomial.get_maxpower();
   cout<<"Polynomial degree ="<<degree<<'\n';
}

void find_valuex(Polynomial currentPolynomial)
{
    long double result=0.0;
     float number;
     cout<<"Enter number\n";
     cin>>number;
    result=currentPolynomial(number);
    cout<<"Value for  (x="<<number<<") :"<<result<<'\n';
}

void compare_poly(Polynomial  currentPolynomial)
{
    string temp;
    vector<Term>Terms;
    string flag;
    cout<<"Enter Polynomial\n";
    cin>>temp;
    Terms=set_terms(temp);
    Polynomial other(Terms);
    other.sort_poly();
    other.check_equal_powers();
    currentPolynomial.sort_poly();
    currentPolynomial.check_equal_powers();
    cout<<"Comparing Current_Polynomial with Other_Polynomial \n";

    cout<<"Current_Polynomial > Other_Polynomial:";
    (currentPolynomial>other) ?  cout<<"true\n":cout<<"false\n";

    cout<<"Current_Polynomial >= Other_Polynomial:";
    (currentPolynomial>=other)?  cout<<"true\n":cout<<"false\n";

     cout<<"Current_Polynomial < Other_Polynomial:";
     (currentPolynomial<other) ?  cout<<"true\n":cout<<"false\n";


    cout<<"Current_Polynomial <= Other_Polynomial:";
    (currentPolynomial<=other)? cout<<"true\n":cout<<"false\n";


     cout<<"Current_Polynomial == Other_Polynomial:";
     (currentPolynomial==other)? cout<<"true\n":cout<<"false\n";


}


void text_file()
{
  Polynomial temp;
    string namefile;
    cout<<"Enter namefile\n";
    cin>> namefile;
    try{
    temp=load_textfile(namefile);
    switch_addmenu(temp);
    }
   catch (file_error error)
    {
        cout<< error.get_error();
    }
}

void binary_file()
{
    Polynomial temp;
      string namefile;
      cout<<"Enter namefile\n";
      cin>> namefile;
      try{
      temp=load_binaryfile(namefile);
      switch_addmenu(temp);
      }
      catch(file_error error)
      {
       cout<< error.get_error();
      }
}












