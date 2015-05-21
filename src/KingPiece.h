//
// Created by Marián on 21. 5. 2015.
//

#ifndef CHECKERS_KINGPIECE_H
#define CHECKERS_KINGPIECE_H

#include "Piece.h"

class KingPiece : public Piece
{
public:
    const int type = TYPE_KING;

    KingPiece( Player *owner, GameController *parent, int location );
};


#endif //CHECKERS_KINGPIECE_H
