//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions 
//and the functions needed to handle the server processing of the next client/customer's selections. 
//When new client connects to chosen server’s port, 
//server commits a thread to run this master function 
//loop continues until until client ends session by choosing “exit the program”from main menu


//will need to have synchronized access to available seats struct in shared memory and "summary" files

#include "trainSeating.h"
#include "caleb_server.h"
#include "server_tempFunctions.h"


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//trainTicketMaster socket to customer, address pointer to shared memory,pointers to today and tomorrow's reserations files

//struct type customerInfo



void trainTicketMaster(socket){

//BEWARE, WORK IN PROGRESS:
    //while(1) //infinite loop until customer exits program

        //int customerResponse;
        //customerResponse = mainMenu(socket) returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

        //switch(customerResponse)
        //case 1: //makeReservation
                //customerInfo nextCustomer //temp struct to hold next customers info
                //nextCustomer = struct customerInfo reservationMenu(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
                //if (checkAvailableSeats(date, nextCustomer.numberOfTravelers) == TRUE)
                    //if (confirmReservationMenu() == true) //menu asking to confirm reservation//if returns true then proceed
                        //nextCustomer.ticketNumber = //assign ticket number //can be a random num or incremented value
                        //needs to be synchronized: //priority is given to customers with most travelers
                        //displayAvailableSeats(nextCustomer.numberoftravelors) //shows available seats customer selects starting index (seat) and #of travelers fills in seats
                        //selectAvailableSeats(nextCustomer.numberofTravelors)
                        //writeToSummaryFile() //writes to appropriate day's summary file, ticket number will be used to search summary later on
                        //sendReceipt(socket) //sends receipt code via tcp (which tell client to get call makeReceipt(), which opens a file fprints received data(receipt) and closes file)
                            //then sends receipt strings to client//
                    //else //customer didn't confirm reservation 
                        //so call trainTicketMaster recursively
                //else //sorry not enough seats available!
                    //call trainTicketMaster(socket) recursivley       

        //case 2: ticketInquiry //syncrhonization, just reading so just have to make sure no other writers at time of reading
                //int ticketNumber
                //ticket Number = ticketInquiryMenu(socket); //will ask for ticket
                //displayTicketInfo(ticketNumber) //will search summary files for ticketNumber 

        //case 3: modifyReservation //needs to be synchronized so no other concurrent writers or readers
                //sturct customerInfo modifiedInfo customersMods  //struct that holds modfied info
                //customerMods = modifyReservationMenu(); //returns struct holding customers modified info //have to get ticket number
                //modifySummaryFile(customerMods) = will use customerMods.ticketNumber to search, commits modification to summary files, adds note at end saying which server made modificaitons

        //case 4: cancelReservation  //writing to summary file needs to be synchronized
                    //bool cancelConfirmation
                    //if (bool cancelMenu() == true)
                        //cancelReservation(ticketNumber) //cancel reservation by deleting from summary files

        //case 5: exitProgram()
                //Exit message
                //function returns and thread is returned to server's threadpool

        //default:
            //non valid input message
            //so trainTicketMaster(socket) //recursvie call

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
