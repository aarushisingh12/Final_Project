//PLEASE DO NOT DELETE. USED FOR TESTING
//JUST COPY FUNCTION STUBS TO OWN FILE TO WORK ON, CAN COMMENT THESE OUT IF YOU NEED TO TEST

//FUNCTIONS THAT NEED TO BE IMPLEMENTED BY TEAM


#include "server_tempFunctions.h"


#include <stdbool.h>
#include <string.h>



// THIS is just working through an adaptation of caleb's readFromUser() (to be called main menu) 
// as I am trying to develop overall program flow, this would remain in caleb's client file
// would move removed submenu responses to actual functions handling those specific request functions
int mainMenu(socket){
    
    char stringBuffer[STRING_BUFFER_MAX];

    //send printTrain string
    strcpy(stringBuffer,"Hello User! Welcome to the Group I train ticket reservation system!\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    strcpy(stringBuffer, "1. Make a reservation\n2. Inquiry about the ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program\n\n");

    int input; //int buffer to hold client main menu input
    
    //receive response via tcp
    strcpy(stringBuffer,"inputInt"); //code that customer will read and no to scanf for int
    recv(socket,input,sizeof(int),0); 
    if (input == 5) {
        return 5;
    }
    else if (input == 4) {
        return 4;
    }
    else if (input == 3) {
        return 3;
    }
    else if (input == 2) {
        return 2;
    }
    else if (input == 1) {
        return 1;
    }
    else {
        strcpy(stringBuffer,"isn't a valid input, please try again!\n");
        send(socket,stringBuffer, 0);
        mainMenu(socket); //call itself recursively
    }
    return 0;
}




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



//will search summary files for ticketNumber and send to customer via tcp
void displayTicketInfo(int ticketNumber){

}


//asks what fields customer want to modifiy, returns struct holding customers modified info //have to get ticket number
customerInfo modifyReservationMenu(){
    customerInfo customersMods;  //struct that holds modfied info

    return customersMods;
}


//will use customerMods.ticketNumber to search, commits modification to summary files, 
//adds note at end saying which server made modificaitons
void modifyReservation(customerInfo customerMods){
}


//cancel confirmation sent over tcp if customer sends back yes then returns true, else false
bool cancelMenu(){
    return true;
} 


//need to be synchronized
//cancel reservation by deleting from summary files
void cancelReservation(int ticketNumber){

}

//needs to close socket and have process exit/return thread to pool
void exitProgram(int socket){
    close(socket);

}
