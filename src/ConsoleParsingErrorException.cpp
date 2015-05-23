//
// Created by Marián on 24. 5. 2015.
//

#include "ConsoleParsingErrorException.h"


ConsoleParsingErrorException::ConsoleParsingErrorException( const std::string &reason ) : runtime_error( reason )
{

}
