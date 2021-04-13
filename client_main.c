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

#include "andrew_clientFuncs.h"

#define STRING_BUFFER_MAX 300//for tcp 

void reservationPortal(int);
void acceptReceipt(int);

int main() {
   printf("\nClient says hello\n"); //for debugging

   char client_message[50] = "Client message to server"; //for testing, buffer for socket send for testing

   //printf("\nWhich server do you want to connect to (1, 2 or 3): \n");

   int chosenServer;

   //scanf("%d", &chosenServer);

   //client side socket creation
   int sock;
   sock = socket(AF_INET,SOCK_STREAM,0); // for tcp
   struct sockaddr_in server_address;
   server_address.sin_family = AF_INET;

   server_address.sin_port = htons(8001);//for local on linux, was using for testing

   //ports need to be appropriate for current OS
    //windows ports maybe: 7400,7401,7402
   // switch(chosenServer) {
   //       case 1:
   //          server_address.sin_port = htons(8001); //for local connections
   //       case 2:
   //          server_address.sin_port = htons(8002); //for local connections
   //       case 3:
   //          server_address.sin_port = htons(8003); //for local connections
   // }

   server_address.sin_addr.s_addr = INADDR_ANY; //for local

   //for connecting to receive from Server
   printf("\nclient going to attempt to connect\n");
   int connection = connect(sock,(struct sockaddr *) &server_address,
   sizeof(server_address));
   if (connection == -1){
       printf("There is an issue with connection!!!\n");
    }

     printf("\nclient about to call reservation portal\n"); 
    reservationPortal(sock);

    sleep(1);
    //close(sock);

   return 0;
}
