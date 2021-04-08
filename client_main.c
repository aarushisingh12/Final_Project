//Andrew Ingle 04/08/2021 - Team I - Final Project
//general client main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
   printf("\nClient says hello\n");

   char client_message[50] = "Client message to server"; //buffer for socket send for testing
   
   //client side socket creation
   int sock;
   sock = socket(AF_INET,SOCK_STREAM,0); // for tcp
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(8001); //for local
   server_address.sin_addr.s_addr = INADDR_ANY; //for local
   //previous attempts to get server to work remotely
   //server_address.sin_addr.s_addr = inet_addr("10.203.72.24");
   //inet_pton(AF_INET, "10.203.72.24", &(server_address.sin_addr));

   //for connecting to receive from Server
   int connection = connect(sock,(struct sockaddr *) &server_address,
   sizeof(server_address));
   if (connection == -1){
       printf("There is an issue with connection!!!\n\n");
    }
    send(sock,client_message,sizeof(client_message),0);
    sleep(1);
    close(sock);

   return 0;
}