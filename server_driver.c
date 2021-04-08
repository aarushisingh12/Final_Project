//Andrew Ingle 04/07/2021 - Team I - Final Project
//Main Driver Programmer for Server, will fork and execute to create servers

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
   
   printf("\nServer Driver says hello!\n"); //for debugging

   //creating 3 servers
   for (int i = 0;i<3;i++){

      pid_t pid = fork();
   
      if(pid < 0) {
         fprintf(stderr, "fork failed for next server.");
         return 1;
      } 
      else if(pid == 0) { //next child server
         //server_main program launch
         execlp("./server_main","server_main",NULL); //system call provided by Andrew
      }
   }

   /* parent process */
	/* parent will wait for the child to complete */
   sleep(2); //for debugging to give time for servers to print to terminal
   wait(NULL);
	printf("All child processes complete, Server Driver will exit\n");
	
   return 0;
}