//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_PIECE_H
#define PA2_LS2015_SEMESTRALKA_PIECE_H

#include <vector>
#include "Player.h"
#include "GameController.h"

// Forward declaration to avoid circular dependency problems
class Player;
class GameController;

class Piece
{
public:
    Player *owner;
    GameController *parent;
    static const int TYPE_MEN = 1, TYPE_KING = 2;
    const int type = 0;

    Piece( Player *owner, GameController *parent, int location );
    void moveTo( int newLocation );

    virtual std::vector<int> findAllMoves() = 0;
    virtual int numOfPossibleMoves() = 0;

protected:
    int location = -1;
};


#endif //PA2_LS2015_SEMESTRALKA_PIECE_H
