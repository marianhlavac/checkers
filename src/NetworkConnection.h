//
// Created by Marián on 30. 5. 2015.
//

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
#include <chrono>

class NetworkConnection
{
public:
    static const int CONNECTION_NONE = 0, CONNECTION_CLIENT = 1, CONNECTION_SERVER = 2;
    bool isConnected = false;

    int prepareServerSocket ( const char * listenAddr );
    int prepareClientSocket ( const char * listenAddr );

    NetworkConnection( int connectionType, char * address, char * port );
    NetworkConnection( int connectionType, const char * address, const char * port );
    ~NetworkConnection();
    bool makeConnection();
    bool receive( std::string & received );
    bool sendMessage( std::string message );
    void sendHandShake();
    void waitForHandShake();
    double getHandShakeLatency();

private:
    int connectionType = CONNECTION_NONE;
    int socketnum = -1;
    char * address, * port;
    double latency;
};


#endif //CHECKERS_NETWORKCONNECTION_H
