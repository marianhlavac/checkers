//
// Created by Marián on 11. 5. 2015.
//

#include "Console.h"
#include "SingletonInstantiationException.h"

Console::Console()
{
    throw SingletonInstantiationException();
}

int Console::parseCommandLineArguments( int argc, char *argv[] )
{
    return COMMAND_PLAY;
}