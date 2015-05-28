//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_SINGLETONINSTANTIATIONEXCEPTION_H
#define CHECKERS_SINGLETONINSTANTIATIONEXCEPTION_H

#include <exception>

class SingletonInstantiationException : public std::exception
{
    virtual const char* what() const throw();
};

#endif //CHECKERS_SINGLETONINSTANTIATIONEXCEPTION_H
