//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UIRenderer.h"
#include "GameController.h"
#include "Console.h"

using namespace std;

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
    logoLines = new wstring[6] {
            L"      _               _",
            L"     | |             | |",
            L"  ___| |__   ___  ___| | _____ _ __ ___",
            L" / __| '_ \\ / _ \\/ __| |/ / _ \\ '__/ __| ",
            L"| (__| | | |  __/ (__|   <  __/ |  \\__ \\ ",
            L" \\___|_| |_|\\___|\\___|_|\\_\\___|_|  |___/  v1.0 ",
    };
}

UIRenderer::UIRenderer( GameController * parent ) :
        UIRenderer( parent, 'w', 'b', 'W', 'B', '!', L'\u2591', L'\u2591', '.', '>', '!', '|', true )
{
    wcout << L"Default UI Renderer initialized..." << endl;
}

void UIRenderer::redraw( ) const
{
    // Clear screen
    flushScreen();

    // Draw header
    drawHeader();

    // Vspace between header and field
    wcout << endl << endl;

    // Draw field
    drawField();

    // Debug: Print all possible turns
    if ( DEBUG_SHOW_MOVES )
    {
        wcout << endl << endl << wstring( LEFT_MARGIN , ' ' ) << L"--- Possible moves: " << wstring( 27, '-') << endl;
        for ( pair<int,int> move : parent->possibleTurns[ parent->onTurn ] )
            wcout << Console::translateCoordsW( move.first ) << L" -> " << Console::translateCoordsW( move.second ) << L", ";
    }

    // Draw input prompt
    wcout << endl << endl << wstring( LEFT_MARGIN , ' ' ) << L"--- Your turn: " << wstring( 32, '-')
        << endl << wstring( LEFT_MARGIN - 1, ' ' ) << ( parent->invalidInput ? INVALID_INPUT_CHAR : L' ' )
        << L' ' << PROMPT_CHAR << L' ';
}

GameController *UIRenderer::getParent( ) const
{
    return parent;
}

void UIRenderer::drawHeader( ) const
{
    for ( int i = 0; i < 6; i++ )
    {
        wcout << wstring( LEFT_MARGIN, ' ' );
        drawLogoLine( i );

        if ( i == 1 ) wcout << wstring( 32, ' ' ) << L"Tick " << parent->ticks;
        if ( i == 3 ) wcout << wstring( 12, ' ' ) << (parent->gameMode == parent->MODE_VSLOC ? L"Versus local" : L"Versus AI");

        wcout << endl;
    }
}

void UIRenderer::drawLogoLine( int line ) const
{
    if ( line >= 0 && line < 6 )
        wcout << logoLines[ line ];
}

void UIRenderer::flushScreen( ) const
{
    wcout << wstring( 60, '\n' );
}

void UIRenderer::showSplashScreen( ) const
{
    wcout << L"Showing splash screen..." << endl;

    fstream splashfile;
    splashfile.open( "checkers-splash.txt" );

    string line;

    if ( ! splashfile.fail() )
        while ( ! splashfile.eof() )
        {
            getline( splashfile, line );
            wcout << endl << wstring(line.begin(), line.end());
        }
}

void UIRenderer::drawField( ) const
{
    // Draw field col labels
    wcout << wstring( LEFT_MARGIN + 2, ' '  );
    for ( int i = 0; i < 8; i++ )
    {
        wcout << " " << (wchar_t)( 65 + i ) << " ";
    } wcout << endl;

    // Draw field lines + infobox lines prepended with numbers
    for ( int i = 0; i < 8; i++ )
    {
        wcout << wstring( LEFT_MARGIN, ' '  ) << i+1 << L" ";
        drawFieldLine( i );
        wcout << wstring( 5, ' ' );
        drawInfoboxLine( i );
        wcout << endl;
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
                wcout << L"   ";
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
    if ( line == 0 ) wcout << L"This is infobox";
    if ( line == 2 ) wcout << wstring(parent->onTurn->name.begin(), parent->onTurn->name.end() ) << L" is on turn.";
}

void UIRenderer::drawGameoverScreen( ) const
{
    // Clear screen
    flushScreen();

    // Draw header
    drawHeader();

    // Vspace between header and field
    wcout << endl << endl;

    // Draw result
    if ( parent->winner == nullptr )
    {
        // It's draw
        wcout << "DRAW!" << endl;
    }
    else
    {
        wcout << wstring( parent->winner->name.begin(), parent->winner->name.end() ) << L" WINS!" << endl;
    }

}
