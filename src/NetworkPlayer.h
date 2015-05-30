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
};


#endif //CHECKERS_NETWORKPLAYER_H
