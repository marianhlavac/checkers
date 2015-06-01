/**
 * @file    LocalPlayer.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class LocalPlayer
 *
 * This file contains prototype of LocalPlayer class
 */

#ifndef CHECKERS_LOCALPLAYER_H
#define CHECKERS_LOCALPLAYER_H

#include "Player.h"

/**
 * Local player
 */
class LocalPlayer : public Player
{
public:
    /** Default constructor */
    LocalPlayer( GameController * parent );

    /** Destructor */
    ~LocalPlayer( );

    /**
     * Waits for user input. Returns his move.
     * Reads from stdin.
     *
     * @return Move
     */
    std::pair<int, int> WaitForInput( );

    /**
     * Informs this player about other player's move.
     * Used only in NetworkPlayer.
     *
     * @param from Move from
     * @param to Move to
     */
    void informMove( int from, int to );
};


#endif //CHECKERS_LOCALPLAYER_H
