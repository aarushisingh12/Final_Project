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

//BEWARE, WORK IN PROGRESS:
    //while(1) //infinite loop untiil customer exits program

    //int customerResponse
    //customerResponse = mainMenu(socket) returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

    //switch(customerResponse)
    //case 1: //makeReservation
            //customerInfo nextCustomer //temp struct to hold next customers info
            //nextCustomer = struct customerInfo makeReservation(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
            //if (checkAvailableSeats(date, nextCustomer.numberOfTravelers) == TRUE)
                //if (confirmReservation() == true) //menu asking to confirm reservation//if returns true then proceed

                    //needs to be synchronized:
                    //availableSeats(next.Customer.numberoftravelors) //shows available seats customer selects starting index (seat) and #of travelers fills in seats
                    //writeToSummaryFile(date) //assigns ticket number writes to apprapriate days summary file

                    //sendReceipt(socket) //via tcp sends receipt strings to client//client has to have function to receive strings open file, prints string to file and close 
                //else //customer didn't confirm reservation 
                    //so call mainMenu recursively
            //else //sorry not enough seats available!
                //call mainMenu recursivley       

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
//      send("%s isn't a valid input, please try again!\n", input);
//      mainMenu(socket); call itself recursively
//     }
//   }
// }


//makeReservation()
//    //asks how many will be travelling with you
    //for each travelor asks
//
//
//}