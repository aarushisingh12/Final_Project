
#ifndef server_tempFunctions_h
#define server_tempFunctions_h

#include "trainTicketMaster.h"
#include <stdbool.h>



int mainMenu(int socket);


//will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
customerInfo reservationMenu(int socket);


//needs to be synchronized
bool checkAvailableSeats(int date, int numberOfTravelers);


//menu that asks customer via tcp if they want to confirm reservation, returns true if yes, else false
bool confirmReservationMenu();



//needs to be synchronized
//shows seats customer selects starting index (seat) and #of travelers fills in seats
//accessess shared memory to read seats avaialbe and copies to string buffer and then sends to client via tcp
void displayAvailableSeats();



//needs to be synchronized
//accesses shared memory and alows customer to select from available seats and writes to shared memory
void selectAvailableSeats(int numberOfTravelers);



//accesses date and writes reservation info to day's summary file
void writeToSummaryFile(); 



 //send "receipt" code to customer via tcp (client will then know to run acceptReceipt() func)
//then sends receipt data in form of strings (client acceptReceipt func will create/open receipt file print)
void sendReceipt(int socket);
   



//will ask for ticket customer via tcp for ticket number, returns ticket number
int ticketInquiryMenu(int socket);



//will search summary files for ticketNumber and send to customer via tcp
void displayTicketInfo(int ticketNumber);


//asks what fields customer want to modifiy, returns struct holding customers modified info //have to get ticket number
customerInfo modifyReservationMenu();


//will use customerMods.ticketNumber to search, commits modification to summary files, 
//adds note at end saying which server made modificaitons
void modifyReservation(customerInfo customerMods);


//cancel confirmation sent over tcp if customer sends back yes then returns true, else false
bool cancelMenu();


//need to be synchronized
//cancel reservation by deleting from summary files
void cancelReservation(int ticketNumber);



#endif /* server_tempFunctions.h */
