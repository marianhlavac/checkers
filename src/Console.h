/**
 * @file    Console.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class Console
 *
 * This file contains prototype of Console class
 */

#ifndef CHECKERS_CONSOLE_H
#define CHECKERS_CONSOLE_H

#include <iostream>
#include <queue>
#include <sstream>

/**
 * Utility for parsing console command arguments
 */
class Console
{
public:

    /**
     * Processes the command arguments.
     *
     * @param[in] argc Number of arguments
     * @param[in] argv Array of arguments
     * @param[out] gameMode Game mode
     * @param[out] renderMode Render mode
     * @param[out] loadfile File used to load the game from
     * @param[out] networkaddress Network address
     * @param[out] networkport Network port
     * @param[out] nick P1 nick
     * @param[out] nick2 P2 nick
     */
    static void parseCmdln( int argc, char *argv[], int &gameMode, int &renderMode, std::string &loadfile,
                            std::string &networkaddress, std::string & networkport, std::string & nick, std::string & nick2 );

    /**
     * Dequeues next command from specified queue. Shortcut
     *
     * @param commands Commands queue
     * @return Next command
     */
    static std::string getNextCommand( std::queue<std::string> &commands );

    /**
     * Translates coords from numeric format to string format [A0-H8]
     *
     * @param location Location in numeric format
     * @return Location in string format [A0-H8]
     */
    static std::string translateCoords( int location );

    /**
     * Translates coords from numeric format to string format [A0-H8]
     *
     * @param location Location in string format [A0-H8]
     * @return Location in numeric format
     */
    static int translateCoords( std::string location );

    /**
     * Translates coords from numeric format to wide char string format [A0-H8]
     *
     * @param location Location in numeric format
     * @return Location in wide char string format [A0-H8]
     */
    static std::wstring translateCoordsW( int location );
};


#endif //CHECKERS_CONSOLE_H
