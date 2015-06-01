/**
 * @file    NetworkConnection.h
 * @author  Marián Hlaváč
 * @date    May, 2015
 * @bug     No known bugs.
 * @brief   Prototype of class NetworkConnection
 *
 * This file contains prototype of NetworkConnection class
 */

#ifndef CHECKERS_NETWORKCONNECTION_H
#define CHECKERS_NETWORKCONNECTION_H

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cctype>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

/**
 * Object providing network connection ability
 */
class NetworkConnection
{
public:
    /** Connection type constant, none */
    static const int CONNECTION_NONE = 0,
    /** Connection type constant, client connection */
            CONNECTION_CLIENT = 1,
    /** Connection type constant, server connection */
            CONNECTION_SERVER = 2;

    /**
     * Prepares a server socket.
     *
     * This code snippet was taken from assignment attachment, net_2015.tgz
     * https://edux.fit.cvut.cz/courses/BI-PA2/semestralka
     *
     * @author Ladislav Vagner
     * @date 26 April, 2015
     * @param listenAddr Listening network address
     * @return Socket number ( file descriptor )
     */
    int prepareServerSocket ( const char * listenAddr );

    /**
     * Prepares a client socket.
     *
     * This code snippet was taken from assignment attachment, net_2015.tgz
     * https://edux.fit.cvut.cz/courses/BI-PA2/semestralka
     *
     * @author Ladislav Vagner
     * @date 26 April, 2015
     * @param listenAddr Listening network address
     * @return Socket number ( file descriptor )
     */
    int prepareClientSocket ( const char * listenAddr );

    /** Default constructor */
    NetworkConnection( int connectionType, char * address, char * port );

    /** Constructor with const char * */
    NetworkConnection( int connectionType, const char * address, const char * port );

    /** Destructor */
    ~NetworkConnection();

    /**
     * Makes the connection. Waits until other side connects.
     *
     * @return Success
     */
    bool makeConnection();

    /**
     * Receives a message over network. Waits until something appears.
     *
     * @param[out] received Received message
     * @return Success
     */
    bool receive( std::string & received );

    /**
     * Sends a message over network.
     *
     * @param message Message to send
     * @return Success
     */
    bool sendMessage( std::string message );

    /**
     * Sends a handshake.
     */
    void sendHandShake();

    /**
     * Waits for a handshake.
     */
    void waitForHandShake();

private:
    /** Connection type */
    int connectionType;

    /** Socket number */
    int socketnum;

    /** Network address */
    char * address;

    /** Network port */
    char * port;
};


#endif //CHECKERS_NETWORKCONNECTION_H
