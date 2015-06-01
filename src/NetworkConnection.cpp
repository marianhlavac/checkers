/**
 * @file    NetworkConnection.cpp
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Implementation of class NetworkConnection
 *
 * This file contains prototype of NetworkConnection class
 */

#include "NetworkConnection.h"

#include <chrono>

using namespace std;


NetworkConnection::NetworkConnection( int connectionType, char * address, char * port ) :
        connectionType( connectionType ), address( address ), port( port )
{
    connectionType = CONNECTION_NONE;
    socketnum = -1;
}
NetworkConnection::NetworkConnection( int connectionType, const char * address, const char * port ) :
        connectionType( connectionType )
{
    this->address = (char *) address;
    this->port = (char *) port;
}

bool NetworkConnection::makeConnection()
{
    if ( connectionType == CONNECTION_SERVER )
    {
        int listensock  = prepareServerSocket(address);

        if ( listensock == -1 )
        {
            cerr << "Can't create connection. Error #" << errno << endl;
            return false;
        }

        struct sockaddr addr;
        socklen_t addrLen = sizeof( addrLen );

        cout << "Waiting for client connection..." << endl;

        if ( ( socketnum = accept(listensock, &addr, &addrLen) ) == -1 )
        {
            cerr << "Accepting client's connection failed!" << errno;
            return false;
        }

        return true;
    }
    else {
        socketnum = prepareClientSocket(address);

        if ( socketnum == -1 ) {
            cerr << "Can't create connection. Error #" << errno << endl;
            return false;
        }

        return true;
    }

}

int NetworkConnection::prepareServerSocket(const char *listenAddr)
{
    struct addrinfo * ai;

    if ( getaddrinfo ( listenAddr, port, NULL, &ai ) != 0 ) return -1;

    int sock = socket ( ai->ai_family, SOCK_STREAM, 0 );

    if ( sock == -1 )
    {
        freeaddrinfo ( ai );
        return -1;
    }

    if ( bind ( sock, ai->ai_addr, ai->ai_addrlen ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }

    if ( listen ( sock, 10 ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }
    freeaddrinfo ( ai );
    return sock;
}

int NetworkConnection::prepareClientSocket( const char *listenAddr )
{
    struct addrinfo * ai;

    if ( getaddrinfo ( listenAddr, port, NULL, &ai ) != 0 ) return -1;

    int sock = socket ( ai->ai_family, SOCK_STREAM, 0 );
    if ( sock == -1 )
    {
        freeaddrinfo ( ai );
        return -1;
    }

    if ( connect ( sock, ai->ai_addr, ai->ai_addrlen ) != 0 )
    {
        close ( sock );
        freeaddrinfo ( ai );
        return -1;
    }
    freeaddrinfo ( ai );
    return sock;
}

bool NetworkConnection::receive( string & received )
{
    char buffer[256];

    int len = recv( socketnum, buffer, sizeof( buffer ) - 1, 0);

    if ( len <= 0 ) return false;

    buffer[ len ] = '\0';
    received = string( buffer );

    return true;
}

bool NetworkConnection::sendMessage( string message )
{
    return send( socketnum, message.c_str(), strlen( message.c_str() ), 0 ) != 1;
}

void NetworkConnection::sendHandShake()
{
    if ( ! sendMessage( "CHECKERS_HANDSHAKE" ) ) cerr << errno << endl;
}

void NetworkConnection::waitForHandShake()
{
    string received;

    while ( received != "CHECKERS_HANDSHAKE" )
    {
        receive( received );
    }
}

NetworkConnection::~NetworkConnection()
{
    close( socketnum );
}
