//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_NETWORKPLAYER_H
#define CHECKERS_NETWORKPLAYER_H

#include "Player.h"

class NetworkPlayer : public Player
{
public:
    NetworkPlayer( GameController * parent );
    pair<int, int> WaitForInput( );
    void informMove( int from, int to );

private:
    void parseIncoming( std::string & recv, int & from, int & to, int & ticknum, int & netgameid );
};


#endif //CHECKERS_NETWORKPLAYER_H
