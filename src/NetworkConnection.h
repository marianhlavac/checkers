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

class NetworkConnection
{
public:
    static const int CONNECTION_NONE = 0, CONNECTION_CLIENT = 1, CONNECTION_SERVER = 2;
    int connectionType = CONNECTION_NONE;
    bool isConnected = false;
    std::string address;


    NetworkConnection( int connectionType );
    void connect();

};


#endif //CHECKERS_NETWORKCONNECTION_H
