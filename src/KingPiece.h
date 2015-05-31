/**
 * @file    KingPiece.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class KingPiece
 *
 * This file contains prototype of KingPiece class
 */

#ifndef CHECKERS_KINGPIECE_H
#define CHECKERS_KINGPIECE_H

#include "Piece.h"

/**
 * King piece
 *
 * Is able to move any direction, diagonally, any count of fields.
 */
class KingPiece : public Piece
{
public:
    /** Default constructor */
    KingPiece( Player *owner, GameController *parent, int location );

    /**
     * Finds all moves possible with this piece.
     *
     * @return Move
     */
    std::pair<std::vector<int>, std::vector<int>> findAllMoves();

    /**
     * Does the diagonal search and returns all possible moves
     * in that direction.
     *
     * @param dirx X direction ( -1 or 1 )
     * @param diry Y direction ( -1 or 1 )
     * @return Vector of moves and vector of jumps
     */
    std::pair<std::vector<int>, std::vector<int>> diagonalSearch( int dirx, int diry );
};


#endif //CHECKERS_KINGPIECE_H
