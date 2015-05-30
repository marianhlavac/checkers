//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include <string>
#include "Piece.h"
#include "GameController.h"

// Forward declaration to avoid circular dependency problems
class Piece;
class GameController;

using namespace std;

class Player
{
public:
    string name;
    char color = 'w';

    Player( GameController *parent );
    virtual pair< int, int > WaitForInput() = 0;

protected:
    GameController *parent;
};


#endif //CHECKERS_PLAYER_H
