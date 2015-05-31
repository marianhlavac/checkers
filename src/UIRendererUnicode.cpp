/**
 * @file    UIRendererUnicode.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class UIRendererUnicode
 *
 * This file contains prototype of UIRendererUnicode class
 */

#include "UIRendererUnicode.h"

using namespace std;

UIRendererUnicode::UIRendererUnicode( GameController *parent ) :
        UIRenderer( parent, 'i', 'z', 'B', 'W', '!', (charType) 177, (charType) 177, '.', u'\u058D', '!', '|', true)
{

}
