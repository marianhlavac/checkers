//
// Created by majko on 31.5.15.
//

#include "exceptions.h"

ConsoleParsingErrorException::ConsoleParsingErrorException( const std::string &reason ) : runtime_error( reason ) { }
const char* SingletonInstantiationException::what() const throw() { return "You cannot instantiate a singleton."; }
CreatingGameFailedException::CreatingGameFailedException( const std::string &reason ) : runtime_error( reason ) { }