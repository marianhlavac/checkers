//
// Created by Marián on 11. 5. 2015.
//

#include "AIPlayer.h"

AIPlayer::AIPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> AIPlayer::WaitForInput( )
{
    return make_pair( 0, 0 );
}
