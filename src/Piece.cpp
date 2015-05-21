//
// Created by Mari�n on 11. 5. 2015.
//


#include <stdexcept>
#include "Piece.h"
#include "GameController.h"

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

Piece::Piece( Player *owner, GameController *parent, int location ) : owner( owner ), parent( parent ), location( location )
{
}
