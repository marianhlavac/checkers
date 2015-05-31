/**
 * @file    Savefile.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class Savefile
 *
 * This file contains prototype of Savefile class
 */

#ifndef CHECKERS_SAVEFILE_H
#define CHECKERS_SAVEFILE_H


#include "GameController.h"

/**
 * Utility for saving actual game state into a file
 */
class Savefile
{
public:
    /**
     * Creates a new state save.
     *
     * @param gameController Game controller
     * @return A serialized game state
     */
    static std::string create( GameController * gameController );

    /**
     * Loads a game state from savefile data stream into game controller.
     *
     * @param[in] savedInfo Saved game data stream
     * @param[out] gameController Game controller
     */
    static bool load( std::istream & savedInfo, GameController * gameController );
private:
    /**
     * Parse parameters from one savefile line separated by ';'.
     *
     * @param[in] paramString Parameters line
     * @param[out] params Parameters array
     */
    static void parseParams( std::string paramString, std::vector<std::string> & params );
};


#endif //CHECKERS_SAVEFILE_H
