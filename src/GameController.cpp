//
// Created by Marián on 11. 5. 2015.
//
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <typeinfo>
#include <algorithm>

#include "GameController.h"
#include "UIRenderer.h"
#include "SingletonInstantiationException.h"
#include "MenPiece.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"

int GameController::instances = 0;

GameController::GameController()
{
    instances++;

    if ( instances > 1 ) throw SingletonInstantiationException();
}

std::string GameController::translateCoords( int location )
{
    stringstream ss;
    int col = location % 8, row = location / 8;
    ss << (char)( 65 + col ) << (row + 1);
    return ss.str();
}

int GameController::translateCoords( std::string location )
{
    int col = -1, row = -1;

    if ( location[0] >= 65 && location[0] <= 72 ) col = location[0] - 65;
    if ( location[0] >= 97 && location[0] <= 104 ) col = location[0] - 97;
    if ( location[1] >= 49 && location[1] <= 57 ) row = location[1] - 49;

    return ( col == -1 || row == -1 ? -1 : row * 8 + col );
}

void GameController::tick()
{
    // What player is playing now?
    Player *playerOnTurn = turn == 0 ? firstplayer : secondplayer;

    // Check game end conditions
    if ( numOfPossibleTurns( firstplayer ) == 0 )
    {
        // It could be draw
        if ( numOfPossibleTurns( secondplayer ) == 0 )
        {
            gameOver( 3 );
            return;
        }

        gameOver( 1 );
        return;
    }
    else if ( numOfPossibleTurns( secondplayer ) == 0 )
    {
        gameOver( 2 );
        return;
    }

    // Wait for input and check it's correctness
    pair<int, int> inputTurn = make_pair( INTMAX_MIN, INTMAX_MIN );
    do
    {
        if ( inputTurn.first != INTMAX_MIN ) renderer->redraw();
        inputTurn = playerOnTurn->WaitForInput( );
        invalidInput = true;
    }
    while ( ! isTurnValid( inputTurn ) );

    invalidInput = false;

    // Manipulate pieces and other objects on field
    getPiece( inputTurn.first )->moveTo( inputTurn.second );
    discardAnyBetween( inputTurn.first, inputTurn.second );

    // Detect jump sequence or pass the turn
    if ( !( jumpSequence = isJumpSequence( ) ) ) endOfTurn( );

    // Make one step forward ( +1 tick )
    cout << "End of tick " << ticks << "...";
    ticks++;

    // Redraw
    renderer->redraw( );
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

    // Create players
    firstplayer = new LocalPlayer();
    secondplayer = new LocalPlayer();
    firstplayer->color = 'w';
    secondplayer->color = 'b';

    // Create field of pieces
    field = new Piece*[64];
    for ( int i = 0; i < 64; i++ ) field[i] = nullptr;

    // Fill the field with pieces for 1st player
    for ( int i = 40; i < 64; i += 2 )
    {
        if ( i == 48 ) i++;
        if ( i == 57 ) i--;
        field[i] = new MenPiece( firstplayer, this, i );
    }

    // Fill the field with pieces for 2nd player
    for ( int i = 1; i < 24; i += 2 )
    {
        if ( i == 16 ) i++;
        if ( i == 9 ) i--;
        field[i] = new MenPiece( secondplayer, this, i );
    }

    // Set mode for local todo: temporary
    gameMode = MODE_SP;
}

void GameController::gameOver( int winner )
{
    this->winner = winner;
    gameHasEnded = true;

}

bool GameController::isTurnValid( pair<int, int> turn ) const
{
    // Range check
    if ( turn.first < 0 || turn.first > 63 || turn.second < 0 || turn.second > 63 ) return false;

    // Does the from piece exists and is correct ownership?
    if ( getPiece( turn.first ) != nullptr && getPiece( turn.first )->owner == ( this->turn == 0 ? firstplayer : secondplayer ) )
    {
        vector<int> possibleMoves = getPiece( turn.first )->findAllMoves();
        return find( possibleMoves.begin(), possibleMoves.end(), turn.second ) != possibleMoves.end();
    }
    else return false;
}

void GameController::discardAnyBetween( int from, int to )
{

}

bool GameController::isJumpSequence( ) const
{
    return false;
}

void GameController::endOfTurn( )
{
    turn = turn == 1 ? 0 : 1;
}

Piece *GameController::getPiece( int index ) const
{
    return ( index >= 0 && index < 64 ? field[ index ] : nullptr );
}

void GameController::setPiece( int index, Piece *piece )
{
    if ( index > 0 && index < 64 )
        this->field[ index ] = piece;
    else
        throw runtime_error("Accessing non-existent place in field");
}

Piece *GameController::getPieceRelative( int from, int byx, int byy ) const
{
    return getPiece( from + byx + ( byy * 8 ) );
}

int GameController::numOfPossibleTurns( ) const
{
    int turns = 0;

    for ( int i = 0; i < 64; i++ )
        if ( getPiece( i ) != nullptr ) turns += getPiece( i )->numOfPossibleMoves();

    return turns;
}

int GameController::numOfPossibleTurns( Player *player ) const
{
    int turns = 0;

    for ( int i = 0; i < 64; i++ )
        if ( getPiece( i ) != nullptr && getPiece( i )->owner == player ) turns += getPiece( i )->numOfPossibleMoves();

    return turns;
}
