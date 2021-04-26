/*
 * Created by: Maxwell Meckling
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
//#include <sys/shm.h>  // Possibly also for shared memory
#include <sys/mman.h>   // Needed for shared memory
//#include <sys/stat.h> //I don't think this one helps
#include <fcntl.h>      // Needed for shared memory
#include <semaphore.h>  // Used for semaphores
#include <stdbool.h>    // Used to declare boolean values
#include <unistd.h>     // Used for ftruncate in shared memory

#ifndef TRAINSEATING_H
#define TRAINSEATING_H

#define STRING_BUFFER_MAX 300//for tcp 

typedef struct StructForSeating {
    //string for the date.
    char dateStr[15];
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
}dates;

typedef struct customerInfo {
    char fullName[60];
    char dateOfBirth[20];
    char gender[10];
    char governmentID[20];
    int dayOfTravel; //1 for today, 2 for tomorrow, convenience property for other functions
    char dateOfTravel[20]; //if dayOfTravel == 1 for today, can use to fill in date if needed
    int numberOfTravelers;
    int ticketNumber; //assigned when confirming reservation
    int bookedSeats[27]; //assigned after selectAvailableSeats()
}customerInfo;


int trainSeating();

#endif /* TRAINSEATING_H */

