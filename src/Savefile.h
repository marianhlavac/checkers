//
// Created by Marián on 29. 5. 2015.
//

#ifndef CHECKERS_SAVEFILE_H
#define CHECKERS_SAVEFILE_H


#include "GameController.h"

class Savefile
{
public:
    static std::string create( GameController * gameController );
    static bool load( std::istream & savedInfo, GameController * gameController );
private:
    static void parseParams( std::string paramString, std::vector<std::string> & params );
};


#endif //CHECKERS_SAVEFILE_H
