//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions 
//and the functions needed to handle the server processing of the next client/customer's selections. 
//When new client connects to chosen server’s port, 
//server commits a thread to run this master function 
//loop continues until until client ends session by choosing “exit the program”from main menu


//will need to have synchronized access to available seats struct in shared memory and "summary" files

#include "trainTicketMaster.h"
//#include "trainSeating.h"
//#include "caleb_server.h"
#include "server_tempFunctions.h"


//trainTicketMaster: will need to add address pointer to shared memory as parameter, pointers to today and tomorrow's reserations files


void trainTicketMaster(int socket){
        
        char todaysDate[20]; //gets todays date if needed
        strcpy(todaysDate,getTodaysDate().today);

        while(1) {//infinite loop until customer exits program

                int customerResponse = 0;
                dates date; //struct type dates will hold today and tomorrows date
                customerResponse = mainMenu(socket); //returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

                customerInfo nextCustomer; //temp struct to hold next customers info
                int ticketNumber = 0;
                customerInfo customersMods; //struct that holds modfied info
                bool cancelConfirmation = false;
                
                switch(customerResponse){
                case 1: //makeReservation
                        nextCustomer = reservationMenu(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
                        if (checkIfAvailableSeats(nextCustomer.dayOfTravel, nextCustomer.numberOfTravelers) == true){ //dayOfTravel 1 for today and 2 for tomorrow
                                if (confirmReservationMenu() == true) {//menu asking to confirm reservation//if returns true then proceed
                                        //needs to be synchronized: //priority is given to customers with most travelers
                                        displayAvailableSeats(nextCustomer.dayOfTravel,nextCustomer.numberOfTravelers); //shows available seats customer selects starting index (seat) and #of travelers fills in seats
                                        nextCustomer = selectAvailableSeats(nextCustomer); //accesses shared memory and alows customer to select from available seats and writes to shared memory and saves bookedSeats to customer struct copy
                                        nextCustomer.ticketNumber = assignTicketNumber(); //assign ticket number //can be a random num or incremented value in shared memory
                                        writeToSummaryFile(nextCustomer); //writes to appropriate day's summary file, ticket number will be used to search summary later on
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
                        ticketNumber = ticketInquiryMenu(socket); //will ask for ticket
                        displayTicketInfo(ticketNumber); //will search summary files for ticketNumber 
                        break;

                case 3: //modifyReservation //needs to be synchronized so no other concurrent writers or readers
                        customersMods = modifyReservationMenu(); //returns struct holding customers modified info //have to get ticket number
                        modifyReservation(customersMods); //will use customerMods.ticketNumber to search, commits modification to summary files, adds note at end saying which server made modificaitons
                        break;

                case 4: //cancelReservation  //writing to summary file needs to be synchronized
                        if (cancelMenu() == true){
                                cancelReservation(ticketNumber); //cancel reservation by deleting from summary files
                        }
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

}
