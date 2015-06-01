/**
 * @file    AIPlayer.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class AIPlayer
 *
 * This file contains prototype of AIPlayer class
 */

#include <iostream>
#include <cstdlib>
#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer( GameController *parent ) : Player( parent )
{

}

AIPlayer::~AIPlayer() {

}

pair<int, int> AIPlayer::WaitForInput( )
{
    /*
     * AIPlayer, basic
     * "Dumb" tactic: choose random from all possible turns
     */

    // Fake "thinking" delay
    parent->delay( 2 );

    // Choose random turn
    int idx = rand() % (parent->possibleMoves.size() - 1);
    return parent->possibleMoves.at( this ).at( idx );
}

void AIPlayer::informMove(int from, int to) { }
