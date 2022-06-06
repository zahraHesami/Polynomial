#ifndef FILE_ERROR_H
#define FILE_ERROR_H


#include <iostream>

class file_error
{
public:
    file_error();
    std::  string get_error();
private:
     std:: string error;
};

#endif // FILE_ERROR_H
