//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions 
//and the functions needed to handle the server processing of the next client/customer's selections. 
//When new client connects to chosen server’s port, 
//server commits a thread to run this master function 
//loop continues until until client ends session by choosing “exit the program”from main menu


//will need to have synchronized access to available seats struct in shared memory and "summary" files

#include "trainTicketMaster.h"
#include "trainSeating.h"
#include "caleb_server.h"
#include "server_tempFunctions.h"



#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//trainTicketMaster: will need to add address pointer to shared memory as parameter, pointers to today and tomorrow's reserations files


void trainTicketMaster(socket){

//BEWARE, WORK IN PROGRESS:
    while(1) {//infinite loop until customer exits program

        int customerResponse = 0;
        int date = 0;
        customerResponse = mainMenu(socket); //returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

        switch(customerResponse){
            case 1: //makeReservation
                    customerInfo nextCustomer; //temp struct to hold next customers info
                    nextCustomer = reservationMenu(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
                    if (checkIfAvailableSeats(date, nextCustomer.numberOfTravelers) == true){
                        if (confirmReservationMenu() == true) {//menu asking to confirm reservation//if returns true then proceed
                            nextCustomer.ticketNumber = 100; //assign ticket number //can be a random num or incremented value in shared memory
                            //needs to be synchronized: //priority is given to customers with most travelers
                            displayAvailableSeats(nextCustomer.numberOfTravelers); //shows available seats customer selects starting index (seat) and #of travelers fills in seats
                            selectAvailableSeats(nextCustomer.numberOfTravelers);
                            writeToSummaryFile(); //writes to appropriate day's summary file, ticket number will be used to search summary later on
                            sendReceipt(socket); //sends receipt code via tcp (which tell client to get call makeReceipt(), which opens a file fprints received data(receipt) and closes file)
                               // then sends receipt strings to client//
                        } 
                        else {//customer didn't confirm reservation 
                            trainTicketMaster(socket); //recursively
                        }
                    }
                    else {//sorry not enough seats available!
                        trainTicketMaster(socket); //recursivley  
                    }   
                    break;

            case 2: //ticketInquiry //syncrhonization, just reading so just have to make sure no other writers at time of reading
                    int ticketNumber;
                    ticketNumber = ticketInquiryMenu(socket); //will ask for ticket
                    displayTicketInfo(ticketNumber); //will search summary files for ticketNumber 
                    break;

            case 3: //modifyReservation //needs to be synchronized so no other concurrent writers or readers
                    customerInfo customersMods; //struct that holds modfied info
                    customersMods = modifyReservationMenu(); //returns struct holding customers modified info //have to get ticket number
                    modifyReservation(customersMods); //will use customerMods.ticketNumber to search, commits modification to summary files, adds note at end saying which server made modificaitons
                    break;

            case 4: //cancelReservation  //writing to summary file needs to be synchronized
                        bool cancelConfirmation;
                        if (cancelMenu() == true)
                            cancelReservation(ticketNumber); //cancel reservation by deleting from summary files
                    break;

            case 5: //exits progrom, closes socket
                    //send "exit" code via tcp, for client to read
                    exitProgram(socket);
                    //function returns and thread is returned to server's threadpool
                    break;

            default: //this is probably redundant
                    //send not a valid input message 
                    trainTicketMaster(socket); //recursvie call
            
        }

}
