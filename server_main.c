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

   printf("\nServer %d says hello\n",getpid()); //for debugging

   //TODO: Set up thread pool code

   int fd = open("myfifo1", O_RDONLY); //fifo between server_driver and server_main

   char client_message[50]; //buffer for socket receive for testing

   int server_name;
   //reading from pipe connected to parent process server_driver
   read(fd,&server_name,sizeof(int)); //server now named either 1,2 or 3

   printf("\nServer %d is alive and named!\n",server_name);
   close(fd);

   


      /* creation of the socket */
   int server_socket;
   server_socket = socket(AF_INET, SOCK_STREAM, 0);

   struct sockaddr_in address;
   address.sin_family = AF_INET;


 
   //windows ports maybe: 7400,7401,7402

   //based on server_name, port is assigned
   switch(server_name) {
      case 1:
         address.sin_port = htons(8001); //for local connections
      case 2:
         address.sin_port = htons(8002); //for local connections
      case 3:
         address.sin_port = htons(8003); //for local connections
   }

   //for debugging. shutting down other unused servers so their ports are released
   if (server_name!=1){
      printf("\nserver %d exited\n",server_name);
      exit(0);
   }

   address.sin_addr.s_addr = INADDR_ANY; //for local connetions

   bind(server_socket, (struct sockaddr*)&address,sizeof(address));

   listen(server_socket, 5); //will update second number to reflect max number of customers allowed at a time
   printf("\nserver %d listening for clients\n",server_name);


   //will eventually need to do this within loop so next client can be accepted
   int client_socket;
   client_socket = accept(server_socket, NULL, NULL);


   printf("\nserver %d about to call trainTicketMaster()\n",server_name); //for debugging
   //will eventually assign thread to call this:
   trainTicketMaster(client_socket,server_name);


   //thread will return to pool when client exits program from menu

   sleep(1);

   close(server_socket);

   

   return 0;
}
