#include <cstdio>
#include <cstring>
#include <cctype>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
using namespace std;

/* A simple client. The message is taken from the command line 
 * and sent to the server.
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

void recvPrint ( int cliSock )
 { // receive & print everything until newline.
   while ( 1 )
    {
      char buffer[50];
      // the reply may be long - we read it in a loop
      int l = recv ( cliSock, buffer, sizeof ( buffer ) - 1, 0 );
      // l < 0 -> error, l == 0 -> finished
      if ( l <= 0 ) return;
      buffer[l] = 0;
      printf ( "%s", buffer );
      // if newline -> return
      if ( index ( buffer, '\n' ) ) return;
    }
 }

void communicate ( int cliSock, const char * msg )
 {
   char newline = '\n';
   recvPrint ( cliSock );

   // send the buffer 
   send ( cliSock, msg, strlen ( msg ), 0 );
   // add newline
   send ( cliSock, &newline, 1, 0 );
   
   recvPrint ( cliSock );
 }

int main ( int argc, char * argv [] )
 {
   if ( argc < 2 ) 
    {
      printf ( "Usage: %s <msg>\n", argv[0] );
      return 1;
    }
   
   int cliSock = prepareCliSocket ( "localhost", 12345 );

   if ( cliSock == -1 )
    {
      printf ( "error - cli socket\n" );
      return 1;
    }
   communicate ( cliSock, argv[1] );
   close ( cliSock );
   return 0;
 }



