/**
 * @file    GameController.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class GameController
 *
 * This file contains prototype of GameController class
 */

#ifndef CHECKERS_GAMECONTROLLER_H
#define CHECKERS_GAMECONTROLLER_H

#include "UIRenderer.h"
#include "Piece.h"
#include "NetworkConnection.h"
#include <map>
#include <iostream>

// Forward declaration to avoid circular dependency problems
class UIRenderer;
class Piece;
class Player;

/**
 * Object for directing the game, top-level game logic
 */
class GameController
{
public:
    /** Mode constant, not set */
    static const int MODE_NOTSET = -1,
    /** Mode constant, versus local player */
            MODE_VSLOC = 0,
    /** Mode constant, versus AI player */
            MODE_VSAI = 1,
    /** Mode constant, versus network player */
            MODE_VSNET = 2;

    /** Number of instances */
    static int instances;

    /** Game mode */
    int gameMode;

    /** Number of ticks elapsed */
    int ticks;

    /** Indicates if game has ended */
    bool gameHasEnded;

    /** Indicates if current turn is jump sequence */
    bool jumpSequence;

    /** Indicates if used sent invalid input */
    bool invalidInput;

    /** Indicates if board is rotated ( by 180 dgr ) */
    bool boardRotated;

    /** Player on turn */
    Player * onTurn;

    /** Winner of the game */
    Player * winner;

    /** Selected renderer */
    UIRenderer * renderer;

    /** All possible moves of both players */
    std::map<Player*, std::vector<std::pair<int,int>>> possibleMoves;

    /** Player 1 */
    Player * firstplayer;

    /** Player 2 */
    Player * secondplayer;

    /** Network connection */
    NetworkConnection * net;

    /** Game ID used for network connection communication */
    int netGameId;

    /** Default constructor */
    GameController( );

    /** Destructor */
    ~GameController( );

    /**
     * Prepares new local game.
     *
     * @param nick Nickname of player 1
     * @param nick2 Nickname of player 2
     */
    void prepareNewGame( std::string nick, std::string nick2 );

    /**
     * Loads previously saved local/ai game from file using Savefile class.
     *
     * @param loadInfo Saved data stream
     * @return Success
     */
    bool loadGame( std::istream & loadInfo );

    /**
     * Prepares new network game.
     *
     * @param address IP address
     * @param port Network port
     * @param nick Nickname of player 1
     * @param nick2 Nickname of player 2
     */
    void prepareNewNetworkGame( std::string & address, std::string & port, std::string nick, std::string nick2 );

    /**
     * Tick method - todo: ted fakt ne
     */
    void tick( );

    /**
     * Makes delay specified in seconds.
     *
     * @param s Number of seconds
     * @bug The delay has very low resolution (in seconds), so it varies by one second.
     */
    void delay( int s );

    /**
     * Gets piece from the game field by its index.
     *
     * @param index Piece index
     * @return Piece object
     */
    Piece *getPiece( int index ) const;

    /**
     * Sets piece at specifed index.
     *
     * @param index Index
     * @param piece Piece object to be set
     */
    void setPiece( int index, Piece * piece );

    /**
     * Gets piece from the game field by its relative position from specified index.
     *
     * @param from Default location
     * @param byx Shift by on x axis
     * @param byy Shift by on y axis
     * @return Piece object
     */
    Piece *getPieceRelative( int from, int byx, int byy ) const;

    /**
     * Sets piece at relative position from specified index.
     *
     * @param from Default location
     * @param byx Shift by on x axis
     * @param byy Shift by on y axis
     * @param piece Piece object to be set
     */
    void setPieceRelative( int from, int byx, int byy, Piece * piece );

    /**
     * Gets count of possible player's moves.
     *
     * @param player Player
     * @return Number of possible moves
     */
    int numOfPossibleMoves(Player *player) const;

    /**
     * Checks if specified relative position is out of field or not.
     *
     * @param from Default location
     * @param byx Shift by on x axis
     * @param byy Shift by on y axis
     * @return Is out of field
     */
    bool outOfFieldRelative( int from, int byx, int byy ) const;

    /**
     * Finds all possible moves for player and saves it to possibleMoves variable.
     * Have to be called before calling other moves-related methods, eg. numOfPossibleMoves,
     * isTurnValid, etc.
     *
     * @param player Player
     * @param[out] isJumps Sets to true if the turns are jumps
     */
    void findPossibleMoves(Player *player, bool *isJumps = nullptr);

private:
    /**
     * Checks if turn is valid.
     *
     * @param turn Turn
     * @return Is valid
     */
    bool isTurnValid( std::pair< int, int > turn ) const;

    /**
     * Discards any pieces between two locations ( only diagonally! )
     *
     * @param from From location
     * @param to To location
     */
    void discardAnyBetween( int from, int to );

    /**
     * Finds out if this turn is jump sequence
     *
     * @return Is jump sequence
     */
    bool isJumpSequence( );

    /**
     * Ends this turn. Toggles the onTurn variable.
     */
    void endOfTurn( );

    /**
     * Converts all mens on opposite side to kings.
     */
    void conversionToKings( );

    /**
     * Ends the game.
     *
     * @param winner Winner player
     */
    void gameOver( Player * winner );

    /**
     * Saves the game using Savefile class
     */
    void saveGame( );

    /**
     * Fills the field with mens on correct starting positions.
     * Used for initialization.
     */
    void fillFieldWithMens( );

    /**
     * Parse initialization data incoming through network.
     * Used for initialization
     *
     * @param[in] received Received message
     * @param[out] color Player color
     * @param[out] nick Player nick
     * @param[out] netgameid Game ID
     */
    void parseNetInitData( std::string & received, char & color, std::string & nick, int & netgameid );

    /** Game field */
    Piece ** field;
};


#endif //CHECKERS_GAMECONTROLLER_H
