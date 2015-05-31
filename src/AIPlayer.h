/**
 * @file    AIPlayer.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class AIPlayer
 *
 * This file contains prototype of AIPlayer class
 */

#ifndef CHECKERS_AIPLAYER_H
#define CHECKERS_AIPLAYER_H

#include "Player.h"

/**
 * Artifical intelligence player
 */
class AIPlayer : public Player
{
public:
    /** Default constructor */
    AIPlayer( GameController * parent );

    /**
     * Waits for user input. Returns his move.
     * This is pseudo-AI, using dumb tactic, choosing
     * randomly from all possible moves.
     *
     * @return Move
     */
    pair<int, int> WaitForInput( );

    /**
     * Informs this player about other player's move.
     * Used only in NetworkPlayer.
     *
     * @param from Move from
     * @param to Move to
     */
    void informMove( int from, int to );
};


#endif //CHECKERS_AIPLAYER_H
