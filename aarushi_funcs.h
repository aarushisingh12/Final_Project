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

#include "trainTicketMaster.h"
#include "server_tempFunctions.h"

//will have to comment out versions in server_tempFunctions .c and .h to with rest of system
// int writeToSummaryFile(customerInfo,int server_name,int socket);
// int displayTicketInfo(int ticketNumber, int socket);


#endif /* aarushi_funcs.h */
