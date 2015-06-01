/**
 * @file    Piece.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class Piece
 *
 * This file contains prototype of Piece class
 */

#include <stdexcept>
#include "Piece.h"
#include "GameController.h"

using namespace std;

void Piece::moveTo( int newLocation )
{
    if ( location == newLocation ) throw runtime_error("Trying to move piece to the very same position in the field");

    parent->setPiece( location, nullptr );
    if ( parent->getPiece( newLocation ) == nullptr )
    {
        parent->setPiece( newLocation, this );
        location = newLocation;
    } else throw runtime_error("Trying to move piece to a occupied position in the field");
}

Piece::Piece( Player *owner, GameController *parent, int location, int type ) :
        owner( owner ), parent( parent ), type( type ), location( location )
{ }

Piece::~Piece()
{

}
