//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
#define PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H

#include "UIRenderer.h"
#include "Piece.h"

// Forward declaration to avoid circular dependency problems
class UIRenderer;
class Piece;
class Player;

class GameController
{
public:
    static int instances;
    static const int MODE_NOTSET = -1, MODE_SP = 0, MODE_MPVSAI = 1, MODE_MPVSNETWORK = 2;

    int turn = 0, gameMode = MODE_NOTSET, ticks = 0, winner = -1;
    bool gameHasEnded, jumpSequence = false, invalidInput = false;
    UIRenderer * renderer;

    static std::string translateCoords( int location );
    static int translateCoords( std::string location );

    GameController( );
    void prepareGame( );
    void tick( );
    void delay( int s );
    void gameOver( int winner );
    Piece *getPiece( int index ) const;
    void setPiece( int index, Piece * piece );
    Piece *getPieceRelative( int from, int byx, int byy ) const;
    int numOfPossibleTurns() const;
    int numOfPossibleTurns( Player *player ) const;

private:
    Player * firstplayer, * secondplayer;
    Piece ** field;

    bool isTurnValid( std::pair< int, int > turn ) const;
    void discardAnyBetween( int from, int to );
    bool isJumpSequence() const;
    void endOfTurn();
};


#endif //PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
