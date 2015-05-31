/**
 * @file    GameController.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class GameController
 *
 * This file contains prototype of GameController class
 */

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <fstream>

#include "GameController.h"
#include "UIRenderer.h"
#include "exceptions.h"
#include "MenPiece.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
#include "NetworkPlayer.h"
#include "KingPiece.h"
#include "Savefile.h"
#include "NetworkConnection.h"

using namespace std;

int GameController::instances = 0;

GameController::GameController()
{
    if ( ++instances > 1 ) throw SingletonInstantiationException();
}

GameController::~GameController()
{
    delete firstplayer;
    delete secondplayer;
    delete[] field;

    if ( gameMode == MODE_VSNET ) delete net;

    delete renderer;
}

void GameController::tick()
{
    bool jumpAvailable = false;

    // Find all possible moves / jumps and set as state
    possibleMoves.clear();
    findPossibleMoves(firstplayer, firstplayer == onTurn ? &jumpAvailable : nullptr);
    findPossibleMoves(secondplayer, secondplayer == onTurn ? &jumpAvailable : nullptr);

    // Check game end conditions
    if (numOfPossibleMoves(firstplayer) == 0 )
    {
        // It could be draw
        if (numOfPossibleMoves(secondplayer) == 0 )
        {
            gameOver( nullptr );
            return;
        }

        gameOver( secondplayer );
        return;
    }
    else if (numOfPossibleMoves(secondplayer) == 0 )
    {
        gameOver( firstplayer );
        return;
    }

    // Wait for input and check it's correctness
    pair<int, int> inputTurn = make_pair( INTMAX_MIN, INTMAX_MIN );
    do
    {
        // If entering input failed, redraw
        if ( inputTurn.first != INTMAX_MIN ) renderer->redraw();

        // Wait for input...
        inputTurn = onTurn->WaitForInput( );

        // If input is ( -2, -2 ), it's signal for game quit
        if ( inputTurn == pair<int,int>( -2, -2 ) )
        {
            if ( dynamic_cast<LocalPlayer*>(onTurn) == nullptr ) wcout << L"The other player decided to surrender." << endl;
            wcout << L"Exiting game..." << endl;
            gameHasEnded = true;
            ( firstplayer == onTurn ? secondplayer : firstplayer )->informMove( inputTurn.first, inputTurn.second );
            break;
        }

        // If input is ( -4, -4 ), it's signal for saving game
        if ( inputTurn == pair<int,int>( -4, -4 ) )
        {
            wcout << L"Saving game..." << endl;
            saveGame();
        }

        // If input is ( -6, -6 ), it's signal for failed input receive
        if ( inputTurn == pair<int,int>( -6, -6 ) )
        {
            cerr << "Receiving other player's move failed. The connection may be desynchronized or there is general failure with connection.\n"
                            "Aborting the game." << endl;
            gameHasEnded = true;
            break;
        }

        invalidInput = true;
    }
    while ( ! isTurnValid( inputTurn ) );

    invalidInput = false;

    if ( gameHasEnded ) return;

    // Inform the other player about this move (only used in network conn)
    ( firstplayer == onTurn ? secondplayer : firstplayer )->informMove( inputTurn.first, inputTurn.second );

    // Manipulate pieces and other objects on field
    getPiece( inputTurn.first )->moveTo( inputTurn.second );
    discardAnyBetween( inputTurn.first, inputTurn.second );
    conversionToKings();

    // Detect jump sequence or pass the turn
    if ( ! ( jumpAvailable && ( jumpSequence = isJumpSequence( ) ) ) ) endOfTurn( );

    // Make one step forward ( +1 tick )
    wcout << L"End of tick " << ticks << "...";
    ticks++;

    // Redraw
    renderer->redraw( );
}

void GameController::delay( int s )
{
    time_t start = time( nullptr );
    while ( time( nullptr ) - s < start )
    { }
}

void GameController::prepareNewGame( string nick, string nick2 )
{
    wcout << L"Preparing a local game..." << endl;

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
    else throw runtime_error( "Wrong gamemode" );

    firstplayer->color = 'w';
    secondplayer->color = 'b';

    // Set players names
    firstplayer->name = nick;
    secondplayer->name = nick2;
    if ( gameMode == MODE_VSAI ) secondplayer->name = "AI player";

    // Create field of pieces
    field = new Piece*[64];
    for ( int i = 0; i < 64; i++ ) field[i] = nullptr;

    // Fill the field
    fillFieldWithMens( );

    // First player's turn
    onTurn = firstplayer;
}

void GameController::prepareNewNetworkGame( string & address, string & port, string nick, string nick2 )
{
    wcout << L"Preparing a network game..." << endl;

    bool isServer = address == "hostinggame";
    if ( isServer ) address = "127.0.0.1";

    gameHasEnded = false;
    boardRotated = !isServer;

    // Create connection
    NetworkConnection *net = new NetworkConnection(
            isServer ? NetworkConnection::CONNECTION_SERVER : NetworkConnection::CONNECTION_CLIENT,
            address.c_str(),
            port.c_str()
    );

    // Server have to wait, so display instructions
    if ( isServer ) renderer->drawConnectionScreen( port );

    // Make connection between players
    if ( ! net->makeConnection() ) throw CreatingGameFailedException( "Could not create a connection between" );
    wcout << L"Connection established" << endl;

    // 2x Handshake
    if ( isServer )
    {
        delay( 2 );
        net->sendHandShake();
        net->waitForHandShake();
        net->sendHandShake();
        net->waitForHandShake();
    }
    else
    {
        net->waitForHandShake();
        net->sendHandShake();
        net->waitForHandShake();
        net->sendHandShake();
    }
    wcout << L"Handshake successful!\nExchanging initial information..." << endl;

    // Exchange init information server <--> client
    if ( isServer )
    {
        // Short wait for client
        delay( 1 );

        // Create first player
        firstplayer = new LocalPlayer( this );
        firstplayer->color = 'w';
        firstplayer->name = nick;

        // Create netGame ID
        netGameId = rand() % 65535;

        // Send info about me
        net->sendMessage( "w;" + firstplayer->name + ";7;" + to_string( netGameId ) );

        string received, rnick; char color; int hisnetGameId;

        // Wait for data from client about him
        net->receive( received );

        // Parse received data
        parseNetInitData( received, color, rnick, hisnetGameId );

        if ( netGameId != hisnetGameId )
            throw CreatingGameFailedException( "Invalid netGameId received" );

        // Create second player
        secondplayer = new NetworkPlayer( this );
        secondplayer->color = color;
        secondplayer->name = rnick;


    }
    else
    {
        string received, rnick;
        char color;

        // Wait for data from server
        net->receive( received );

        // Parse received data
        parseNetInitData( received, color, rnick, netGameId );

        // Create first player
        firstplayer = new NetworkPlayer( this );
        firstplayer->color = color;
        firstplayer->name = rnick;

        // Create second player
        secondplayer = new LocalPlayer( this );
        secondplayer->color = color == 'w' ? 'b' : 'w';
        secondplayer->name = nick;

        // Send info about me
        net->sendMessage( string( 1, secondplayer->color ) + ";" + secondplayer->name + ";7;" + to_string( netGameId ) );
    }

    // Create field of pieces
    field = new Piece*[64];
    for ( int i = 0; i < 64; i++ ) field[i] = nullptr;

    // Fill field
    fillFieldWithMens();

    // Game is ready to play... (whew!)
    this->net = net;
    onTurn = firstplayer;

}

bool GameController::loadGame( istream & loadInfo )
{
    wcout << L"Loading the game from save file..." << endl;

    gameHasEnded = false;

    // Create field of pieces
    field = new Piece*[64];
    for ( int i = 0; i < 64; i++ ) field[i] = nullptr;

    return Savefile::load( loadInfo, this );
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
    return find( possibleMoves.at(onTurn).begin(), possibleMoves.at(onTurn).end(), turn ) != possibleMoves.at(onTurn).end();
}

void GameController::discardAnyBetween( int from, int to )
{
    int xdir = ( to % 8 > from % 8 ? 1 : -1 ), ydir = ( to / 8 > from / 8 ? 1 : -1 );

    // Go through diag and throw out enemy's piece
    for ( int x = from % 8, y = from / 8; x != to % 8 && y != to / 8; x += xdir, y += ydir )
    {
        Piece *piece = getPiece( x + y * 8 );
        if ( piece != nullptr && piece->owner != onTurn )
        {
            delete piece;
            setPiece( x + y * 8, nullptr );
        }
    }
}

bool GameController::isJumpSequence( )
{
    bool isJump = false;

    // Refresh possible turns
    findPossibleMoves(onTurn, &isJump);

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
    if ( index >= 0 && index <= 63 )
        this->field[ index ] = piece;
    else
        throw runtime_error("Accessing non-existent place in field");
}
Piece *GameController::getPieceRelative( int from, int byx, int byy ) const
{
    return getPiece( from + byx + ( byy * 8 ) );
}

int GameController::numOfPossibleMoves(Player *player) const
{
    return possibleMoves.at(player).size();
}

void GameController::setPieceRelative( int from, int byx, int byy, Piece * piece )
{
    if ( from + byx + ( byy * 8 ) > 0 && from + byx + ( byy * 8 ) < 64 )
        this->field[ from + byx + ( byy * 8 ) ] = piece;
    else
        throw runtime_error("Accessing non-existent place in field");
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
    return from + byx + ( byy * 8 ) > 63 || from + byx + ( byy * 8 ) < 0 ||
            from + byx < 0 || from + byx > 63 || (from + byx) / 8 != from / 8;
}

void GameController::findPossibleMoves(Player *player, bool *isJumps)
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
    possibleMoves[ player ] = jumps.size() > 0 ? jumps : moves;
    if ( isJumps != nullptr ) *isJumps = jumps.size() > 0;
}

void GameController::saveGame( )
{
    // Create savefile
    string save = Savefile::create( this );
    ofstream file;

    // Open file
    time_t t; time( &t );
    char buf[128];
    strftime( buf, 128, "save-%Y%m%d%H%M%S.txt", gmtime( &t ) );
    file.open( buf );

    if ( ! file.fail() )
    {
        // Save to file
        file << save;
        wcout << endl << L" > Game saved as '" << buf << L"'." << endl;
        delay( 3 );
    }
    else
    {
        cerr << "/!\\ ERROR! The folder is not writtable! Save unsuccessful." << endl;
        delay( 5 );
    }

    file.close();
}

void GameController::fillFieldWithMens( )
{
    // Fill the field with pieces for 1st player
    for ( int i = 40; i < 64; i += 2 )
    {
        if ( i == 48 ) i++;
        if ( i == 57 ) i--;
        field[ boardRotated ? 63-i : i ] = new MenPiece( firstplayer, this, boardRotated ? 63-i : i );
    }

    // Fill the field with pieces for 2nd player
    for ( int i = 1; i < 24; i += 2 )
    {
        if ( i == 16 ) i++;
        if ( i == 9 ) i--;
        field[ boardRotated ? 63-i : i ] = new MenPiece( secondplayer, this, boardRotated ? 63-i : i );
    }
}

void GameController::parseNetInitData( string & received, char & color, string & nick, int & netgameid )
{
    stringstream ss;
    ss.str( received );

    string colorstr, ngidstr;

    getline( ss, colorstr, ';' );
    getline( ss, nick, ';' );
    getline( ss, ngidstr, ';' ); // threw reserved 7 away
    getline( ss, ngidstr, ';' );

    color = colorstr[0];
    netgameid = stoi( ngidstr );
}
