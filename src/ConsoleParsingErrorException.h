//
// Created by Marián on 24. 5. 2015.
//

#ifndef CHECKERS_CONSOLEPARSINGERROREXCEPTION_H
#define CHECKERS_CONSOLEPARSINGERROREXCEPTION_H

#include <stdexcept>

class ConsoleParsingErrorException : public std::runtime_error
{
public:
    ConsoleParsingErrorException( const std::string &reason );
};


#endif //CHECKERS_CONSOLEPARSINGERROREXCEPTION_H
