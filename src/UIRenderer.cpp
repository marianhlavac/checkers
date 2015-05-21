//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UIRenderer.h"
#include "GameController.h"

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

}

GameController *UIRenderer::getParent( ) const
{
    return parent;
}

void UIRenderer::drawHeader( ) const
{
    for ( int i = 0; i < 6; i++ )
    {
        cout << std::string( 6, ' ' );
        drawLogoLine( i );
    }
}

void UIRenderer::drawLogoLine( int line ) const
{
    if ( line >= 0 && line < 6 )
        cout << logoLines[ line ] << endl;
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
