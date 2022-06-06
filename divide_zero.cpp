#include "Divide_zero.h"
#include <iostream>

Divide_zero::Divide_zero()
{
  error="You can't divide the Term by zero";
}
std::string Divide_zero:: get_error(){
    return error;
}
