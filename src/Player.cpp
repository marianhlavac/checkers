//
// Created by Marián on 11. 5. 2015.
//

#include "Player.h"

bool Player::haveAnyTurns( ) const
{
 return false;
}

pair<int, pair<int, int> > Player::WaitForInput( )
{
 return std::pair<int, pair<int, int>>( );
}

Piece *Player::getPiece( int index ) const
{
 return nullptr;
}
