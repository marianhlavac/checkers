//
// Created by Marián on 21. 5. 2015.
//

#include "KingPiece.h"

KingPiece::KingPiece( Player *owner, GameController *parent, int location ) : Piece( owner, parent, location, TYPE_KING )
{

}

std::pair< std::vector<int>, std::vector<int> > KingPiece::findAllMoves( )
{
    std::pair< std::vector<int>, std::vector<int> > movesnjumps;

    // All moves left up
    pair<vector<int>, vector<int>> found = diagonalSearch( -1, -1 );
    for ( int jump : found.first ) movesnjumps.first.push_back( jump );
    for ( int jump : found.second ) movesnjumps.second.push_back( jump );

    // All moves right up
    found = diagonalSearch( 1, -1 );
    for ( int jump : found.first ) movesnjumps.first.push_back( jump );
    for ( int jump : found.second ) movesnjumps.second.push_back( jump );

    // All moves left down
    found = diagonalSearch( -1, 1 );
    for ( int jump : found.first ) movesnjumps.first.push_back( jump );
    for ( int jump : found.second ) movesnjumps.second.push_back( jump );

    // All moves right down
    found = diagonalSearch( 1, 1 );
    for ( int jump : found.first ) movesnjumps.first.push_back( jump );
    for ( int jump : found.second ) movesnjumps.second.push_back( jump );

    return movesnjumps;
}

std::pair<std::vector<int>, std::vector<int> > KingPiece::diagonalSearch( int dirx, int diry )
{
    char color = owner->color;
    vector<int> moves, jumps;
    int x = 0, y = 0;
    bool jumpingover = false;

    while ( ! parent->outOfFieldRelative( location, x, y ) )
    {
        if ( x == 0 && y == 0 ) { x += dirx; y += diry; continue; }
        Piece *piece = parent->getPieceRelative( location, x, y );

        if ( piece != nullptr )
        {
            // We can jump over enemy's piece
            if ( piece->owner->color != color )
                jumpingover = true;

            // But we can't jump over own pieces
            else
                break;
        }
        else
        {
            // We can move or jump to free place
            if ( jumpingover )
            {
                jumps.push_back( location + x + y*8 );
                // But jump can be only one
                break;
            }
            else
                moves.push_back( location + x + y*8 );

            jumpingover = false;
        }

        x += dirx; y += diry;
    }

    return make_pair( moves, jumps );
}
