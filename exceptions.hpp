#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <exception>

class Nullptr_din_array_err : public std::exception{    //Dynamic array received nullpointer as input
public:
  const char *what() const noexcept { return "Received NULLPTR in dynamic array" ; }

};

class Nullptr_stat_int_err : public std::exception{
public:
    const char *what() const noexcept { return "Recieved illegal NULPTR at reading" ;}

};



#endif // EXCEPTIONS_HPP
