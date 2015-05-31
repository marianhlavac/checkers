//
// Created by Marián on 29. 5. 2015.
//

#include <sstream>
#include "Savefile.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
#include "KingPiece.h"
#include "MenPiece.h"
#include <typeinfo>
#include <ctime>
#include <stdlib.h>

using namespace std;

#define SAVEGAMEFILE_VERSION    1
#define SPR                     ';'

string Savefile::create( GameController *gameController )
{
    stringstream ss;

    // Print heading
    ss << "_CHECKERS_VER" << SAVEGAMEFILE_VERSION << "SAVEGAMEFILE";

    // Timestamp
    ss << endl << time(0);

    // Game vars
    ss << endl << typeid( gameController ).name() << SPR << 31 << SPR << 31             // tpi, rsrvd, rsrvd
        << SPR << gameController->gameMode << SPR << gameController->ticks              // gamemode, ticks
        << SPR << ( gameController->jumpSequence ? 1 : 0 )                              // jmpsqc
        << SPR << ( gameController->onTurn == gameController->secondplayer ? 2 : 1 );   // plyonturn

    // Game field
    ss << endl << typeid( Piece ).name();
    for ( int i = 0; i < 64; i++ )
    {
        if ( gameController->getPiece( i ) == nullptr )
        {
            ss << SPR << 0 << SPR << 0;
        }
        else
        {
            ss << SPR << ( gameController->getPiece( i )->owner == gameController->firstplayer ? 2 : 1 )
                << SPR << gameController->getPiece( i )->type;
        }
    }

    // Determine player types
    int p1type = 0, p2type = 0;
    if ( dynamic_cast< LocalPlayer* >( gameController->firstplayer ) != nullptr )   p1type = 1;
    else if ( dynamic_cast< AIPlayer* >( gameController->firstplayer ) != nullptr ) p1type = 2;
    if ( dynamic_cast< LocalPlayer* >( gameController->secondplayer ) != nullptr )   p2type = 1;
    else if ( dynamic_cast< AIPlayer* >( gameController->secondplayer ) != nullptr ) p2type = 2;

    // Player 1
    ss << endl << typeid( gameController->firstplayer ).name() << SPR << gameController->firstplayer->color
            << SPR << gameController->firstplayer->name << SPR << p1type;

    // Player 2
    ss << endl << typeid( gameController->secondplayer ).name() << SPR << gameController->secondplayer->color
            << SPR << gameController->secondplayer->name << SPR << p2type;

    return ss.str();
}

bool Savefile::load( istream & savedInfo, GameController *gameController )
{
    string head, timestamp, gameVars, field, player1, player2;

    while ( ! savedInfo.eof() )
    {
        // Read lines
        getline( savedInfo, head ); // header
        getline( savedInfo, timestamp ); // timestamp
        getline( savedInfo, gameVars ); // timestamp
        getline( savedInfo, field ); // timestamp
        getline( savedInfo, player1 ); // timestamp
        getline( savedInfo, player2 ); // timestamp
    }

    // Quick check by head and field size if file isn't corrupted
    if ( head.length() > 30 || field.length() < 96 ) return false;

    vector<string> params;

    // Create player 1
    params.clear();
    parseParams( player1, params );
    if ( params.size() != 4 ) return false;
    if ( params[ 3 ] == "1" )
        gameController->firstplayer = new LocalPlayer( gameController );
    else if ( params[ 3 ] == "2" )
        gameController->firstplayer = new AIPlayer( gameController );
    else return false;
    gameController->firstplayer->color = params[ 1 ][ 0 ];
    gameController->firstplayer->name = params[ 2 ];

    // Create player 2
    params.clear();
    parseParams( player2, params );
    if ( params.size() != 4 ) return false;
    if ( params[ 3 ] == "1" )
        gameController->secondplayer = new LocalPlayer( gameController );
    else if ( params[ 3 ] == "2" )
        gameController->secondplayer = new AIPlayer( gameController );
    else return false;
    gameController->secondplayer->color = params[ 1 ][ 0 ];
    gameController->secondplayer->name = params[ 2 ];

    // Fill gamevars info into gameController
    params.clear();
    parseParams( gameVars, params );
    if ( params.size() != 7 || params[ 2 ] != "31" ) return false;
    gameController->gameMode = atoi( params[ 3 ].c_str() );
    gameController->ticks = atoi( params[ 4 ].c_str() );
    gameController->jumpSequence = params[ 5 ] == "1";
    gameController->onTurn = params[ 6 ] == "2" ? gameController->secondplayer : gameController->firstplayer;

    // Fill the field
    params.clear();
    parseParams( field, params );
    if ( params.size() != 129 ) return false;
    for ( int i = 1; i < 129; i += 2 )
    {
        if ( params[ i ] != "0" )
        {
            Player *owner = params[ i ] == "2" ? gameController->secondplayer : gameController->firstplayer;

            if ( params[ i + 1 ] == "2" )
                gameController->setPiece( i / 2, new KingPiece( owner, gameController, i / 2 ) );
            else
                gameController->setPiece( i / 2, new MenPiece( owner, gameController, i / 2 ) );
        }
    }


    return true;
}

void Savefile::parseParams( string paramString, vector<string> & params )
{
    stringstream ss;
    ss.str( paramString );

    while ( ! ss.eof() )
    {
        string param;
        getline( ss, param, SPR );
        params.push_back( param );
    }
}
