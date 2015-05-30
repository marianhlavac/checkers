//
// Created by Marián on 11. 5. 2015.
//

#include "NetworkPlayer.h"

NetworkPlayer::NetworkPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> NetworkPlayer::WaitForInput( )
{
    return make_pair( 0, 0 );
}
