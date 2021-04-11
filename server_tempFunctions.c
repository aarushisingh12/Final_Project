//PLEASE DO NOT DELETE. USED FOR TESTING
//JUST COPY FUNCTION STUBS TO OWN FILE TO WORK ON, CAN COMMENT THESE OUT IF YOU NEED TO TEST

//FUNCTIONS THAT NEED TO BE IMPLEMENTED BY TEAM


#include "server_tempFunctions.h"
#include "trainTicketMaster.h"

#include <stdbool.h>



//will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
customerInfo reservationMenu(int socket){
    customerInfo nextCustomersInfo;

    return nextCustomersInfo;
}


//needs to be synchronized
bool checkAvailableSeats(int date, int numberOfTravelers){

    return true;
}



bool confirmReservationMenu(){
    return true;
}


//needs to be synchronized
//shows seats customer selects starting index (seat) and #of travelers fills in seats
//accessess shared memory to read seats avaialbe and copies to string buffer and then sends to client via tcp
void displayAvailableSeats(){ 

} 



//needs to be synchronized
//accesses shared memory and alows customer to select from available seats and writes to shared memory
void selectAvailableSeats(int numberOfTravelers){

}



void writeToSummaryFile(){
    //accesses date and writes reservation info to day's summary file 
}



void sendReceipt(int socket){
    //send "receipt" code to customer via tcp (client will then know to run acceptReceipt() func)
    //then sends receipt data in form of strings (client acceptReceipt func will create/open receipt file print)

}



//will ask for ticket customer via tcp for ticket number, returns ticket number
int ticketInquiryMenu(int socket){
    int ticketNumber;

    return ticketNumber;
}



//will search summary files for ticketNumber 
void displayTicketInfo(int ticketNumber){

}


//asks what fields customer want to modifiy, returns struct holding customers modified info //have to get ticket number
customerInfo modifyReservationMenu(){
    customerInfo customersMods;  //struct that holds modfied info

    return customersMods;
}


//will use customerMods.ticketNumber to search, commits modification to summary files, 
//adds note at end saying which server made modificaitons
void modifySummaryFile(customerInfo customerMods){
}


//cancel confirmation sent over tcp if customer sends back yes then returns true, else false
bool cancelMenu(){
    return true;
} 


//need to be synchronized
//cancel reservation by deleting from summary files
void cancelReservation(int ticketNumber){

}


