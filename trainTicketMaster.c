//Andrew Ingle 04/010/2021 - Team I - Final Project
//An overall algorithmic loop, a master function manages sequencing of menu functions
//and the functions needed to handle the server processing of the next client/customer's selections.
//When new client connects to chosen server’s port,
//server commits a thread to run this master function
//loop continues until until client ends session by choosing “exit the program”from main menu


//will need to have synchronized access to available seats struct in shared memory and "summary" files

#include "trainTicketMaster.h"
//#include "trainSeating.h"
#include "caleb_server.h"
#include "server_tempFunctions.h"


//trainTicketMaster: will need to add address pointer to shared memory as parameter, pointers to today and tomorrow's reserations files


void trainTicketMaster(int socket, int server_name){

        //char todaysDate[20]; //gets todays date if needed
        //strcpy(todaysDate,getTodaysDate().today);

        while(1) {//infinite loop until customer exits program

                int customerResponse = 0;
                dates date; //struct type dates will hold today and tomorrows date
                customerResponse = mainMenu(socket); //returns the int response (see below)- presents main menu to customer via tcp, receives response and returns int response adapted from Caleb's readFromUser()

                customerInfo nextCustomer; //temp struct to hold next customers info
                int ticketNumber = 0;
                customerInfo customersMods; //struct that holds customers info for modification or cancellation
                bool cancelConfirmation = false;
                int previousDayOfTravel = 0;
                int newDayOfTravel = 0;

                switch(customerResponse){
                case 1: //makeReservation
                        nextCustomer = reservationMenu(socket); //will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
                        if (checkIfAvailableSeats(nextCustomer.dayOfTravel, nextCustomer.numberOfTravelers,socket) == true){ //dayOfTravel 1 for today and 2 for tomorrow
                                if (confirmReservationMenu() == true) {//menu asking to confirm reservation//if returns true then proceed
                                        //needs to be synchronized: //priority is given to customers with most travelers
                                        displayAvailableSeats(nextCustomer.dayOfTravel,nextCustomer.numberOfTravelers,socket); //shows available seats customer selects starting index (seat) and #of travelers fills in seats
                                        nextCustomer = selectAvailableSeats(nextCustomer,socket); //accesses shared memory and alows customer to select from available seats and writes to shared memory and saves bookedSeats to customer struct copy
                                        nextCustomer.ticketNumber = assignTicketNumber(); //assign ticket number //can be a random num or incremented value in shared memory
                                        writeToSummaryFile(nextCustomer,server_name,socket); //writes to appropriate day's summary file, ticket number will be used to search summary later on
                                        sendReceipt(nextCustomer,socket,server_name); //sends receipt code via tcp (which tell client to get call makeReceipt(), which opens a file fprints received data(receipt) and closes file)
                                        // then sends receipt strings to client//
                                }
                                else {//customer didn't confirm reservation //
                                        trainTicketMaster(socket,server_name); //recursively
                                }
                        }
                        else {//sorry not enough seats available!
                                trainTicketMaster(socket,server_name); //recursivley
                        }
                        break;

                case 2: //ticketInquiry //syncrhonization, just reading so just have to make sure no other writers at time of reading
                        ticketNumber = ticketInquiryMenu(socket); //will ask for ticket
                        displayTicketInfo(ticketNumber,socket); //will search summary files for ticketNumber
                        break;

                case 3: //modifyReservation //needs to be synchronized so no other concurrent writers or readers
                        ticketNumber = ticketInquiryMenu(socket); //will ask for ticket
                        customersMods = retrieveCustomersInfo(ticketNumber); //will retrieve customer info from summary file
                        displayTicketInfo(ticketNumber,socket); //display ticket info to customer
                        customerResponse = modifyReservationMenu(socket); //returns int for response
                        switch (customerResponse){
                        case 1: //change customers seats
                                freeCustomersSeatsInSharedMem(customersMods); //uses customer struct properties dayOfTravel and bookedSeats[] to find and free seats in shared memory
                                displayAvailableSeats(customersMods.dayOfTravel,customersMods.numberOfTravelers,socket);
                                customersMods = selectAvailableSeats(customersMods,socket); //customer selects new seats
                                //send seats changed message
                                break;
                        case 2: //change day of travel
                                previousDayOfTravel = customersMods.dayOfTravel;
                                //TODO: newDayOfTravel == ask customer what day of travel, save to variable return
                                if (checkIfAvailableSeats(newDayOfTravel, nextCustomer.numberOfTravelers,socket) == true){
                                        freeCustomersSeatsInSharedMem(customersMods); //using customers old dayOfTravel and booked seats, frees customers seats
                                        customersMods.dayOfTravel = newDayOfTravel;
                                        displayAvailableSeats(customersMods.dayOfTravel,customersMods.numberOfTravelers,socket);
                                        selectAvailableSeats(customersMods,socket);
                                        //send dayOfTravelChanged
                                }else{
                                        //send sorry not enought seats available on this day
                                }

                        case 3: //TODO: change number of travelers
                        
                        modifyReservation(customersMods,server_name,socket); //will use customerMods.ticketNumber to search, commits modification to summary files, adds note at end saying which server made modificaitons
                        break;

                case 4: //cancelReservation  //writing to summary file needs to be synchronized
                        if (confirmCancellationMenu(socket) == true){ //confirm cancellation menu
                                ticketNumber = ticketInquiryMenu(socket); //will ask for ticket
                                customersMods = retrieveCustomersInfo(ticketNumber); //will retrieve customer info from summary file
                                displayTicketInfo(ticketNumber,socket); //display ticket info to customer
                                freeCustomersSeatsInSharedMem(customersMods); //uses customer struct properties dayOfTravel and bookedSeats[] to find and free seats in shared memory
                                cancelReservation(customersMods,socket); //using customers info .dayOfTravel and .bookedSeats[], cancel reservation by deleting from summary files
                                //let customer know reservation cancelled, maybe send receipt that says cancelled or just message
                        }
                        break;

                case 5: //exits progrom, closes socket
                        //send "exit" code via tcp, for client to read
                        exitProgram(socket);
                        //function returns and thread is returned to server's threadpool
                        break;

                default: //this is probably redundant
                        //send not a valid input message
                        trainTicketMaster(socket,server_name); //recursvie call
                        
                }
        }

}
