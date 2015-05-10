//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_SINGLETONINSTANTIATIONEXCEPTION_H
#define PA2_LS2015_SEMESTRALKA_SINGLETONINSTANTIATIONEXCEPTION_H

#include <exception>

class SingletonInstantiationException : public std::exception
{
    virtual const char* what() const throw();
};

#endif //PA2_LS2015_SEMESTRALKA_SINGLETONINSTANTIATIONEXCEPTION_H
