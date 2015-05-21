//
// Created by Marián on 21. 5. 2015.
//

#ifndef CHECKERS_MENPIECE_H
#define CHECKERS_MENPIECE_H

#include "Piece.h"

class MenPiece : public Piece
{
public:
    const int type = TYPE_MEN;

    MenPiece( Player *owner, GameController *parent, int location );
    std::vector<int> findAllMoves();
    int numOfPossibleMoves();
};


#endif //CHECKERS_MENPIECE_H
