#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <fstream>

#include "GameController.h"
#include "Player.h"
#include "Console.h"
#include "UIRenderer.h"
#include "ConsoleParsingErrorException.h"
#include "UIRendererUnicode.h"
#include "UIRendererCompatible.h"

#define  SPLASH_SCREEN_TIME  1

using namespace std;

int main( int argc, char *argv[] )
{
    int gamemode = GameController::MODE_VSLOC, rendermode = 0;
    std::string loadfilename = "", networkaddress = "";
    GameController gameController;

    // Parse command line arguments
    try
    {
        Console::parseCmdln( argc, argv, gamemode, rendermode, loadfilename, networkaddress );
    }
    catch ( ConsoleParsingErrorException ex )
    {
        cerr << "Can't run." << endl << "Error parsing arguments: " << ex.what();
        return 1;
    }

    // Set received gamemode
    gameController.gameMode = gamemode;

    // Set active renderer
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

    // Load / create new game
    if ( loadfilename != "" )
    {
        cout << "Opening save file '" << loadfilename << "' ..." << endl;
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
    else
    {
        gameController.prepareNewGame();
    }

    cout << "Game ready..." << endl;

    // First redraw
    gameController.renderer->redraw();

    while ( ! gameController.gameHasEnded )
    {
        gameController.tick();
    }

    gameController.delay( 4 );

    return 0;

}