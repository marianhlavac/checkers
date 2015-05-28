//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_AIPLAYER_H
#define CHECKERS_AIPLAYER_H

#include "Player.h"

class AIPlayer : public Player
{
public:
    AIPlayer( GameController * parent );
    pair<int, int> WaitForInput( );
};


#endif //CHECKERS_AIPLAYER_H
