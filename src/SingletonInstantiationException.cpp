//
// Created by Marián on 11. 5. 2015.
//

#include "SingletonInstantiationException.h"

const char* SingletonInstantiationException::what() const throw()
{
    return "You cannot instantiate a singleton.";
}
