/**
 * @file    Piece.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class Piece
 *
 * This file contains prototype of Piece class
 */

#ifndef CHECKERS_PIECE_H
#define CHECKERS_PIECE_H

#include <vector>
#include "Player.h"
#include "GameController.h"

// Forward declaration to avoid circular dependency problems
class Player;
class GameController;

/**
 * Base class for MenPiece and KingPiece
 */
class Piece
{
public:
    /** Owner of this piece */
    Player *owner;

    /** Parent game controller */
    GameController *parent;

    /** Type constant, none */
    static const int TYPE_NONE = 0,
    /** Type constant, men */
     TYPE_MEN = 1,
    /** Type constant, king */
     TYPE_KING = 2;

    /** Piece type */
    const int type;

    /** Default constructor */
    Piece( Player *owner, GameController *parent, int location, int type );

    /**
     * Moves the piece on another location in the game field
     *
     * @param newLocation New location
     */
    void moveTo( int newLocation );

    /**
     * Finds all moves possible with this piece
     *
     * @return Move
     */
    virtual std::pair<std::vector<int>, std::vector<int>> findAllMoves() = 0;

protected:
    /** Piece location in game field */
    int location = -1;
};


#endif //CHECKERS_PIECE_H
