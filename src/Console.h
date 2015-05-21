//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_CONSOLE_H
#define PA2_LS2015_SEMESTRALKA_CONSOLE_H

class Console
{
public:
    static const int COMMAND_PLAY = 0, COMMAND_LOAD = 1;

    /**
     * Processes the command line arguments
     */
    static int parseCmdln( int argc, char *argv[] );
};


#endif //PA2_LS2015_SEMESTRALKA_CONSOLE_H
