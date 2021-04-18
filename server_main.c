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
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include "trainTicketMaster.h"
#include "server_tempFunctions.h"

#define THREAD_NUM 5

//multi thread code
typedef struct Job {
    void (*functionToExecute)(int, int); //this will become void (*trainTicketMaster(int,int));
    int arg1, arg2; //will be for clients socket and server_name
} Job;

Job jobQueue[200];
int jobCount = 0;
pthread_mutex_t mutexQueue;
pthread_cond_t condQueue;

void executeJob(Job* job) {
    job->functionToExecute(job->arg1, job->arg2);
}

void submitJobForExecution(Job job) {
    pthread_mutex_lock(&mutexQueue);
    jobQueue[jobCount] = job;
    jobCount++;
    pthread_mutex_unlock(&mutexQueue);
    pthread_cond_signal(&condQueue);
}

void* startThread(void* args) {
    
        Job job;

        pthread_mutex_lock(&mutexQueue);
        while (jobCount == 0) {
            pthread_cond_wait(&condQueue, &mutexQueue);
        }

        job = jobQueue[0];
       
        for (int i = 0; i < jobCount - 1; i++) {
            jobQueue[i] = jobQueue[i + 1];
        }
        jobCount--;
        pthread_mutex_unlock(&mutexQueue);
        
        executeJob(&job);
    
}


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

   
   pthread_t th[THREAD_NUM];
   pthread_mutex_init(&mutexQueue, NULL);
   pthread_cond_init(&condQueue, NULL);
   int i;
   //creating the threads
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) {
            perror("Failed to create the thread");
        }
    }


      /* creation of the socket */
   int server_socket, c;
   server_socket = socket(AF_INET, SOCK_STREAM, 0);

   if (server_socket == -1){
		printf("Could not create socket");
	}

   struct sockaddr_in server_address, client_address;
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = INADDR_ANY; 
   //windows ports maybe: 7400,7401,7402
   //based on server_name, port is assigned
   switch(server_name) {
      case 1:
         server_address.sin_port = htons(8001); //for local connections
      case 2:
         server_address.sin_port = htons(8002); //for local connections
      case 3:
         server_address.sin_port = htons(8003); //for local connections
   }


   //for debugging. shutting down other unused servers before port binding
   if (server_name!=1){
      printf("\nserver %d exited\n",server_name);
      exit(0);
   }
  
   //Bind
   if( bind(server_socket,(struct sockaddr *)&server_address , sizeof(server_address)) < 0){
	   printf("bind failed");
   }

   listen(server_socket, 5); //will update second number to reflect max number of customers allowed at a time
   printf("\nserver %d listening for clients\n",server_name);


   int client_socket;
   //client_socket = accept(server_socket, NULL, NULL); //if not in accept loop

//live server code
   while( (client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t*)&c)) ){
	    printf("\nConnection accepted from within accept loop");
        printf("\nserver %d about to call trainTicketMaster()\n",server_name); //for debugging
      //will eventually assign thread to call this with pointer to function:
      //trainTicketMaster(client_socket,server_name);
        Job t = {.functionToExecute = &trainTicketMaster, .arg1 = client_socket, .arg2 = server_name };
        submitJobForExecution(t);
   }

   if (client_socket<0){
		perror("\nserver accept failed after accept loops\n");
	}

   //thread will return to pool when client exits program from menu
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join the thread");
        }
    }

   pthread_mutex_destroy(&mutexQueue);
   pthread_cond_destroy(&condQueue);

   close(server_socket);

   printf("\nServer Exited from main\n"); //for debugging

   return 0;
}
