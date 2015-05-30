#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
using namespace std;

/* A simple server. It sends hello to the client, waits for input data and 
 * sends them back (changing the lower/upper case).
 *
 * This version is able to serve many clients simultaneously (uses select 
 * to find the sockets that need to be served).
 */

int prepareSrvSocket ( const char * listenAddr )
 {
   struct addrinfo * ai;

   if ( getaddrinfo ( listenAddr, "12345", NULL, &ai ) != 0 ) return -1;

   int sock = socket ( ai -> ai_family, SOCK_STREAM, 0 );

   if ( sock == -1 )
    {
      freeaddrinfo ( ai );
      return -1;
    }

   if ( bind ( sock, ai -> ai_addr, ai -> ai_addrlen ) != 0 )
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

bool serveClient ( int clientSock )
 {
   char buffer[100];
   int len = recv ( clientSock, buffer, sizeof ( buffer ), 0 );

   // error or no further data -> finish
   if ( len <= 0 ) return false;

   for ( int i = 0; i < len; i ++ )
    if ( isalpha ( buffer[i] ) )
     buffer[i] ^= 0x20;

   send ( clientSock, buffer, len, 0 );
   // continue (the connection is not to be closed)
   return true;
 }

int main ( int argc, char * argv [] )
 {
   int listenSock = prepareSrvSocket ( "localhost" );

   if ( listenSock == -1 )
    {
      printf ( "error - srv socket\n" );
      return 1;
    }

   vector<int> clients;

   while ( 1 )
    {
      struct sockaddr addr;
      socklen_t addrLen = sizeof ( addr );
       // This initialization was missing in the program I was developing 
       // in the consultation - and the absence caused the segmentation faults.
       // Surprisingly it did not demonstrate in the sequential version.
                                                      
      fd_set rd;
      int    max = listenSock;
      
      FD_ZERO ( &rd );
      FD_SET ( listenSock, &rd );
      
      for ( vector<int>::size_type i = 0; i < clients . size (); i ++ ) 
       {
         FD_SET ( clients[i], &rd );
         if ( clients[i] > max ) max = clients[i];
       }
      
      // wait for either incloming connection (listen sock) 
      // or some data to process
      select ( max + 1, &rd, NULL, NULL, NULL );
      
      if ( FD_ISSET ( listenSock, &rd ) )
       {
         int clientSock = accept ( listenSock, &addr, &addrLen );
         const char * helloMsg = "Welcome to the sample server\n";

         clients . push_back ( clientSock );
         send ( clientSock, helloMsg, strlen ( helloMsg ), 0 );
       }
       
      for ( vector<int>::size_type i = 0; i < clients . size (); i ++ ) 
       if ( FD_ISSET ( clients[i], &rd ) )
        { // data available from client i
          if ( ! serveClient ( clients[i] ) )
           { // client i has finished
             close ( clients[i] );
             clients[i] = clients . back ();
             clients . pop_back ();
             i --;
           }
        }
    }
   close ( listenSock );
   return 0;
 }
