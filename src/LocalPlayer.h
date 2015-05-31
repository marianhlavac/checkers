//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_LOCALPLAYER_H
#define CHECKERS_LOCALPLAYER_H

#include "Player.h"

class LocalPlayer : public Player
{
public:
    LocalPlayer( GameController * parent );
    pair<int, int> WaitForInput( );
    void informMove( int from, int to );
};


#endif //CHECKERS_LOCALPLAYER_H
