/**
 * @file    UIRendererCompatible.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class UIRendererCompatible
 *
 * This file contains prototype of UIRendererCompatible class
 */

#ifndef CHECKERS_UIRENDERERCOMPATIBLE_H
#define CHECKERS_UIRENDERERCOMPATIBLE_H


#include "UIRenderer.h"

/**
 * Compatible UI renderer not using extended characters
 */
class UIRendererCompatible : public UIRenderer
{
public:
    /**
     * Default constructor
     */
    UIRendererCompatible( GameController * parent );

    /** Destructor */
    ~UIRendererCompatible( );
};


#endif //CHECKERS_UIRENDERERCOMPATIBLE_H
