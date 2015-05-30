//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UIRenderer.h"
#include "GameController.h"
#include "Console.h"

#define LEFT_MARGIN         6
#define DEBUG_SHOW_MOVES    true

UIRenderer::UIRenderer( GameController * parent, charType wmen, charType bmen, charType wking,
                        charType bking, charType nonepcs, charType outsprtr, charType insprtr,
                        charType waiting, charType prompt, charType invalidinp,
                        charType infoboxsprtr, bool allowColors)
        : parent( parent ), WMEN_CHAR( wmen ), BMEN_CHAR( bmen ), WKING_CHAR( wking ), BKING_CHAR( bking ),
          NONE_PCS_CHAR( nonepcs ), OUT_SPRTR_CHAR( outsprtr ), IN_SPRTR_CHAR( insprtr ), WAITING_CHAR( waiting ),
          PROMPT_CHAR( prompt ), INVALID_INPUT_CHAR( invalidinp ), INFOBOX_SEP_CHAR( infoboxsprtr ),
          allowColors( allowColors )
{
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

UIRenderer::UIRenderer( GameController * parent ) :
        UIRenderer( parent, 'b', 'w', 'B', 'W', '!', (charType) 177, (charType) 177, '.', '>', '!', '|', true )
{
    cout << "Default UI Renderer initialized..." << endl;
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
    if ( DEBUG_SHOW_MOVES )
    {
        cout << endl << endl << std::string( LEFT_MARGIN , ' ' ) << "--- Possible moves: " << std::string( 27, '-') << endl;
        for ( pair<int,int> move : parent->possibleTurns[ parent->onTurn ] )
            cout << Console::translateCoords( move.first ) << " -> " << Console::translateCoords( move.second ) << ", ";
    }

    // Draw input prompt
    cout << endl << endl << std::string( LEFT_MARGIN , ' ' ) << "--- Your turn: " << std::string( 32, '-');
    cout << endl << std::string( LEFT_MARGIN - 1, ' ' ) << ( parent->invalidInput ? INVALID_INPUT_CHAR : ' ' )
            << ' ' ;
    wcout << PROMPT_CHAR << ' ';
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
            wcout << OUT_SPRTR_CHAR << IN_SPRTR_CHAR << OUT_SPRTR_CHAR;
        else
            if ( piece == nullptr )
                cout << "   ";
            else
            {
                charType pieceChar = NONE_PCS_CHAR;

                if ( piece->owner->color == 'b' )
                    pieceChar = (piece->type == piece->TYPE_KING ? BKING_CHAR : BMEN_CHAR);
                else if ( piece->owner->color == 'w' )
                    pieceChar = (piece->type == piece->TYPE_KING ? WKING_CHAR : WMEN_CHAR);

                wcout << " " << pieceChar << " ";
            }
    }
}

void UIRenderer::drawInfoboxLine( int line ) const
{
    wcout << INFOBOX_SEP_CHAR << ' ';
    if ( line == 0 ) cout << "This is infobox";
    if ( line == 2 ) cout << parent->onTurn->name << " is on turn.";
}

void UIRenderer::drawGameoverScreen( ) const
{
    // Clear screen
    flushScreen();

    // Draw header
    drawHeader();

    // Vspace between header and field
    cout << endl << endl;

    // Draw result
    if ( parent->winner == nullptr )
    {
        // It's draw
        cout << "DRAW!" << endl;
    }
    else
    {
        cout << parent->winner->name << " WINS!" << endl;
    }

}
