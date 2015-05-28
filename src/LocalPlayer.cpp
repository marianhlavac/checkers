//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <cstdlib>
#include "LocalPlayer.h"
#include "Console.h"

LocalPlayer::LocalPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> LocalPlayer::WaitForInput( )
{
    string from = "", to = "";
    cin >> from;

    // Command for exiting the game
    if ( from == "q" || from == "quit" ) return make_pair( -2, -2 );

    // Command for choosing random move
    if ( from == "random" || from == "rand" || from == "r" )
    {
        int idx = rand() % (parent->possibleTurns.size() - 1);
        return parent->possibleTurns.at( this ).at( idx );
    }

    cin >> to;

    if ( from.length() == 2 && to.length() == 2 )
        return make_pair( Console::translateCoords( from ), Console::translateCoords( to ) );
    else
        return make_pair( -1, -1 );
}
