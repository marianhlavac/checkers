//
// Created by Marián on 21. 5. 2015.
//

#include "MenPiece.h"

MenPiece::MenPiece( Player *owner, GameController *parent, int location ) : Piece( owner, parent, location )
{

}

vector<int> MenPiece::findAllMoves( )
{
  char color = owner->color;
  vector<int> moves, jumps;

  // Move left
  if ( location % 8 > 0 && ( color == 'w' ? location / 8 > 0 : location / 8 < 7 ) &&
          parent->getPieceRelative( location, -1, color == 'w' ? -1 : 1 ) == nullptr )
    moves.push_back( location - 1 + ( color == 'w' ? -1 : 1 ) * 8 );

  // Move right
  if ( location % 8 < 7 && ( color == 'w' ? location / 8 > 0 : location / 8 < 7 ) &&
          parent->getPieceRelative( location, 1, color == 'w' ? -1 : 1 ) == nullptr )
    moves.push_back( location + 1 + ( color == 'w' ? -1 : 1 ) * 8 );

  // Jump left
  if ( location % 8 > 1 && ( color == 'w' ? location / 8 > 1 : location / 8 < 6 )  )
  {
    Piece *endpiece = parent->getPieceRelative( location, -2, color == 'w' ? -2 : 2 ),
            *midpiece = parent->getPieceRelative( location, -1, color == 'w' ? -1 : 1 );

    if ( endpiece == nullptr && midpiece != nullptr && midpiece->owner->color != color )
      jumps.push_back( location - 2 + ( color == 'w' ? -2 : 2 ) * 8 );
  }

  // Jump right
  if ( location % 8 < 7 && ( color == 'w' ? location / 8 > 1 : location / 8 < 6 )  )
  {
    Piece *endpiece = parent->getPieceRelative( location, 2, color == 'w' ? -2 : 2 ),
            *midpiece = parent->getPieceRelative( location, 1, color == 'w' ? -1 : 1 );

    if ( endpiece == nullptr && midpiece != nullptr && midpiece->owner->color != color )
      jumps.push_back( location + 2 + ( color == 'w' ? -2 : 2 ) * 8 );
  }

  // Return appropriate set of moves/jumps
  if ( jumps.size() > 0 )
    return jumps;
  else
    return moves;
}

int MenPiece::numOfPossibleMoves( )
{
  return findAllMoves().size();
}
