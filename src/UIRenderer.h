/**
 * @file    UIRenderer.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class UIRenderer
 *
 * This file contains prototype of UIRenderer class
 */

#ifndef CHECKERS_UIRENDERER_H
#define CHECKERS_UIRENDERER_H

#include <string>

#include "GameController.h"

typedef wchar_t charType;

// Forward declaration to avoid circular dependency problems
class GameController;

/**
 * Default UI renderer using extended characters and colors
 */
class UIRenderer
{
public:
    /** Character - white men */
    const charType WMEN_CHAR;

    /** Character - black men */
    const charType BMEN_CHAR;

    /** Character - white king */
    const charType WKING_CHAR;

    /** Character - black king */
    const charType BKING_CHAR;

    /** Character - none piece */
    const charType NONE_PCS_CHAR;

    /** Character - outer field separator */
    const charType OUT_SPRTR_CHAR;

    /** Character - inner field separator */
    const charType IN_SPRTR_CHAR;

    /** Character - waiting character */
    const charType WAITING_CHAR;

    /** Character - prompt character */
    const charType PROMPT_CHAR;

    /** Character - invalid input character */
    const charType INVALID_INPUT_CHAR;

    /** Character - infobox separator character */
    const charType INFOBOX_SEP_CHAR;

    /** Character - user icon */
    const charType USERICON_CHAR;

    /** Indicates if colors are allowed */
    const bool allowColors;

    /** Default constructor */
    UIRenderer( GameController * parent, charType wmen, charType bmen, charType wking,
                charType bking, charType nonepcs, charType outsprtr, charType insprtr,
                charType waiting, charType prompt, charType invalidinp, charType infoboxsprtr, charType usericon,
                bool allowColors );

    /** Constructor with default character setup */
    UIRenderer( GameController * parent );

    /** Destructor */
    ~UIRenderer( );

    /**
     * Redraws the screen
     */
    void redraw( ) const;

    /**
     * Flushes the screen
     *
     * Because of platform variability, flushing is done by
     * printing a lot of newlines.
     */
    void flushScreen( ) const;

    /**
     * Shows a splash screen, if the file is present.
     */
    void showSplashScreen( ) const;

    /**
     * Shows a game over screen.
     */
    void drawGameoverScreen( ) const;

    /**
     * Draws a waiting connection instructions.
     */
    void drawConnectionScreen( std::string port ) const;

    /**
     * Draws a header.
     */
    virtual void drawHeader( ) const;

    /**
     * Draws the game field.
     */
    virtual void drawField( ) const;

protected:
    /** Parent game controller */
    GameController * parent;

    /** Logo lines */
    std::wstring * logoLines;

    /**
     * Draws one logo line.
     *
     * @param line Line number
     */
    void drawLogoLine( int line ) const;

    /**
     * Draws one field line.
     *
     * @param line Line number
     */
    virtual void drawFieldLine( int line ) const;

    /**
     * Draws one infobox line.
     *
     * @param line Line number
     */
    virtual void drawInfoboxLine( int line ) const;
};


#endif //CHECKERS_UIRENDERER_H
