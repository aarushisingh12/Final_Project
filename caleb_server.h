
#ifndef caleb_server_h
#define caleb_server_h

#include "trainTicketMaster.h"

#define STRING_BUFFER_MAX 300//for tcp
#define SEATS 40
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// to comipile code, run "gcc -o UICaleb caleb_client.c"

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


int mainMenu(int socket);

//will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
customerInfo reservationMenu(int socket);

//menu that asks customer via tcp if they want to confirm reservation, returns true if yes, else false
bool confirmReservationMenu();

//will ask for ticket customer via tcp for ticket number, returns ticket number
int ticketInquiryMenu(int socket);

//asks what fields customer want to modifiy, returns struct holding customers modified info //have to get ticket number
customerInfo modifyReservationMenu(int socket);

//cancel confirmation sent over tcp if customer sends back yes then returns true, else false
bool cancelMenu(int socket);

/*
int readFromUser();
// Starts the client reading process

int reservation();
// UI for making a reservation

int inquiry(int ticketNumber);
// UI for diplaying a ticket

int modifyTicket(int ticketNumber);
// UI for modifying a ticket

int cancelTicket(int ticketNumber);
// UI for canceling a ticket reservation
*/

void printTrain();
// Prints an ASCII art train


#endif /* caleb_server_h */
