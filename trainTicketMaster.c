//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions 
//and the functions needed to handle the server processing of the next client/customer's selections. 
//When new client connects to chosen server’s port, 
//server commits a thread to run this master function 
//loop continues until until client ends session by choosing “exit the program”from main menu


//will need to have synchronized access to available seats struct in shared memory and "summary" files

#include "trainSeating.h"

//trainTicketMaster socket to customer, address pointer to shared memory,pointers to today and tomorrow's reserations files

//struct type customerInfo

void trainTicketMaster(socket){

    //while(1) //infinite loop untiil customer exist program
    //int customerResponse
    //customerResponse = mainMenu(socket) returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

//WORK IN PROGRESS:
    //switch(customerResponse)
    //case 1: makeReservation()
            //present struct customerInfo reservationMenu(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
            //if multiple customers will return multiple structs to be held in customerInfo struct []
            //availableSeats()
            //writeToSummaryFile(date)
            //sendReceipt(socket)
    //case 2: ticketInquiry()
            //present ticketInquiryMenu(socket); //will ask for 
            //displayTicketInfo(customer name) //will search 
    //case 3: modifyReservation()
            //modifyReservationMenu();
    //case 4: cancelReservation()
            //cancelMenu
    //case 5: exitProgram()

}




//THIS is just working through an adaptation of caleb's readFromUser() (to be called main menu) 
//as I am trying to develop overall program flow, this would remain in caleb's client file
//would move removed submenu responses to actual functions handling those specific request functions
//int mainMenu(socket){
//send via tcp
//   send printTrain string
//   send("Hello User! Welcome to the Group I train ticket reservation system!\n");
//     send("\n\nPick one of the following options:\n\n");
//     send("1. Make a reservation\n2. Inquiry about the ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program\n\n");

//     char input[500];
//     //receive response via tcp
//     if (strcmp(input, "5") == 0) {
//       return 5;
//     }
//     else if (strcmp(input, "4") == 0) {
//       return 4;
//     }
//     else if (strcmp(input, "3") == 0) {
//      return 3;
//     }
//     else if (strcmp(input, "2") == 0) {
//      return 2;
//     }
//     else if (strcmp(input, "1") == 0) {
//       return 1;
//     }
//     else {
//       send("%s isn't a valid input, please try again!\n", input);
//     }
//   }
// }
