/**
 * @file    UIRenderer.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class UIRenderer
 *
 * This file contains prototype of UIRenderer class
 */

#include <iostream>
#include <string>
#include <fstream>
#include "UIRenderer.h"
#include "GameController.h"
#include "Console.h"
#include "LocalPlayer.h"

using namespace std;

#define LEFT_MARGIN         6
#define DEBUG_SHOW_MOVES    false

UIRenderer::UIRenderer( GameController * parent, charType wmen, charType bmen, charType wking,
                        charType bking, charType nonepcs, charType outsprtr, charType insprtr,
                        charType waiting, charType prompt, charType invalidinp,
                        charType infoboxsprtr,  charType usericon, bool allowColors)
        : parent( parent ), WMEN_CHAR( wmen ), BMEN_CHAR( bmen ), WKING_CHAR( wking ), BKING_CHAR( bking ),
          NONE_PCS_CHAR( nonepcs ), OUT_SPRTR_CHAR( outsprtr ), IN_SPRTR_CHAR( insprtr ), WAITING_CHAR( waiting ),
          PROMPT_CHAR( prompt ), INVALID_INPUT_CHAR( invalidinp ), INFOBOX_SEP_CHAR( infoboxsprtr ),
          USERICON_CHAR( usericon ),
          allowColors( allowColors )
{
    // Initialize logo lines
    logoLines = new wstring[6] {
            L"      _               _",
            L"     | |             | |",
            L"  ___| |__   ___  ___| | _____ _ __ ___",
            L" / __| '_ \\ / _ \\/ __| |/ / _ \\ '__/ __|       ",
            L"| (__| | | |  __/ (__|   <  __/ |  \\__ \\       ",
            L" \\___|_| |_|\\___|\\___|_|\\_\\___|_|  |___/  v1.0 ",
    };
}

UIRenderer::UIRenderer( GameController * parent ) :
        UIRenderer( parent, 'w', 'b', 'W', 'B', '!', L'\u2591', L'\u2591', '.', '>', '!', '|', '-',  true )
{
    wcout << L"Default UI Renderer initialized..." << endl;
}

UIRenderer::~UIRenderer()
{
    delete[] logoLines;
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
        for ( pair<int,int> move : parent->possibleMoves[ parent->onTurn ] )
            wcout << Console::translateCoordsW( move.first ) << L" -> " << Console::translateCoordsW( move.second ) << L", ";
    }

    // Instructions
    if ( parent->ticks < 1 )
    {
        wcout << endl << endl << wstring( LEFT_MARGIN , ' ' ) << L"--- How to play: " << wstring( 27, '-') << endl
                << wstring( LEFT_MARGIN , ' ' ) << " Input format is \"XX XX\" where XX is A0 - H8. Type quit or q to quit the game.";
    }

    // Draw input prompt
    wcout << endl << endl << wstring( LEFT_MARGIN , ' ' );
    if ( dynamic_cast<LocalPlayer*>(parent->onTurn) != nullptr ) wcout << L"--- Your turn: "; else wcout << L"--- Waiting for the other player... ";
    wcout << wstring( 32, '-')
        << endl << wstring( LEFT_MARGIN - 1, ' ' ) << ( parent->invalidInput ? INVALID_INPUT_CHAR : L' ' )
        << L' ' << PROMPT_CHAR << L' ';
}

void UIRenderer::drawHeader( ) const
{
    for ( int i = 0; i < 6; i++ )
    {
        wcout << wstring( LEFT_MARGIN, ' ' );
        drawLogoLine( i );

        wstring mode = L"2P HOTSEAT";
        if ( parent->gameMode == GameController::MODE_VSAI ) mode = L"1P VS AI";
        if ( parent->gameMode == GameController::MODE_VSNET ) mode = L"2P NET";

        if ( i == 3 || i == 5 ) wcout << wstring( 4, ' ' ) << INFOBOX_SEP_CHAR;
        if ( i == 4 ) wcout << wstring( 4, ' ' ) << INFOBOX_SEP_CHAR << L"  " << mode;

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

    if ( line == 1 ) wcout << wstring(parent->onTurn->name.begin(), parent->onTurn->name.end() ) << L" is on turn.";

    if ( line == 3 ) wcout << (wchar_t)( parent->onTurn == parent->firstplayer ? WAITING_CHAR : ' ' ) << ' ' <<
                USERICON_CHAR << L"   " << wstring( parent->firstplayer->name.begin(), parent->firstplayer->name.end() );
    if ( line == 4 ) wcout << L"       vs ";
    if ( line == 5 ) wcout << (wchar_t)( parent->onTurn == parent->secondplayer ? WAITING_CHAR : ' ' ) << ' ' <<
                USERICON_CHAR << L"   " << wstring( parent->secondplayer->name.begin(), parent->secondplayer->name.end() );
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

void UIRenderer::drawConnectionScreen( string port ) const {

    wcout << endl <<
             wstring( 6, ' ' ) << L"/" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"Waiting for a client to connect..." << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 3, ' ' ) << L"To run a client, use:" << endl;
    wcout << wstring( 6, ' ' ) << L"|" << wstring( 7, ' ' ) << L"./checkers --versus-network --ip [yourip] --port " << wstring( port.begin(), port.end() ) << endl;
    wcout << wstring( 6, ' ' ) << L"\\" << endl << endl;

}
