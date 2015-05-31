/**
 * @file    exceptions.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementations of exception classes
 *
 * This file contains prototypes of all exception classes
 */

#include "exceptions.h"

using namespace std;

ConsoleParsingErrorException::ConsoleParsingErrorException( const string &reason ) : runtime_error( reason ) { }
const char* SingletonInstantiationException::what() const throw() { return "You cannot instantiate a singleton."; }
CreatingGameFailedException::CreatingGameFailedException( const string &reason ) : runtime_error( reason ) { }