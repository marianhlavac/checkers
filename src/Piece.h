//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

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
    static const int TYPE_NONE = 0, TYPE_MEN = 1, TYPE_KING = 2;
    const int type;

    Piece( Player *owner, GameController *parent, int location, int type );
    void moveTo( int newLocation );

    virtual std::pair<std::vector<int>, std::vector<int>> findAllMoves() = 0;
    int numOfPossibleMoves();

protected:
    int location = -1;
};


#endif //CHECKERS_PIECE_H
