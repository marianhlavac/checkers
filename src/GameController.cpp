//
// Created by Marián on 11. 5. 2015.
//
#include <ctime>
#include <iostream>

#include "GameController.h"
#include "UIRenderer.h"
#include "SingletonInstantiationException.h"
#include "MenPiece.h"

int GameController::instances = 0;

GameController::GameController()
{
    instances++;

    if ( instances > 1 ) throw SingletonInstantiationException();
}

void GameController::tick()
{
    // Make one step forward ( + tick )
    ticks++; cout << "Tick " << ticks << " started...";
    renderer->flushScreen();

    // What player is playing now?
    Player * playerOnTurn = turn == 1 ? firstplayer : secondplayer;

    // Check game end conditions
    if ( ! firstplayer->haveAnyTurns() )
    {
        // It could be draw
        if ( ! secondplayer->haveAnyTurns() )
        {
            gameOver( 3 ); return;
        }

        gameOver( 1 ); return;
    }
    else if ( ! secondplayer->haveAnyTurns() )
    {
        gameOver( 2 ); return;
    }

    // Wait for input and check it's correctness
    pair< int, pair< int, int >> inputTurn;
    do { inputTurn = playerOnTurn->WaitForInput(); }
    while ( ! isTurnValid( inputTurn ) );

    // Manipulate pieces and other objects on field
    playerOnTurn->getPiece( inputTurn.first )->moveTo( inputTurn.second.second );
    discardAnyBetween( inputTurn.second.first, inputTurn.second.second );

    if ( isJumpSequence() )
    // - detekce vícenásobného skoku

    // Redraw
    renderer->redraw();
}

void GameController::delay( int s )
{
    time_t start = std::time( nullptr );
    while ( std::time( nullptr ) - s < start )
    { }
}

void GameController::prepareGame( )
{
    cout << "Preparing the game..." << endl;

    // Create field of pieces
    field = new Piece*[64];
    for ( int i = 0; i < 64; i++ ) field[i] = nullptr;

    // Fill the field with pieces for 1st player
    for ( int i = 40; i < 64; i += 2 )
    {
        if ( i == 48 ) i++;
        if ( i == 57 ) i--;
        field[i] = new MenPiece();
    }

    // Fill the field with pieces for 2nd player
    for ( int i = 1; i < 24; i += 2 )
    {
        if ( i == 16 ) i++;
        if ( i == 9 ) i--;
        field[i] = new MenPiece();
    }

    // Set mode for local todo: temporary
    gameMode = MODE_SP;
}

void GameController::gameOver( int winner )
{
    this->winner = winner;
    gameHasEnded = true;

}

bool GameController::isTurnValid( pair<int, pair<int, int> > turn ) const
{
    return false;
}

void GameController::discardAnyBetween( int from, int to )
{

}

bool GameController::isJumpSequence( ) const
{
    return false;
}
