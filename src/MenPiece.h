//
// Created by Marián on 21. 5. 2015.
//

#ifndef CHECKERS_MENPIECE_H
#define CHECKERS_MENPIECE_H

#include "Piece.h"

class MenPiece : public Piece
{
public:
    MenPiece( Player *owner, GameController *parent, int location );
    std::pair< std::vector<int>, std::vector<int> > findAllMoves();
};


#endif //CHECKERS_MENPIECE_H
