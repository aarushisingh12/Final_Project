#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SEATS 40
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// to comipile code, run "gcc -o UICaleb caleb_client.c"

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

void printTrain();
// Prints an ASCII art train
