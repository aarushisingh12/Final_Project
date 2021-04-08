//Andrew Ingle 04/08/2021 - Team I - Final Project
//Has to be built but not run. 
//This is the primary server program, will be executed when server_driver calls execpl


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
   printf("\nServer %d says hello\n",getpid());
   return 0;
}