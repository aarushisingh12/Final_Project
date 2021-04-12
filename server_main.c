//Andrew Ingle 04/08/2021 - Team I - Final Project
//Has to be built but not run.
//This is the primary server program, will be executed when server_driver calls execpl
//This program receives server name from server_driver parent process, assigns itself a port based on name
//manages thread pool and listens for next client, and assigns thread to run trainTicketMaster() for each customer
//when customer exists program via menu selection, thread returns to pool

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "trainTicketMaster.h"
#include "server_tempFunctions.h"

int main() {

//NEED TO ADD SHARED MEMORY ACCESS

   printf("\nServer %d says hello\n",getpid());

   //TODO: Set up thread pool code

   int fd = open("myfifo1", O_RDONLY); //fifo between manager and assistant

   char client_message[50]; //buffer for socket receive for testing

   int server_name;
   //reading from pipe connected to managaer
   read(fd,&server_name,sizeof(int));

   printf("\nServer %d is alive and named!\n",server_name);
   close(fd);
   
      /* creation of the socket */
   int server_socket;
   server_socket = socket(AF_INET, SOCK_STREAM, 0);

   struct sockaddr_in address;
   address.sin_family = AF_INET;


   //address.sin_port = htons(8001); //for testing on local linux connections

   switch(server_name) {
      case 1:
         address.sin_port = htons(7400); //for local connections
      case 2:
         address.sin_port = htons(7401); //for local connections
      case 3:
         address.sin_port = htons(7402); //for local connections
   }

   address.sin_addr.s_addr = INADDR_ANY; //for local connetions

   bind(server_socket, (struct sockaddr*)&address,sizeof(address));

   listen(server_socket, 5); //will update second number to reflect max number of customers allowed at a time
   
   //will eventually need to do this within loop so next client can be accepted
   int client_socket;
   client_socket = accept(server_socket, NULL, NULL);

   //will eventually assign thread to call this:
   trainTicketMaster(client_socket);

   //thread will return to pool when client exits program from menu

   // //for debugging
   // recv(client_socket,client_message,sizeof(client_message),0); 

   // //for testing
   // printf("\nServer %d receives following message from client:\n", server_name);
   // printf("%s",client_message);
   sleep(1);

   close(server_socket);
   

   return 0;
}
