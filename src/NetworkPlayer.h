//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_NETWORKPLAYER_H
#define PA2_LS2015_SEMESTRALKA_NETWORKPLAYER_H

#include "Player.h"

class NetworkPlayer : public Player
{
    pair<int, int> WaitForInput( );
};


#endif //PA2_LS2015_SEMESTRALKA_NETWORKPLAYER_H
