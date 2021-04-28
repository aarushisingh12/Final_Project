/*
 * Created by: Maxwell Meckling
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <sys/shm.h>  // Possibly also for shared memory
#include <sys/mman.h>   // Needed for shared memory
#include <sys/stat.h> //I don't think this one helps
#include <fcntl.h>      // Needed for shared memory
#include <semaphore.h>  // Used for semaphores
#include <stdbool.h>    // Used to declare boolean values
#include <unistd.h>     // Used for ftruncate in shared memory

#include <sys/types.h> //need these for sockets
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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


//int trainSeating();

//calculates and then returns the number of available seats for a given day
int countNumberOfAvailableSeats(availableSeats*);

//Returns 0 or 1 based on the passed dayOfTravel variable to match which day we should be on.
//Looks at the int, not the string
int matchDayOfTravel(availableSeats*, int);

//helps with sending a message through tcp
void seatingSendMessageToClient(char*, int);

//Function for moving data to a new day:
//We copy day2 into day1 and reset day2.
void updateDays(availableSeats*, char[15]);

//accesses shared memory to assign next available ticket number to customer
//then increments ticket number for next customer
//returns int ticket number
int assignTicketNumber(customerInfo, int, availableSeats*);

//needs to be synchronized 
//checks shared memory using customers numberOfTravelers
bool checkIfAvailableSeats(int, int, int, availableSeats*);

//needs to be synchronized
//shows seats customer selects starting index (seat) and #of travelers fills in seats
//accessess shared memory to read seats avaialbe and copies to string buffer and then sends to client via tcp
void displayAvailableSeats(int, int, int, availableSeats*);

//needs to be synchronized
//accesses shared memory and alows customer to select from available seats and writes to shared memory and saves seats to customer struct copy
//will use int nextCustomer.dayOfTravel and mextCustomer.numberOfTravelers
//had to add addedSeatsIf Modified for when just adding select number number of seats
customerInfo selectAvailableSeats(customerInfo, int, int, availableSeats*);

//Frees the customer's seats and frees those seats in shared memory too
customerInfo freeCustomersSeatsInSharedMem(customerInfo, int, int, availableSeats*);

#endif /* TRAINSEATING_H */

