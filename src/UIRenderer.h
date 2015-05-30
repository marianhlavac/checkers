//
// Created by Marián on 11. 5. 2015.
//

#ifndef CHECKERS_UIRENDERER_H
#define CHECKERS_UIRENDERER_H

#include <string>

#include "GameController.h"

typedef wchar_t charType;

// Forward declaration to avoid circular dependency problems
class GameController;

class UIRenderer
{
public:
    const charType WMEN_CHAR, BMEN_CHAR, WKING_CHAR, BKING_CHAR, NONE_PCS_CHAR, OUT_SPRTR_CHAR, IN_SPRTR_CHAR,
            WAITING_CHAR, PROMPT_CHAR, INVALID_INPUT_CHAR, INFOBOX_SEP_CHAR;
    const bool allowColors;

    UIRenderer( GameController * parent, charType wmen, charType bmen, charType wking,
                charType bking, charType nonepcs, charType outsprtr, charType insprtr,
                charType waiting, charType prompt, charType invalidinp, charType infoboxsprtr,
                bool allowColors );
    UIRenderer( GameController * parent );
    void redraw( ) const;
    void flushScreen( ) const;
    void showSplashScreen( ) const;
    void drawGameoverScreen( ) const;

    virtual void drawHeader( ) const;
    virtual void drawField( ) const;

    GameController *getParent( ) const;

protected:
    GameController * parent;
    std::string * logoLines;

    void drawLogoLine( int line ) const;
    virtual void drawFieldLine( int line ) const;
    virtual void drawInfoboxLine( int line ) const;
};


#endif //CHECKERS_UIRENDERER_H
