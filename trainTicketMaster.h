//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions
//and the functions needed to handle the server processing of the next client/customer's selections.
//When new client connects to chosen server’s port,
//server commits a thread to run this master function
//loop continues until until client ends session by choosing “exit the program”from main menu


#ifndef trainTicketMaster_h
#define trainTicketMaster_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <semaphore.h>


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

typedef struct StructForSeating {
    //int for the date (1 or 2)
    int dateInt;
    //int for keeping track of which ticket number we are on each day.
    //ticketNumber will start at 1 and increment from there.
    int ticketNumber;
    //int array for the seats. 
    //0 means the seat is open and 1 means it is already taken.
    //There are 27 seats total in three rows and nine columns
    //(just like the assignment document shows).
    int seats[27]; 
}availableSeats;


typedef struct Date {
     char today[20];
     char tomorrow[20];
} dates;

int trainTicketMaster(int, int,availableSeats*,int,sem_t *reader, sem_t *writer);

#endif /* trainTicketMaster_h */
