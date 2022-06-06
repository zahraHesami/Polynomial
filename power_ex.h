#ifndef POWER_EX_H
#define POWER_EX_H


#include <iostream>
class power_ex
{
public:
    power_ex();
    std::string get_error();
  private:
    std::string error;
};

#endif // POWER_EX_H
