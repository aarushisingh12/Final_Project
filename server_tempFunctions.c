//PLEASE DO NOT DELETE. USED FOR TESTING
//JUST COPY FUNCTION STUBS TO OWN FILE TO WORK ON, CAN COMMENT THESE OUT IF YOU NEED TO TEST

//FUNCTIONS THAT NEED TO BE IMPLEMENTED BY TEAM


#include "server_tempFunctions.h"


// // mainMenu func, sends of tcp and returns int
// int mainMenu(int socket){
//     printf("\nMain menu called.\n");
//     char stringBuffer[STRING_BUFFER_MAX];

//     //send printTrain string
//     strcpy(stringBuffer,"Hello User! Welcome to the Group I train ticket reservation system!\n");
//     send(socket,stringBuffer,sizeof(stringBuffer),0);
//     strcpy(stringBuffer, "1. Make a reservation\n2. Inquiry about the ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program\n\n");
//     send(socket,stringBuffer,sizeof(stringBuffer),0);

//     //receive response via tcp
//     strcpy(stringBuffer,"needint"); //code that customer will read and no to scanf for int
//     send(socket,stringBuffer,sizeof(stringBuffer),0);

//     int intInput; //int buffer to hold client main menu input
//     recv(socket,&intInput,sizeof(int),0);
//     if (intInput == 5) {
//         return 5;
//     }
//     else if (intInput == 4) {
//         return 4;
//     }
//     else if (intInput == 3) {
//         return 3;
//     }
//     else if (intInput == 2) {
//         return 2;
//     }
//     else if (intInput == 1) {
//         return 1;
//     }
//     else {
//         strcpy(stringBuffer,"isn't a valid input, please try again!\n");
//         send(socket,stringBuffer, sizeof(stringBuffer), 0);
//         mainMenu(socket); //call itself recursively
//     }
//     return 0;
// }


//to use:   char date[20];
//          strcpy(date,getTodaysDate().today)
struct Date getTodaysDate() {
     struct Date date;
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     sprintf(date.today,"%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
     return date;
}



//will ask for and receive via TCP customerInfo, and save to customerInfo struct and return struct
//customerInfo reservationMenu(int socket){
//    customerInfo nextCustomersInfo;
//
//    return nextCustomersInfo;
//}


//needs to be synchronized
bool checkIfAvailableSeats(int dayOfTravel, int numberOfTravelers, int socket){
    printf("\ncheckIfavailableSeats() called\n"); //for debugging
        //or false if not enough available to cover numberOfTravelers
    return true;
}



// bool confirmReservationMenu(int socket){
//    printf("\nconfirmtReservationMenu() called\n"); //for debugging
// //return false if they do not confirm, could say reservation not confirmed or something
//
//    return true;
// }


//needs to be synchronized
//shows seats customer selects starting index (seat) and #of travelers fills in seats
//accessess shared memory to read seats avaialbe and copies to string buffer and then sends to client via tcp
void displayAvailableSeats(int dayOfTravel,int numberOfTravelers, int socket){
    printf("diplayAvailalbeSeats() called\n"); //for debugging

}




//needs to be synchronized
//accesses shared memory and alows customer to select from available seats and writes to shared memory
//will use int nextCustomer.dayOfTravel and mextCustomer.numberOfTravelers
customerInfo selectAvailableSeats(customerInfo nextCustomer, int socket){
    printf("selectAvailalbeSeats() called\n"); //for debugging

    return nextCustomer;
}


//accesses shared memory struct member .nextTicketNumber to assign next available ticket number to customer
//then increments ticket number for next customer
int assignTicketNumber(int socket){
    printf("assignTicketNumber() called\n"); //for debugging
    int nextTicketNumber;
      //struct that holds modfied info
    return nextTicketNumber;
}


void writeToSummaryFile(customerInfo nextCustomer, int server_name, int socket){
    printf("writeToSummaryFile() called\n"); //for debugging
    //accesses date and writes reservation info to day's summary file
}



void sendReceipt(customerInfo nextCustomer, int socket,int server_name){
    printf("sendReceipt() called\n"); //for debugging
    //send "receipt" code to customer via tcp (client will then know to run acceptReceipt() func)
    //then sends receipt data in form of strings (client acceptReceipt func will create/open receipt file print)

}



// //will ask for ticket customer via tcp for ticket number, returns ticket number
// int ticketInquiryMenu(int socket){
//    printf("ticketInquiryMenu() called\n"); //for debugging
//    int ticketNumber;
//
//    return ticketNumber;
// }



//will search summary files for ticketNumber and send to customer via tcp
void displayTicketInfo(int ticketNumber,int socket){
    printf("diplayTicketInfo() called\n"); //for debugging

}


//asks what fields customer want to modifiy, returns struct holding customers modified info
//have to get ticket number to use to search summary files
// customerInfo modifyReservationMenu(int socket){
//    printf("diplayAvailalbeSeats() called\n"); //for debugging
//    customerInfo customersMods;  //struct that holds modfied info/
//
//    return customersMods;
// }


//will use customerMods.ticketNumber to search, commits modification to summary files,
//adds note at end saying which server made modificaitons
void modifyReservation(customerInfo customerMods, int server_name, int socket){
    printf("modifyReservation() called\n"); //for debugging
}


//called during modify reservation if change of seats option selected
customerInfo changeCustomerSeats(int ticketNumber,int socket){
    int dayOfTravel = 0;
    char stringBuffer[STRING_BUFFER_MAX];
    customerInfo customerForSeatsFreed;
    customerForSeatsFreed.ticketNumber = ticketNumber; //for use in findSelectedSeatsInSummaryFile
    strcpy(stringBuffer,"\nWhat day are you traveling? If today enter 1. If tommorrow enter 2:\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    //receive response via tcp
    strcpy(stringBuffer,"needint"); //code that customer will read and no to scanf for int
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    recv(socket,&dayOfTravel,sizeof(int),0);

    strcpy(stringBuffer,"\nHow Many Travelers?\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    //receive response via tcp
    strcpy(stringBuffer,"needint"); //code that customer will read and no to scanf for int
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    recv(socket,&dayOfTravel,sizeof(int),0);

    if(dayOfTravel==1){
        customerForSeatsFreed.dayOfTravel = 1;
    }else if (dayOfTravel==2){
        customerForSeatsFreed.dayOfTravel = 2;
    }
    
    customerForSeatsFreed = findSelectedSeatsInSummaryFile(customerForSeatsFreed,socket);

    freeCustomersSeatsInSharedMem(customerForSeatsFreed);

    displayAvailableSeats(customerForSeatsFreed.dateOfTravel,customerForSeatsFreed.numberOfTravelers,socket);

    selectAvailableSeats(customerForSeatsFreed,socket);

    return customerForSeatsFreed;
    
}

customerInfo findSelectedSeatsInSummaryFile(customerInfo customerForSeatsFreed,int socket){
    customerInfo customerForSeatsFreed;
    //using customerForSeatsFreed.dayOfTravel and/or customerForSeatsFreed.ticketNumber find entry in summary files
    //customerForSeatsFreed.numberOfTravelers = find #of travelers
    //customerForSeatsFreed.bookedSeats = found seats//will need to be parsed from string and added to int[] bookedSeats in loop
    return customerForSeatsFreed;
}


void freeCustomersSeats(customerInfo customerForSeatsFreed){
    //using customerForSeatsFreed.dayOfTravel and cusomerForSeatsFreed.bookedSeats, find customers seats in shared memory and free them
}


//cancel confirmation sent over tcp if customer sends back yes then returns true, else false
// bool confirmCancellationMenu(int socket){
//    printf("cancelMenu() called\n"); //for debugging
//    //or false if they don't confirm
//    return true;
// }


//need to be synchronized
//needs to ask for ticket number and then go to summary file(s) and delete entry
void cancelReservation(int socket){
    printf("cancelReservation() called\n"); //for debugging


}

void exitProgram(int socket){
    printf("exitProgram() called\n"); //for debugging
    char stringBuffer[STRING_BUFFER_MAX];
    strcpy(stringBuffer,"\nEnter 1 to just shut down client, Enter 2 to shutdown client and server\n"); //end code to be sent to client, client will then know to call its own exit function
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    strcpy(stringBuffer,"needint"); //end code to be sent to client, client will then know to call its own exit function
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    //sleep(1);
    int intInput; //int buffer to hold client main menu input
    recv(socket,&intInput,sizeof(int),0);
    printf("\n user entered %d\n",intInput);
    if (intInput == 1){
        printf("\n user entered %d\n",intInput);
        strcpy(stringBuffer,"end"); //end code to be sent to client, client will then know to call its own exit function
        send(socket,stringBuffer,sizeof(stringBuffer),0);
        sleep(3); //to give time for customer to process end code
        close(socket);  //closing socket with this customer
    }else if (intInput == 2){
        printf("\n user entered %d\n",intInput);
        strcpy(stringBuffer,"end"); //end code to be sent to client, client will then know to call its own exit function
        send(socket,stringBuffer,sizeof(stringBuffer),0);
        sleep(3); //to give time for customer to process end code
        close(socket);  //closing socket with this customer
        printf("\nServer about to exit\n");
        exit(0); //will need to delete this later once live server loop in place

    }
}
