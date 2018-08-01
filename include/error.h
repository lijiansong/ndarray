#ifndef ERROR_H
#define ERROR_H

#include <exception>

class OutOfRangeException : public std::exception{};
class InvalidInitialListSizeException : public std::exception{};

#endif // ERROR_H
