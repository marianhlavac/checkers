//
// Created by Marián on 21. 5. 2015.
//

#ifndef CHECKERS_KINGPIECE_H
#define CHECKERS_KINGPIECE_H

#include "Piece.h"

class KingPiece : public Piece
{
public:
    KingPiece( Player *owner, GameController *parent, int location );
    std::pair< std::vector<int>, std::vector<int> > findAllMoves();
    std::pair< std::vector<int>, std::vector<int> > diagonalSearch( int dirx, int diry );
};


#endif //CHECKERS_KINGPIECE_H
