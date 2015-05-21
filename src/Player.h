//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_PLAYER_H
#define PA2_LS2015_SEMESTRALKA_PLAYER_H

#include <string>
#include "Piece.h"

// Forward declaration to avoid circular dependency problems
class Piece;

using namespace std;

class Player
{
public:
    string name;
    char color = 'w';

    virtual pair< int, int > WaitForInput() = 0;
};


#endif //PA2_LS2015_SEMESTRALKA_PLAYER_H
