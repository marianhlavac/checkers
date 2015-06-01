/**
 * @file    UIRendererUnicode.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class UIRendererUnicode
 *
 * This file contains prototype of UIRendererUnicode class
 */

#ifndef CHECKERS_UIRENDERERUNICODE_H
#define CHECKERS_UIRENDERERUNICODE_H


#include "UIRenderer.h"

/**
 * Unicode UI Renderer using unicode characters
 */
class UIRendererUnicode : public UIRenderer
{
public:
    /** Default constructor */
    UIRendererUnicode( GameController * parent );

    /** Destructor */
    ~UIRendererUnicode( );
};


#endif //CHECKERS_UIRENDERERUNICODE_H
