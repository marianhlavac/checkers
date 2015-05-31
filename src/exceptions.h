//
// Created by majko on 31.5.15.
//

#ifndef CHECKERS_EXCEPTIONS_H
#define CHECKERS_EXCEPTIONS_H

#include <stdexcept>

class ConsoleParsingErrorException : public std::runtime_error
{
public:
    ConsoleParsingErrorException( const std::string &reason );
};

class SingletonInstantiationException : public std::exception
{
    virtual const char* what() const throw();
};

class CreatingGameFailedException : public std::runtime_error
{
public:
    CreatingGameFailedException( const std::string &reason );
};


#endif //CHECKERS_EXCEPTIONS_H
