//Andrew Ingle 04/08/2021 - Team I - Final Project
//Has to be built but not run. 
//This is the primary server program, will be executed when server_driver calls execpl


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
   printf("\nServer %d says hello\n",getpid());

   int fd = open("myfifo1", O_RDONLY); //fifo between manager and assistant

   int server_name;
   //reading from pipe connected to managaer
   read(fd,&server_name,sizeof(int));

   printf("\nServer %d is alive and named!\n",server_name);
   close(fd);

   return 0;
}