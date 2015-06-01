#include "UIRendererCompatible.h"

using namespace std;

/**
 * @file    UIRendererCompatible.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class UIRendererCompatible
 *
 * This file contains prototype of UIRendererCompatible class
 */

UIRendererCompatible::~UIRendererCompatible() {
        delete[] logoLines;
}

UIRendererCompatible::UIRendererCompatible( GameController *parent ) :
        UIRenderer(
                parent,
                'w', // wmen
                'b', // bmen
                'W', // wking
                'B', // bking
                '!', // nonpcs
                '#', // outsprtr
                '#', // insprtr
                '.', // waiting
                '>', // prompt
                '!', // invalidinp
                '|', // infoboxsprt
                '-' // usericon
                )
{

}
