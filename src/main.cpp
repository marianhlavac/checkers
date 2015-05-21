#include <cstdio>
#include <iostream>

#include "GameController.h"
#include "Player.h"
#include "Console.h"
#include "UIRenderer.h"

#define  SPLASH_SCREEN_TIME  1

using namespace std;

int main( int argc, char *argv[] ) {

    GameController gameController;

    // Parse command line arguments
    int cmdlineCommand = Console::parseCmdln( argc, argv );

    // Set active renderer
    gameController.renderer = new UIRenderer( &gameController );

    // Show splash screen
    gameController.renderer->showSplashScreen();
    gameController.delay( SPLASH_SCREEN_TIME );
    gameController.renderer->flushScreen();

    gameController.prepareGame();
    cout << "Game ready..." << endl;

    // First redraw
    gameController.renderer->redraw();

    while ( ! gameController.gameHasEnded )
    {
        gameController.tick();
    }



    return 0;

}