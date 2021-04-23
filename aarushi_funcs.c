#include "aarushi_funcs.h"
#define STRING_BUFFER_MAX 300 //tcp string buffer, fixed size for send and receive

int writeToSummaryFile(customerInfo nextCustomer,int server_name,int socket) { // writes to appropriate day's summary file, ticket number will be used to search summary later on 
     char stringBuffer[STRING_BUFFER_MAX]; // used to send output to server

    // used to convert bookedseats into a string to write into file
    char seat[3];
    char bookedseats[200];
    memset(bookedseats,0,strlen(bookedseats));
    for (int i = 0; i < 10; i++) {
        sprintf(seat,"%d\t",nextCustomer.bookedSeats[i]);
        strcat(bookedseats,seat);
    }
    for(int i = 0; i < (strlen(bookedseats)); i++){
        if(bookedseats[i] == '\t') {
            bookedseats[i] = ',';
        }
    }

    // if day = today
    if (nextCustomer.dayOfTravel == 1) {
        // gets todays date for summary file
        char name[20];
        struct Date today = getTodaysDate();
        sprintf(name,"%s",today.today);
        // creates summary file and writes customer info and ticket number
        FILE * summary = fopen(name,"a");
        fprintf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
        nextCustomer.numberOfTravelers, bookedseats);
        fclose(summary);
    }

    // if day = tomorrow
    if (nextCustomer.dayOfTravel == 2) {
        // gets tomorrows date for summary file
        char name[20];
        struct Date tomorrow = getTomorrowsDate();
        sprintf(name,"%s",tomorrow.tomorrow);
        // creates summary file and writes customer info and ticket number
        FILE * summary = fopen(name,"a");
        fprintf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
        nextCustomer.numberOfTravelers, bookedseats);
        fclose(summary);
    }
 
    // sends message to server
    strcpy(stringBuffer,"\nThe receipt was added to the summary file!\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    stringBuffer[0] = 0;
}

void displayTicketInfo(int ticketNumber) {
    // TODAY
    // gets todays date for summary file
    char name[20];
    struct Date today = getTodaysDate();
    sprintf(name,"%s",today.today);
    // used to send output to server
    char stringBuffer[STRING_BUFFER_MAX];
    // open summary file
    FILE * summary = fopen(name,"r");
    // struct to read file
    struct customerInfo readToday;
    struct customerInfo *readTodayPTR =
    readTodayPTR = &readToday;
    int server_name;
    char bookedseats[200];
    memset(bookedseats,0,strlen(bookedseats));

    // scan through summary file to find ticketNumber
    while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n", &readTodayPTR->ticketNumber, &server_name, readTodayPTR->fullName, readTodayPTR->dateOfBirth, readTodayPTR->gender, readTodayPTR->governmentID,&readTodayPTR->numberOfTravelers, bookedseats) != EOF) {
        // send ticketNumber and customerInfo to server
        if (readToday.ticketNumber == ticketNumber) {
            sprintf(stringBuffer,"\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",readToday.ticketNumber, server_name, readToday.fullName, readToday.dateOfBirth, readToday.gender, readToday.governmentID, readToday.numberOfTravelers,bookedseats);
            send(socket,stringBuffer,sizeof(stringBuffer),0);
            stringBuffer[0] = 0;
            break;
        }
    }
    fclose(summary);

    // TOMORROW
    // gets tomorrows date for summary file
    char name2[20];
    struct Date tomorrow = getTomorrowsDate();
    sprintf(name2,"%s",tomorrow.tomorrow);
    // struct to read file
    struct customerInfo readTomorrow;
    struct customerInfo *readTomorrowPTR =
    readTomorrowPTR = &readTomorrow;
    memset(bookedseats,0,strlen(bookedseats));
    // open summary file
    FILE * summary1 = fopen(name,"r");

    // scan through summary file to find ticketNumber
    while (fscanf(summary1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n", &readTomorrowPTR->ticketNumber, &server_name, readTomorrowPTR->fullName, readTomorrowPTR->dateOfBirth, readTomorrowPTR->gender, readTomorrowPTR->governmentID,&readTomorrowPTR->numberOfTravelers, bookedseats) != EOF) {
        // send ticketNumber and customerInfo to server
        if (readTomorrow.ticketNumber == ticketNumber) {
            sprintf(stringBuffer,"\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",readTomorrow.ticketNumber, server_name, readTomorrow.fullName, readTomorrow.dateOfBirth, readTomorrow.gender, readTomorrow.governmentID, readTomorrow.numberOfTravelers,bookedseats);
            send(socket,stringBuffer,sizeof(stringBuffer),0);
            stringBuffer[0] = 0;
            break;
        }
    }
    fclose(summary1);
}