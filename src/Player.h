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

    pair< int, pair< int, int > > WaitForInput();
    bool haveAnyTurns() const;
    Piece * getPiece( int index ) const;
};


#endif //PA2_LS2015_SEMESTRALKA_PLAYER_H
