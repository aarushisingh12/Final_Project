#ifndef aarushi_funcs_h
#define aarushi_funcs_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "andrew_trainTicketMaster.h"
#include "max_trainSeating.h"

#include "andrew_serverFuncs.h"

#include <time.h> //for date



//will have to comment out versions in server_tempFunctions .c and .h to with rest of system
void writeToSummaryFile(customerInfo,int server_name,int socket);
void displayTicketInfo(int ticketNumber, int socket);
customerInfo retrieveCustomersInfo(int ticketNumber);
void cancelReservation(customerInfo customerMods, int socket);
void modifyReservation(customerInfo customerMods, int server_name, int socket);
struct Date getTomorrowsDate();

#endif /* aarushi_funcs.h */
