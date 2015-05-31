/**
 * @file    UIRendererCompatible.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class UIRendererCompatible
 *
 * This file contains prototype of UIRendererCompatible class
 */

#include "UIRendererCompatible.h"

using namespace std;

UIRendererCompatible::UIRendererCompatible( GameController *parent ) :
        UIRenderer( parent, 'w', 'b', 'W', 'B', '!', '#', '#', '.', '>', '!', '|', false )
{

}
