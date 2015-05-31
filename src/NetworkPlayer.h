/**
 * @file    NetworkPlayer.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class NetworkPlayer
 *
 * This file contains prototype of NetworkPlayer class
 */

#ifndef CHECKERS_NETWORKPLAYER_H
#define CHECKERS_NETWORKPLAYER_H

#include "Player.h"

/**
 * Network player
 */
class NetworkPlayer : public Player
{
public:
    /** Default constructor */
    NetworkPlayer( GameController * parent );

    /**
     * Waits for user input. Returns his move.
     * Receives on net socket.
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

private:
    /**
     * Parse incoming message into values
     *
     * @param[in] recv Received message
     * @param[out] from Move from
     * @param[out] to Move to
     * @param[out] ticknum No. of tick
     * @param[out] netgameid Game ID
     */
    void parseIncoming( std::string & recv, int & from, int & to, int & ticknum, int & netgameid );
};


#endif //CHECKERS_NETWORKPLAYER_H
