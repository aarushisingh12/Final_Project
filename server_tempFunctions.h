
#ifndef server_tempFunctions_h
#define server_tempFunctions_h

#include "trainTicketMaster.h"
#include "trainSeating.h"

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

//to use:   char date[20];
//          strcpy(date,getTodaysDate().today)
struct Date getTodaysDate();



//new functions related to modifying reservation//ask Andrew

//customerInfo retrieveCustomersInfo(int ticketNumber); //uses ticket number to access sumary files and save and return customer struct

// customerInfo freeCustomersSeatsInSharedMem(customerInfo customerMods,int travelersToRemove);


// int mainMenu(int socket);


//will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
//customerInfo reservationMenu(int socket);


// //needs to be synchronized //checks shared memory using customers numberOfTravelers
// bool checkIfAvailableSeats(int dayOfTravel, int numberOfTravelers,int socket);


// //menu that asks customer via tcp if they want to confirm reservation, returns true if yes, else false
// bool confirmReservationMenu();



// //needs to be synchronized
// //shows seats customer selects starting index (seat) and #of travelers fills in seats
// //accessess shared memory to read seats avaialbe and copies to string buffer and then sends to client via tcp
// void displayAvailableSeats(int dayOfTravel,int numberOfTravelers, int socket);



// //needs to be synchronized
// //accesses shared memory and alows customer to select from available seats and writes to shared memory and saves seats to customer struct copy
// //will use int nextCustomer.dayOfTravel and mextCustomer.numberOfTravelers
// //had to add addedSeatsIf Modified for when just adding select number number of seats
// customerInfo selectAvailableSeats(customerInfo nextCustomer,int socket,int addedSeatsIfModified);




// //accesses shared memory to assign next available ticket number to customer
// //then increments ticket number for next customer
// //returns int ticket number
// int assignTicketNumber();



//accesses date and writes reservation info to day's summary file
// void writeToSummaryFile(customerInfo nextCustomer,int server_name, int socket);



 //send "receipt" code to customer via tcp (client will then know to run acceptReceipt() func)
//then sends receipt data in form of strings (client acceptReceipt func will create/open receipt file print)
void sendReceipt(customerInfo nextCustomer, int socket, int server_name);




// //will ask for ticket customer via tcp for ticket number, returns ticket number
// int ticketInquiryMenu(int socket);



//will search summary files for ticketNumber and send to customer via tcp
// void displayTicketInfo(int ticketNumber, int socket);


// //asks what fields customer want to modifiy, returns struct holding customers modified info //have to get ticket number
// customerInfo modifyReservationMenu(int socket);


//will use customerMods.ticketNumber to search, commits modification to summary files,
//adds note at end saying which server made modificaitons
void modifyReservation(customerInfo customerMods, int server_name, int socket);


// ////cancel confirmation sent over tcp if customer sends back yes then returns true, else false
// bool confirmCancellationMenu(int socket);


//need to be synchronized
//using customers info .dayOfTravel and .bookedSeats[], cancel reservation by deleting from summary files
// void cancelReservation(customerInfo customer,int socket);


//needs to close socket and have process exit/return thread to pool
int exitProgram(int socket,availableSeats*, int);



#endif /* server_tempFunctions.h */
