
#ifndef andrew_serverFuncs_h
#define andrew_serverFuncs_h

#include "andrew_trainTicketMaster.h"
#include "max_trainSeating.h"

#define STRING_BUFFER_MAX 300//for tcp

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h> //need these for sockets
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <time.h> //for date


struct Date getTodaysDate();


 //send "receipt" code to customer via tcp (client will then know to run acceptReceipt() func)
//then sends receipt data in form of strings (client acceptReceipt func will create/open receipt file print)
void sendReceipt(customerInfo nextCustomer, int socket, int server_name);

void modifyReservation(customerInfo customerMods, int server_name, int socket);

//needs to close socket and have process exit/return thread to pool
int exitProgram(int socket,availableSeats*, int);



#endif /* andrew_serverFuncs.h */
