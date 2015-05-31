/**
 * @file    Player.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class Player
 *
 * This file contains prototype of Player class
 */

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include <string>
#include "Piece.h"
#include "GameController.h"

// Forward declaration to avoid circular dependency problems
class Piece;
class GameController;

using namespace std;

/**
 * Base class for AIPlayer, LocalPlayer and NetworkPlayer
 */
class Player
{
public:
    /** Player name */
    std::string name;

    /** Player color */
    char color = 'w';

    /** Default constructor */
    Player( GameController *parent );

    /**
     * Waits for user input. Returns his move.
     *
     * @return Move
     */
    virtual std::pair< int, int > WaitForInput() = 0;

    /**
     * Informs this player about other player's move.
     * Used only in NetworkPlayer.
     *
     * @param from Move from
     * @param to Move to
     */
    virtual void informMove( int from, int to ) = 0;

protected:
    /** Parent game controller */
    GameController *parent;
};


#endif //CHECKERS_PLAYER_H
