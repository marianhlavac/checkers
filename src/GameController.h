//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_GAMECONTROLLER_H
#define CHECKERS_GAMECONTROLLER_H

#include "UIRenderer.h"
#include "Piece.h"
#include "NetworkConnection.h"
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
    int gameMode = MODE_NOTSET;
    int ticks = 0;
    bool gameHasEnded;
    bool jumpSequence = false;
    bool invalidInput = false;
    bool boardRotated = false;
    Player * onTurn = nullptr;
    Player * winner = nullptr;
    UIRenderer * renderer;
    std::map<Player*, std::vector<std::pair<int,int>>> possibleTurns;
    Player * firstplayer;
    Player * secondplayer;
    NetworkConnection * net = nullptr;
    int netGameId = -1;

    GameController( );
    void prepareNewGame( );
    bool loadGame( std::istream & loadInfo );
    void prepareNewNetworkGame( std::string & address, std::string & port );
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
    void fillFieldWithMens( );
    void parseNetInitData( std::string & received, char & color, std::string & nick, int & netgameid );

    Piece ** field;
};


#endif //CHECKERS_GAMECONTROLLER_H
