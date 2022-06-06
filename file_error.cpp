#include "file_error.h"
#include <iostream>

file_error::file_error()
{
   error="Unable to open file\n";

}

std::string file_error::get_error(){
  return error;
}
