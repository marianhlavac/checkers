//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_GAMECONTROLLER_H
#define CHECKERS_GAMECONTROLLER_H

#include "UIRenderer.h"
#include "Piece.h"
#include <map>
#include <iostream>

// Forward declaration to avoid circular dependency problems
class UIRenderer;
class Piece;
class Player;

class GameController
{
public:
    static const int MODE_NOTSET = -1, MODE_VSLOC = 0, MODE_VSAI = 1, MODE_VSNET = 2;
    static int instances;
    int gameMode = MODE_NOTSET, ticks = 0;
    bool gameHasEnded, jumpSequence = false, invalidInput = false;
    Player * onTurn = nullptr, * winner = nullptr;
    UIRenderer * renderer;
    std::map<Player*, std::vector<std::pair<int,int>>> possibleTurns;
    Player * firstplayer, * secondplayer;

    GameController( );
    void prepareNewGame( );
    bool loadGame( std::istream & loadInfo );
    void tick( );
    void delay( int s );
    Piece *getPiece( int index ) const;
    void setPiece( int index, Piece * piece );
    Piece *getPieceRelative( int from, int byx, int byy ) const;
    void setPieceRelative( int from, int byx, int byy, Piece * piece );
    int numOfPossibleTurns() const;
    int numOfPossibleTurns( Player *player ) const;
    int getMoveDirection( int from, int to ) const;
    int getMoveMagnitude( int from, int to ) const;
    bool outOfFieldRelative( int from, int byx, int byy ) const;
    void findPossibleTurns( Player * player, bool * isJumps = nullptr );

private:
    bool isTurnValid( std::pair< int, int > turn ) const;
    void discardAnyBetween( int from, int to );
    bool isJumpSequence( );
    void endOfTurn( );
    void conversionToKings( );
    void gameOver( Player * winner );
    void saveGame( );

    Piece ** field;
};


#endif //CHECKERS_GAMECONTROLLER_H
