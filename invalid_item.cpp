#include "Invalid_item.h"
#include <iostream>

invalid_item::invalid_item()
{
  error="Invalid value selected!!!";
}
std::string invalid_item::get_error()
{
    return error;
}
