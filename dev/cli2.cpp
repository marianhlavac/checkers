#include <cstdio>
#include <cstring>
#include <cctype>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

/* Client - reads the data from the standard input until the user 
 * sends EOF (Ctrl-D).
 *
 */

int prepareCliSocket ( const char * listenAddr, int port )
 {
   struct addrinfo * ai;
   char portTx[20];

   snprintf ( portTx, sizeof ( portTx ), "%d", port );
   if ( getaddrinfo ( listenAddr, portTx, NULL, &ai ) != 0 ) return -1;

   int sock = socket ( ai -> ai_family, SOCK_STREAM, 0 );
   if ( sock == -1 )
    {
      freeaddrinfo ( ai );
      return -1;
    }

   if ( connect ( sock, ai -> ai_addr, ai -> ai_addrlen ) != 0 )
    {
      close ( sock );
      freeaddrinfo ( ai );
      return -1;
    }
   freeaddrinfo ( ai );
   return sock;
 }

void communicate ( int cliSock )
 {
   while ( 1 )
    {
      fd_set rd;
      FD_ZERO ( &rd );
      FD_SET ( cliSock, &rd );
      FD_SET ( STDIN_FILENO, &rd );
      
      // We do not know what to do:
      //  - either there is something to process from the standard input
      //  - or there are some data sent from the server
      // We use select () to wait for either the socket or the standard input
      
      if ( select ( cliSock + 1, &rd, NULL, NULL, NULL ) <= 0 ) return;

      if ( FD_ISSET ( STDIN_FILENO, &rd ) )
       { // data available in the standard input: send them to the server
         char buffer[50];
         int l = read ( STDIN_FILENO, buffer, sizeof ( buffer ) );
         if ( l <= 0 ) return;
         send ( cliSock, buffer, l, 0 );
       }
      else if ( FD_ISSET ( cliSock, &rd ) )
       { // data available in the socket: display them
         char buffer[50];
         int l = recv ( cliSock, buffer, sizeof ( buffer ) - 1, 0 );
         if ( l <= 0 ) return;
         buffer[l] = 0;
         printf ( "%s", buffer );
       }
    }
 }

int main ( int argc, char * argv [] )
 {
   int cliSock = prepareCliSocket ( "localhost", 12345 );

   if ( cliSock == -1 )
    {
      printf ( "error - cli socket\n" );
      return 1;
    }
   communicate ( cliSock );
   close ( cliSock );

   return 0;
 }



