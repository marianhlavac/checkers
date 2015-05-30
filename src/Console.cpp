//
// Created by Marián on 11. 5. 2015.
//

#include <iostream>
#include <string>
#include <queue>

#include "Console.h"
#include "GameController.h"
#include "ConsoleParsingErrorException.h"

void Console::parseCmdln( int argc, char *argv[], int &gameMode, int &renderMode, std::string &loadfile, std::string &networkaddress )
{
    bool gamemodeSet = false, rendermodeSet = false, fileLoaded = false;
    std::string ip = "0.0.0.0", port = "0";

    // Move commands in queue, omitting the first argument
    std::queue<std::string> parsedCommands;
    for ( int i = 1; i < argc; i++ )
        parsedCommands.push( std::string( argv[i] ) );

    while ( ! parsedCommands.empty() )
    {
        std::string command = getNextCommand( parsedCommands );

        std::cout << command << std::endl;

        // --versus-local
        if ( command == "--versus-local" )
        {
            if ( gamemodeSet ) throw ConsoleParsingErrorException( "Gamemode setting must be unambiguous" );
            else if ( fileLoaded ) throw ConsoleParsingErrorException( "You can't set gamemode when loading file" );
            else
            {
                gameMode = GameController::MODE_VSLOC;
                gamemodeSet = true;
            }
        }
        else if ( command == "--versus-ai" )
        {
            if ( gamemodeSet ) throw ConsoleParsingErrorException( "Gamemode setting must be unambiguous" );
            else if ( fileLoaded ) throw ConsoleParsingErrorException( "You can't set gamemode when loading file" );
            else
            {
                gameMode = GameController::MODE_VSAI;
                gamemodeSet = true;
            }
        }
        else if ( command == "--versus-network" )
        {
            if ( gamemodeSet ) throw ConsoleParsingErrorException( "Gamemode setting must be unambiguous" );
            else if ( fileLoaded ) throw ConsoleParsingErrorException( "You can't set gamemode when loading file" );
            else
            {
                gameMode = GameController::MODE_VSNET;
                gamemodeSet = true;
            }
        }
        else if ( command == "--load" )
        {
            if ( gamemodeSet ) throw ConsoleParsingErrorException( "You can't load a game when gamemode has been set" );
            else
            {
                loadfile = getNextCommand( parsedCommands );
                fileLoaded = true;

                if ( loadfile == "" ) throw ConsoleParsingErrorException( "You must specify file name" );
            }
        }
        else if ( command == "--unicode" )
        {
            if ( rendermodeSet ) throw ConsoleParsingErrorException( "The render mode setting must be unamibguous" );
            else
            {
                renderMode = 1;
                rendermodeSet = true;
            }
        }
        else if ( command == "--compatible" )
        {
            if ( rendermodeSet ) throw ConsoleParsingErrorException( "The render mode setting must be unamibguous" );
            else
            {
                renderMode = 2;
                rendermodeSet = true;
            }
        }
        else if ( command == "--ip" )
        {
            if ( gamemodeSet && gameMode == GameController::MODE_VSNET )
            {
                ip = getNextCommand( parsedCommands );
                if ( ip == "" )
                    throw ConsoleParsingErrorException( "Network address must be specified for this gamemode" );
                // todo: check ip address validity
            }
            else throw ConsoleParsingErrorException( "Game mode must be set to versus network before setting network address." );
        }
        else if ( command == "--port" )
        {
            if ( gamemodeSet && gameMode == GameController::MODE_VSNET )
            {
                port = getNextCommand( parsedCommands );
                if ( port == "" ) throw ConsoleParsingErrorException( "Network port must be specified for this gamemode" );
                // todo: check port validity
            }
            else throw ConsoleParsingErrorException( "Game mode must be set to versus network before setting network port." );
        }
        else
        {
            throw ConsoleParsingErrorException( "The argument '" + command + "' can't be recognized. See manual for more information." );
        }

    }

    networkaddress = ip + ":" + port;
}

std::string Console::getNextCommand( std::queue<std::string> &commands )
{
    if ( !commands.empty() )
    {
        std::string command = commands.front();
        commands.pop();
        return command;
    } else return "";
}



std::string Console::translateCoords( int location )
{
    stringstream ss;
    int col = location % 8, row = location / 8;
    ss << (char)( 65 + col ) << (row + 1);
    return ss.str();
}

int Console::translateCoords( std::string location )
{
    int col = -1, row = -1;

    if ( location[0] >= 65 && location[0] <= 72 ) col = location[0] - 65;
    if ( location[0] >= 97 && location[0] <= 104 ) col = location[0] - 97;
    if ( location[1] >= 49 && location[1] <= 57 ) row = location[1] - 49;

    return ( col == -1 || row == -1 ? -1 : row * 8 + col );
}
