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
#include "NetworkPlayer.h"
#include "KingPiece.h"

int GameController::instances = 0;

GameController::GameController()
{
    if ( ++instances > 1 ) throw SingletonInstantiationException();
}

void GameController::tick()
{
    bool jumpAvailable = false;

    // Find all possible moves / jumps and set as state
    possibleTurns.clear();
    findPossibleTurns( firstplayer, firstplayer == onTurn ? &jumpAvailable : nullptr );
    findPossibleTurns( secondplayer, secondplayer == onTurn ? &jumpAvailable : nullptr );

    // Check game end conditions
    if ( numOfPossibleTurns( firstplayer ) == 0 )
    {
        // It could be draw
        if ( numOfPossibleTurns( secondplayer ) == 0 )
        {
            gameOver( nullptr );
            return;
        }

        gameOver( secondplayer );
        return;
    }
    else if ( numOfPossibleTurns( secondplayer ) == 0 )
    {
        gameOver( firstplayer );
        return;
    }

    // Wait for input and check it's correctness
    pair<int, int> inputTurn = make_pair( INTMAX_MIN, INTMAX_MIN );
    do
    {
        if ( inputTurn.first != INTMAX_MIN ) renderer->redraw();
        inputTurn = onTurn->WaitForInput( );
        if ( inputTurn == pair<int,int>( -2, -2 ) )
        {
            gameHasEnded = true;
            break;
        }
        invalidInput = true;
    }
    while ( ! isTurnValid( inputTurn ) );

    invalidInput = false;

    if ( gameHasEnded ) return;

    // Manipulate pieces and other objects on field
    getPiece( inputTurn.first )->moveTo( inputTurn.second );
    discardAnyBetween( inputTurn.first, inputTurn.second );
    conversionToKings();

    // Detect jump sequence or pass the turn
    if ( ! ( jumpAvailable && ( jumpSequence = isJumpSequence( ) ) ) ) endOfTurn( );

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

    gameHasEnded = false;

    // Create players
    if ( gameMode == MODE_VSLOC )
    {
        firstplayer = new LocalPlayer( this );
        secondplayer = new LocalPlayer( this );
    }
    else if ( gameMode == MODE_VSAI )
    {
        firstplayer = new LocalPlayer( this );
        secondplayer = new AIPlayer( this );
    }
    else if ( gameMode == MODE_VSNET )
    {
        firstplayer = new LocalPlayer( this );
        secondplayer = new NetworkPlayer( this );
    }

    // Assign colors to players
    if ( gameMode == MODE_VSNET )
    {
        // todo: make sure the colors are correctly assigned
        firstplayer->color = 'w';
        secondplayer->color = 'b';
    }
    else
    {
        firstplayer->color = 'w';
        secondplayer->color = 'b';
    }

    // Set players names
    firstplayer->name = "Player 1";
    secondplayer->name = "Player 2";

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
    gameMode = MODE_VSLOC;

    // Determine who's starting the game todo: this doesn't work
    onTurn = firstplayer;
}

void GameController::gameOver( Player * winner )
{
    this->winner = winner;
    gameHasEnded = true;

    // Announce the game ending
    renderer->drawGameoverScreen();
}

bool GameController::isTurnValid( pair<int, int> turn ) const
{
    return find( possibleTurns.at(onTurn).begin(), possibleTurns.at(onTurn).end(), turn ) != possibleTurns.at(onTurn).end();
}

void GameController::discardAnyBetween( int from, int to )
{
    cout << "Magnitude was: " << getMoveMagnitude( from, to );
    if ( getMoveMagnitude( from, to ) >= 2 )
    {
        // Get correct piece
        int dir = getMoveDirection( from, to );
        Piece *piece = getPieceRelative( from, dir > 1 ? -1 : 1, dir < 3 && dir > 0 ? 1 : -1 );

        if ( piece == nullptr ) throw runtime_error( "Missing piece between last move!" );

        delete piece;
        setPieceRelative( from, dir > 1 ? -1 : 1, dir < 3 && dir > 0 ? 1 : -1, nullptr );
    }
}

bool GameController::isJumpSequence( )
{
    bool isJump = false;

    // Refresh possible turns
    findPossibleTurns( onTurn, &isJump );

    // If any jump available, it's sequence
    return isJump;
}

void GameController::endOfTurn( )
{
    // Toggle between players
    onTurn = onTurn == firstplayer ? secondplayer : firstplayer;
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
    return possibleTurns.at(firstplayer).size() + possibleTurns.at(secondplayer).size();
}

int GameController::numOfPossibleTurns( Player *player ) const
{
    return possibleTurns.at(player).size();
}

int GameController::getMoveDirection( int from, int to ) const
{
    pair<int,int> fromxy = make_pair( from % 8, from / 8 ),
            toxy = make_pair( to % 8, to / 8 );

    return toxy.first > fromxy.first ?
           ( toxy.second > fromxy.second ? 1 : 0 ) :
           ( toxy.second > fromxy.second ? 2 : 3 );
}

void GameController::setPieceRelative( int from, int byx, int byy, Piece * piece )
{
    if ( from + byx + ( byy * 8 ) > 0 && from + byx + ( byy * 8 ) < 64 )
        this->field[ from + byx + ( byy * 8 ) ] = piece;
    else
        throw runtime_error("Accessing non-existent place in field");
}

int GameController::getMoveMagnitude( int from, int to ) const
{
    pair<int,int> fromxy = make_pair( from % 8, from / 8 ),
            toxy = make_pair( to % 8, to / 8 );

    return (int)sqrt( pow( abs( fromxy.first - toxy.first ), 2 ) + pow( abs( fromxy.second - toxy.second ) , 2 ) );
}

void GameController::conversionToKings( )
{
    // Top line
    for ( int i = 0; i < 7; i++ )
    {
        if ( field[ i ] != nullptr )
        if ( field[ i ]->owner == firstplayer && field[ i ]->type == field[ i ]->TYPE_MEN )
        {
            delete field[ i ];
            field[ i ] = new KingPiece( firstplayer, this, i );
        }
    }

    // Bottom line
    for ( int i = 56; i < 63; i++ )
    {
        if ( field[ i ] != nullptr )
        if ( field[ i ]->owner == secondplayer )
        {
            delete field[ i ];
            field[ i ] = new KingPiece( secondplayer, this, i );
        }
    }
}

bool GameController::outOfFieldRelative( int from, int byx, int byy ) const
{
    return from + byx + ( byy * 8 ) > 63 || from + byx + ( byy * 8 ) < 0 || (from + byx) / 8 != from / 8;
}

void GameController::findPossibleTurns( Player * player, bool * isJumps )
{
    vector<pair<int,int>> moves, jumps;

    // Iterate over field
    for ( int i = 0; i < 64; i++ )
    {
        // Find only pieces that belongs to specified player
        if ( getPiece( i ) != nullptr && getPiece( i )->owner == player )
        {
            // Find all moves and jumps
            pair< vector<int>, vector<int> > movesnjumps = getPiece( i )->findAllMoves();

            // And copy them
            for ( int move : movesnjumps.first ) moves.push_back( make_pair( i, move ) );
            for ( int jump : movesnjumps.second ) jumps.push_back( make_pair( i, jump ) );
        }
    }

    // If there is any possible jump, moves can't be done
    possibleTurns[ player ] = jumps.size() > 0 ? jumps : moves;
    if ( isJumps != nullptr ) *isJumps = jumps.size() > 0;
}
