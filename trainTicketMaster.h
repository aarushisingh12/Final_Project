//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions
//and the functions needed to handle the server processing of the next client/customer's selections.
//When new client connects to chosen server’s port,
//server commits a thread to run this master function
//loop continues until until client ends session by choosing “exit the program”from main menu


#ifndef trainTicketMaster_h
#define trainTicketMaster_h

#include "trainSeating.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define STRING_BUFFER_MAX 300//for tcp

//sturct used to hold customers info, during reservation process
typedef struct customerInfo {
    char fullName[60];
    char dateOfBirth[20];
    char gender[10];
    char governmentID[20];
    int dayOfTravel; //1 for day, 2 for tomorrow
    char dateOfTravel[20];// if dayOfTravel = 1, can use getTodaysDate()
    int numberOfTravelers;
    int ticketNumber; //assigned when confirming reservation with assignTicketNumber() func
    int bookedSeats[27]; //assigned after selectAvailableSeats()

}customerInfo;

typedef struct Date {
     char today[20];
     char tomorrow[20];
} dates;

int trainTicketMaster(int, int,availableSeats*,int);

#endif /* trainTicketMaster_h */
