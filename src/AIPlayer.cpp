//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <cstdlib>
#include "AIPlayer.h"

AIPlayer::AIPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> AIPlayer::WaitForInput( )
{
    /*
     * AIPlayer, basic
     * "Dumb" tactic: choose random from all possible turns
     */

    // Fake "thinking" delay
    parent->delay( 2 );

    // Choose random turn
    int idx = rand() % (parent->possibleTurns.size() - 1);
    return parent->possibleTurns.at( this ).at( idx );
}
