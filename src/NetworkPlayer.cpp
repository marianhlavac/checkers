//
// Created by Marián on 11. 5. 2015.
//

#include <sstream>
#include "NetworkPlayer.h"

using namespace std;

NetworkPlayer::NetworkPlayer( GameController *parent ) : Player( parent )
{

}

pair<int, int> NetworkPlayer::WaitForInput( )
{
    string receivedInput;
    int from, to, ticks, netgameid;

    // Receive input over net
    parent->net->receive( receivedInput );

    // Parse incoming stuff
    parseIncoming( receivedInput, from, to, ticks, netgameid );

    // Check if netgameid is correct
    if ( netgameid != parent->netGameId )
        return make_pair( -6, -6 );

    // Check if game is in sync
    if ( ticks != parent->ticks )
        return make_pair( -6, -6 );

    // All seems correct, rotate the input and pass
    return make_pair( 63 - from, 63 - to );
}

void NetworkPlayer::parseIncoming(string &recv, int &from, int &to, int &ticknum, int &netgameid)
{
    stringstream ss;
    string fromstr, tostr, tickstr, ngstr;

    ss.str( recv );

    getline( ss, fromstr, ';' );
    getline( ss, tostr, ';' );
    getline( ss, tickstr, ';' );
    getline( ss, ngstr, ';' );

    from = stoi( fromstr );
    to = stoi( tostr );
    ticknum = stoi( tickstr );
    netgameid = stoi( ngstr );
}

void NetworkPlayer::informMove(int from, int to)
{
    parent->net->sendMessage( to_string( from ) + ";" + to_string( to ) + ";" +
            to_string( parent->ticks ) + ";" + to_string( parent->netGameId ) );
}
