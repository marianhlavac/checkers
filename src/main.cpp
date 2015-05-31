/**
 * @file    main.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Main file
 */

#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <fstream>

#include "GameController.h"
#include "Player.h"
#include "Console.h"
#include "UIRenderer.h"
#include "exceptions.h"
#include "UIRendererUnicode.h"
#include "UIRendererCompatible.h"

#define  SPLASH_SCREEN_TIME  1

using namespace std;

int main( int argc, char *argv[] )
{
    int gamemode = GameController::MODE_VSLOC, rendermode = 0;
    string loadfilename = "", networkaddress, networkport;

    GameController gameController;

    // Parse command line arguments
    try
    {
        Console::parseCmdln( argc, argv, gamemode, rendermode, loadfilename, networkaddress, networkport );
    }
    catch ( ConsoleParsingErrorException ex )
    {
        cerr << "Can't run." << endl << "Error parsing arguments: " << ex.what() << endl;
        return 1;
    }

    // Set received gamemode
    gameController.gameMode = gamemode;

    // Set active renderer
    if ( rendermode != 2 ) setlocale( LC_ALL, "" );
    if ( rendermode == 1 )
        gameController.renderer = new UIRendererUnicode( &gameController );
    else if ( rendermode == 2 )
        gameController.renderer = new UIRendererCompatible( &gameController );
    else
        gameController.renderer = new UIRenderer( &gameController );



    // Show splash screen
    gameController.renderer->showSplashScreen();
    gameController.delay( SPLASH_SCREEN_TIME );
    gameController.renderer->flushScreen();

    // Create new network game
    if ( gamemode == GameController::MODE_VSNET )
    {
        try
        {
            gameController.prepareNewNetworkGame(networkaddress, networkport);
        }
        catch ( CreatingGameFailedException ex )
        {
            cerr << "Creating network game failed." << endl;
            return 2;
        }
    }
    // Load local game
    else if ( loadfilename != "" )
    {
        wcout << L"Opening save file '" << wstring( loadfilename.begin(), loadfilename.end() ) << L"' ..." << endl;
        ifstream file;
        file.open( loadfilename );

        if ( file.fail() || ! gameController.loadGame( file ) )
        {
            cerr <<
            "Error loading game from file. You don't have rights to read this file or the file is corrupted file save." <<
            endl;
            return 2;
        }
    }
    // Create new localgame
    else
    {
        gameController.prepareNewGame();
    }

    wcout << L"Game ready..." << endl;

    // First redraw
    gameController.renderer->redraw();

    while ( ! gameController.gameHasEnded )
    {
        gameController.tick();
    }

    gameController.delay( 4 );

    return 0;

}