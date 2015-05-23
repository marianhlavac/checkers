//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UIRenderer.h"
#include "GameController.h"

#define LEFT_MARGIN     6

UIRenderer::UIRenderer( GameController * parent ) : parent( parent )
{
    cout << "Default UI Renderer initialized..." << endl;

    // Initialize logo lines
    logoLines = new std::string[6] {
        "      _               _",
        "     | |             | |",
        "  ___| |__   ___  ___| | _____ _ __ ___",
        " / __| '_ \\ / _ \\/ __| |/ / _ \\ '__/ __| ",
        "| (__| | | |  __/ (__|   <  __/ |  \\__ \\ ",
        " \\___|_| |_|\\___|\\___|_|\\_\\___|_|  |___/  v1.0 ",
    };
}

void UIRenderer::redraw( ) const
{
    // Clear screen
    flushScreen();

    // Draw header
    drawHeader();

    // Vspace between header and field
    cout << endl << endl;

    // Draw field
    drawField();

    // Debug: Print all possible turns
    cout << endl << endl << std::string( LEFT_MARGIN , ' ' ) << "--- Possible moves: " << std::string( 27, '-') << endl;
    for ( int i = 0; i < 64; i++ )
    {
        if ( parent->getPiece( i ) != nullptr )
        {
            vector<int> moves = parent->getPiece( i )->findAllMoves();

            for ( int move : moves )
            {
                cout << parent->translateCoords( i ) << " -> " << parent->translateCoords( move ) << ", ";
            }
        }
    }

    // Draw input prompt
    cout << endl << endl << std::string( LEFT_MARGIN , ' ' ) << "--- Your turn: " << std::string( 32, '-');
    cout << endl << std::string( LEFT_MARGIN - 1, ' ' ) << ( parent->invalidInput ? "! > " : "  > " );
}

GameController *UIRenderer::getParent( ) const
{
    return parent;
}

void UIRenderer::drawHeader( ) const
{
    for ( int i = 0; i < 6; i++ )
    {
        cout << std::string( LEFT_MARGIN, ' ' );
        drawLogoLine( i );

        if ( i == 1 ) cout << std::string( 32, ' ' ) << "Tick " << parent->ticks;
        if ( i == 3 ) cout << std::string( 12, ' ' ) << (parent->gameMode == parent->MODE_VSLOC ? "Versus local" : "Versus AI");

        cout << endl;
    }
}

void UIRenderer::drawLogoLine( int line ) const
{
    if ( line >= 0 && line < 6 )
        cout << logoLines[ line ];
}

void UIRenderer::flushScreen( ) const
{
    cout << string( 60, '\n' );
}

void UIRenderer::showSplashScreen( ) const
{
    cout << "Showing splash screen..." << endl;

    fstream splashfile;
    splashfile.open( "checkers-splash.txt" );

    string line;

    if ( ! splashfile.fail() )
        while ( ! splashfile.eof() )
        {
            getline( splashfile, line );
            cout << endl << line;
        }
}

void UIRenderer::drawField( ) const
{
    // Draw field col labels
    cout << std::string( LEFT_MARGIN + 2, ' '  );
    for ( int i = 0; i < 8; i++ )
    {
        cout << " " << (char)( 65 + i ) << " ";
    } cout << endl;

    // Draw field lines + infobox lines prepended with numbers
    for ( int i = 0; i < 8; i++ )
    {
        cout << std::string( LEFT_MARGIN, ' '  ) << i+1 << " ";
        drawFieldLine( i );
        cout << std::string( 5, ' ' );
        drawInfoboxLine( i );
        cout << endl;
    }
}

void UIRenderer::drawFieldLine( int line ) const
{
    for ( int i = line * 8; i < line * 8 + 8; i++ )
    {
        Piece * piece = parent->getPiece( i );

        if ( line % 2 == 0 ? i % 2 == 0 : i % 2 != 0 )
            cout << std::string( 3, (char)178 );
        else
            if ( piece == nullptr )
                cout << "   ";
            else
            {
                char pieceChar = '!';

                if ( piece->owner->color == 'b' )
                    pieceChar = (piece->type == 2 ? BKING_CHAR : BMEN_CHAR);
                else if ( piece->owner->color == 'w' )
                    pieceChar = (piece->type == 2 ? WKING_CHAR : WMEN_CHAR);

                cout << " " << pieceChar << " ";
            }
    }
}

void UIRenderer::drawInfoboxLine( int line ) const
{
    cout << "> ";
    if ( line == 0 ) cout << "This is infobox";
    if ( line == 2 ) cout << "Player " << parent->turn << " is on turn.";
}
