//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions 
//and the functions needed to handle the server processing of the next client/customer's selections. 
//When new client connects to chosen server’s port, 
//server commits a thread to run this master function 
//loop continues until until client ends session by choosing “exit the program”from main menu


#ifndef trainTicketMaster_h
#define trainTicketMaster_h


#include <stdio.h>

#define STRING_BUFFER_MAX 300//for tcp 

//sturct used to hold customers info, during reservation process
typedef struct customerInfo {
    char fullName[60];
    char dateOfBirth[20];
    char gender[10];
    char governmentID[20];
    char dateOfTravel[20];
    int numberOfTravelers;
    int ticketNumber; //assigned when confirming reservation

}customerInfo;

#endif /* trainTicketMaster_h */
