//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_CONSOLE_H
#define PA2_LS2015_SEMESTRALKA_CONSOLE_H

#include <iostream>
#include <queue>

class Console
{
public:
    static const int COMMAND_PLAY = 0, COMMAND_LOAD = 1;

    /**
     * Processes the command line arguments
     */
    static void parseCmdln( int argc, char *argv[], int &gameMode, int &renderMode, std::string &loadfile, std::string &networkaddress );

    static std::string getNextCommand( std::queue<std::string> &commands );
};


#endif //PA2_LS2015_SEMESTRALKA_CONSOLE_H
