/**
 * @file    MenPiece.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class MenPiece
 *
 * This file contains prototype of MenPiece class
 */

#ifndef CHECKERS_MENPIECE_H
#define CHECKERS_MENPIECE_H

#include "Piece.h"

/**
 * Men piece
 *
 * Is able to move forward, diagonally by one field,
 * or jump over enemy's piece.
 */
class MenPiece : public Piece
{
public:
    /** Default constructor */
    MenPiece( Player *owner, GameController *parent, int location );

    /**
     * Finds all moves possible with this piece
     *
     * @return Move
     */
    std::pair<std::vector<int>, std::vector<int>> findAllMoves();
};


#endif //CHECKERS_MENPIECE_H
