#include <thread>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

/* A simple server. It sends hello to the client, waits for input data and 
 * sends them back (changing the lower/upper case).
 *
 * This version is able to serve many clients simultaneously (uses c++11 threads).
 * compile with   -std=c++11 -lpthread
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

void serveClient ( int clientSock )
 {
   const char * helloMsg = "Welcome to the sample server\n";
   send ( clientSock, helloMsg, strlen ( helloMsg ), 0 );
   
   while ( 1 )
    {
      char buffer[100];
      int len = recv ( clientSock, buffer, sizeof ( buffer ), 0 );

      // error or no further data -> finish
      if ( len <= 0 ) break;

      for ( int i = 0; i < len; i ++ )
       if ( isalpha ( buffer[i] ) )
        buffer[i] ^= 0x20;

      send ( clientSock, buffer, len, 0 );
    }
   close ( clientSock );
 }

int main ( int argc, char * argv [] )
 {
   int listenSock = prepareSrvSocket ( "localhost" );

   if ( listenSock == -1 )
    {
      printf ( "error - srv socket\n" );
      return 1;
    }

   while ( 1 )
    {
      struct sockaddr addr;
      socklen_t addrLen = sizeof ( addr ); 
       // This initialization was missing in the program I was developing 
       // in the consultation - and the absence caused the segmentation faults.
       // Surprisingly it did not demonstrate in the sequential version.

      int clientSock = accept ( listenSock, &addr, &addrLen );
      
      // create a separate thread to handle the client communcation
      thread  x ( serveClient, clientSock );
      // detach the thread (the thread is independent)
      x . detach ();
    }
   close ( listenSock );
   return 0;
 }
