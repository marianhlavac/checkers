/**
 * @file    exceptions.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototypes of exception classes
 *
 * This file contains prototypes of all exception classes
 */

#ifndef CHECKERS_EXCEPTIONS_H
#define CHECKERS_EXCEPTIONS_H

#include <stdexcept>

/**
 * Exception: Error parsing console arguments
 */
class ConsoleParsingErrorException : public std::runtime_error
{
public:
    /** Default constructor */
    ConsoleParsingErrorException( const std::string &reason );
};

/**
 * Exception: Singleton instantiated more than once
 */
class SingletonInstantiationException : public std::exception
{
public:
    /** Method returns reason of exception */
    virtual const char* what() const throw();
};

/**
 * Exception: Creating game failed
 */
class CreatingGameFailedException : public std::runtime_error
{
public:
    /** Default constructor */
    CreatingGameFailedException( const std::string &reason );
};


#endif //CHECKERS_EXCEPTIONS_H
