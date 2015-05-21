//
// Created by Marián on 11. 5. 2015.
//

#ifndef PA2_LS2015_SEMESTRALKA_UIRENDERER_H
#define PA2_LS2015_SEMESTRALKA_UIRENDERER_H

#include <string>

#include "GameController.h"

// Forward declaration to avoid circular dependency problems
class GameController;

class UIRenderer
{
public:
    static const char WMEN_CHAR = 'w', BMEN_CHAR = 'b', WKING_CHAR = 'W', BKING_CHAR = 'B';

    UIRenderer( GameController * parent );
    void redraw( ) const;
    void flushScreen( ) const;
    void showSplashScreen( ) const;

    virtual void drawHeader( ) const;
    virtual void drawField( ) const;

    GameController *getParent( ) const;

private:
    GameController * parent;
    std::string * logoLines;

    void drawLogoLine( int line ) const;
    virtual void drawFieldLine( int line ) const;
    virtual void drawInfoboxLine( int line ) const;
};


#endif //PA2_LS2015_SEMESTRALKA_UIRENDERER_H
