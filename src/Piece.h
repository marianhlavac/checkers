//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_PIECE_H
#define PA2_LS2015_SEMESTRALKA_PIECE_H

#include "Player.h"

// Forward declaration to avoid circular dependency problems
class Player;

class Piece
{
public:
    Player *owner;

    virtual void moveTo( int newLocation );
};


#endif //PA2_LS2015_SEMESTRALKA_PIECE_H
