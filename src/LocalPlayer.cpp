//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include "LocalPlayer.h"

pair<int, int> LocalPlayer::WaitForInput( )
{
    string from = "", to = "";
    cin >> from >> to;

    if ( from.length() == 2 && to.length() == 2 )
        return make_pair( GameController::translateCoords( from ), GameController::translateCoords( to ) );
    else
        return make_pair( -1, -1 );
}