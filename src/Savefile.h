//
// Created by Marián on 29. 5. 2015.
//

#ifndef CHECKERS_SAVEFILE_H
#define CHECKERS_SAVEFILE_H


#include "GameController.h"

class Savefile
{
public:
    static string create( GameController * gameController );
    static bool load( istream & savedInfo, GameController * gameController );
private:
    static void parseParams( string paramString, vector<string> & params );
};


#endif //CHECKERS_SAVEFILE_H
