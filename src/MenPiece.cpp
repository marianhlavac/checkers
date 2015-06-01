/**
 * @file    MenPiece.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class MenPiece
 *
 * This file contains prototype of MenPiece class
 */

#include "MenPiece.h"

using namespace std;

MenPiece::MenPiece( Player *owner, GameController *parent, int location ) : Piece( owner, parent, location, TYPE_MEN )
{

}

MenPiece::~MenPiece() {

}

pair< vector<int>, vector<int> > MenPiece::findAllMoves( )
{
  char color = owner->color;
  vector<int> moves, jumps;
  int ydir = parent->boardRotated ? (color == 'w' ? 1 : -1 ) : (color == 'w' ? -1 : 1);

  // Move left
  if ( ! parent->outOfFieldRelative( location, -1, ydir ) &&
           parent->getPieceRelative( location, -1, ydir ) == nullptr )
    moves.push_back( location - 1 + ydir * 8 );

  // Move right
  if ( ! parent->outOfFieldRelative( location, 1, ydir ) &&
           parent->getPieceRelative( location, 1, ydir ) == nullptr )
    moves.push_back( location + 1 + ydir * 8 );

  // Jump left
  if ( ! parent->outOfFieldRelative( location, -2, ydir * 2 ) )
  {
    Piece *endpiece = parent->getPieceRelative( location, -2, ydir * 2 ),
            *midpiece = parent->getPieceRelative( location, -1, ydir  );

    if ( endpiece == nullptr && midpiece != nullptr && midpiece->owner->color != color )
      jumps.push_back( location - 2 + ydir * 2 * 8 );
  }

  // Jump right
  if ( ! parent->outOfFieldRelative( location, 2, ydir * 2 ) )
  {
    Piece *endpiece = parent->getPieceRelative( location, 2, ydir * 2 ),
            *midpiece = parent->getPieceRelative( location, 1, ydir );

    if ( endpiece == nullptr && midpiece != nullptr && midpiece->owner->color != color )
      jumps.push_back( location + 2 + ydir * 2 * 8 );
  }

  // Return appropriate set of moves/jumps
  return make_pair( moves, jumps );
}
