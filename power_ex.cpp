#include "power_ex.h"
#include <iostream>

power_ex::power_ex()
{
    error="Term power is not equal";
}


std::string power_ex::get_error(){
  return error;
}
