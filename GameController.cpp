//
// Created by Marián on 11. 5. 2015.
//

#include "GameController.h"
#include "SingletonInstantiationException.h"

GameController::GameController()
{
    throw SingletonInstantiationException();
}

void GameController::Tick()
{
    // Body z brainstormu:

    // - zkontrolovat remízu / prohru

    // - èekat na vstup

    // - zkontrolovat platnost tahu

    // - manipulace s polem a figurkami

    // - detekce vícenásobného skoku

    // - redraw
}