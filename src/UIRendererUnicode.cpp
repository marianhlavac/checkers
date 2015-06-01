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
        UIRenderer(
                parent,
                L'\u26C2', // wmen
                L'\u26C0', // bmen
                L'\u26C3', // wking
                L'\u26C1', // bking
                'E',       // nonpcs
                L'\u2591', // outsprtr
                L'\u2591', // insprtr
                L'\u25F7', // waiting
                L'\u25BB', // prompt
                L'\u26CC', // invalidinp
                L'\u2503', // infoboxsprt
                L'\u26C4'  // usericon
                )
{

}

UIRendererUnicode::~UIRendererUnicode( ) {

}
