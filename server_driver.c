//Andrew Ingle 04/07/2021 - Team I - Final Project
//Main Driver Programmer for Server, will fork and execute to create servers


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {

   printf("\nServer Driver says hello!\n"); //for debugging

   int server_name = 1; //name of first server will be incremented as we go along

   unlink("myfifo1");
   if (mkfifo("myfifo1", 0666)==-1){    //Create Fifo to send server names to child servers
      printf("Could not create fifo file\n");
      perror("mkfifo() failed");
      return 1;
   }

   //creating 3 servers
   for (int i = 0;i<3;i++){

      pid_t pid = fork();

      if(pid < 0) {
         fprintf(stderr, "fork failed for next server.");
         return 1;
      }
      else if(pid == 0) { //next child server
         // send port to server and change port each time
         execlp("./server_main","server_main",NULL); //system call provided by Andrew
      }
      else {
         wait(NULL);
         printf("that's done");
      }
      sleep(1); //to give time for servers to open
   }

   //opening fifo to send names to servers
   int fd = open("myfifo1", 01); //this waits until child server has opened fifo
      if (fd== -1){
      return 1;
   }

   //sending names to servers
   for (int i=0;i<3;i++){
      write(fd, &server_name, sizeof(int));
      server_name++; //incrementing name
      printf("%d",server_name);
   }


   sleep(10); //for debugging to give time for child servers to print to terminal
   close(fd);
   wait(NULL);
   printf("\nAll child processes complete, Server Driver will exit\n");

   return 0;
}
