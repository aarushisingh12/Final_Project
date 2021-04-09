//Andrew Ingle 04/08/2021 - Team I - Final Project
//Has to be built but not run.
//This is the primary server program, will be executed when server_driver calls execpl


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

int server_main() {
   printf("\nServer %d says hello\n",getpid());

   int fd = open("myfifo1", O_RDONLY); //fifo between manager and assistant

   int server_name;
   //reading from pipe connected to managaer
   read(fd,&server_name,sizeof(int));

   printf("\nServer %d is alive and named!\n",server_name);
   close(fd);

   if (server_name == 1){
         printf("getting there!\n");

      char client_message[50]; //buffer for socket receive for testing
         /* creation of the socket */
      int server_socket;
      server_socket = socket(AF_INET, SOCK_STREAM, 0);

      struct sockaddr_in address;
      address.sin_family = AF_INET;
      switch(server_name) {
         case 1:
            address.sin_port = htons(7400); //for local connections
         case 2:
            address.sin_port = htons(7401); //for local connections
         case 3:
            address.sin_port = htons(7402); //for local connections
      }
         printf("\nServer %d is alive and named!\n",server_name);

      address.sin_addr.s_addr = INADDR_ANY; //for local connetions

      bind(server_socket, (struct sockaddr*)&address,sizeof(address));
      listen(server_socket, 5);

      int client_socket;
      client_socket = accept(server_socket, NULL, NULL);

      recv(client_socket,client_message,sizeof(client_message),0);
      printf("\nServer %d receives following message from client:\n", server_name);
      printf("%s",client_message);
      sleep(1);

      close(server_socket);
   }

   return 0;
}
