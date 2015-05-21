//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
#define PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H

#include "UIRenderer.h"
#include "Piece.h"

// Forward declaration to avoid circular dependency problems
class UIRenderer;

class GameController
{
public:
    static int instances;
    static const int MODE_NOTSET = -1, MODE_SP = 0, MODE_MPVSAI = 1, MODE_MPVSLOCAL = 2, MODE_MPVSNETWORK = 3;

    int turn = 0, gameMode = MODE_NOTSET, ticks = 0, winner = -1;
    bool gameHasEnded;
    UIRenderer * renderer;

    /**
     * todo:
     * todo: throws singletonisnta...
     */
    GameController( );

    void prepareGame( );

    /**
     * Tick - the main
     */
    void tick( );
    void delay( int s );
    void gameOver( int winner );

private:
    Player * firstplayer, * secondplayer;
    Piece ** field;

    bool isTurnValid( pair< int, pair< int, int > > turn ) const;
    void discardAnyBetween( int from, int to );
    bool isJumpSequence() const;
};


#endif //PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
