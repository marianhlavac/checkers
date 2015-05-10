//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
#define PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H


#include "UIRenderer.h"

class GameController
{
public:
    static UIRenderer renderer;

    /**
     * todo:
     * todo: throws singletonisnta...
     */
    GameController();

    /**
     * Tick - the main
     */
    static void Tick();
};


#endif //PA2_LS2015_SEMESTRALKA_GAMECONTROLLER_H
