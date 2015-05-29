//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <cstdlib>
#include "LocalPlayer.h"
#include "Console.h"
#include "MenPiece.h"
#include "KingPiece.h"

#define SPECIAL_COMMANDS_ALLOWED true

LocalPlayer::LocalPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> LocalPlayer::WaitForInput( )
{
    string from = "", to = "";
    cin >> from;

    // Command for exiting the game
    if ( from == "q" || from == "quit" ) return make_pair( -2, -2 );

    // Command for choosing random move
    if ( from == "random" || from == "rand" || from == "r" )
    {
        int idx = rand() % (parent->possibleTurns.size() - 1);
        return parent->possibleTurns.at( this ).at( idx );
    }

    // Command for saving the game
    if ( from == "save" )
    {
        cout << " > not possible. ";
        return make_pair( -1, -1 );
    }

    // # SPECIAL COMMANDS
    if ( SPECIAL_COMMANDS_ALLOWED )
    {
        // Special debugging commands, sp - setpiece, spk - setpieceking, ep - erasepiece
        if ( from == "sp" || from == "spk" || from == "ep" )
        {
            int pos, ply;
            cout << " position, player > ";
            cin >> pos >> ply;
            if ( parent->getPiece( pos ) != nullptr ) delete parent->getPiece( pos );
            if ( from == "ep" )
            {
                parent->setPiece( pos, nullptr );
                return make_pair( -1, -1 );
            }
            parent->setPiece( pos, from == "sp" ? ( Piece * ) new MenPiece( ply == 2 ? parent->secondplayer : parent->firstplayer, parent, pos )
                                                : ( Piece * ) new KingPiece( ply == 2 ? parent->secondplayer : parent->firstplayer, parent, pos ));
            return make_pair( -1, -1 );
        }

        // Special debugging command, eap - eraseallpieces
        if ( from == "eap" )
        {
            for ( int i = 0; i < 64; i++ )
            {
                if ( parent->getPiece( i ) != nullptr ) delete parent->getPiece( i );
                parent->setPiece( i , nullptr );
            }
            return make_pair( -1, -1 );
        }

        // Special debugging command, rpt - refreshpossibleturns
        if ( from == "rpt" )
        {
            parent->findPossibleTurns( parent->onTurn );
            return make_pair( -1, -1 );
        }
    }

    cin >> to;

    if ( from.length() == 2 && to.length() == 2 )
        return make_pair( Console::translateCoords( from ), Console::translateCoords( to ) );
    else
        return make_pair( -1, -1 );
}
