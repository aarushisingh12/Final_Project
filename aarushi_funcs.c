// #include "aarushi_funcs.h"
// #define STRING_BUFFER_MAX 300 //tcp string buffer, fixed size for send and receive


// int writeToSummaryFile(customerInfo nextCustomer,int server_name,int socket) { // writes to appropriate day's summary file, ticket number will be used to search summary later on {

//     char stringBuffer[STRING_BUFFER_MAX]; // used to send output to server
    
//     // if day = today
//     if (nextCustomer.dayOfTravel = '1') {

//         // gets todays date for summary file
//         char name[20];
//         struct Date today = getTodaysDate();
//         sprintf(name,today.today);

//         // creates summary file and writes customer info and ticket number
//         FILE * summary = fopen(name,"a");
//         fprintf(summary, "Ticket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: /
//             %s\nModifications: \n", nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
//             nextCustomer.numberOfTravelers, nextCustomer.bookedSeats);
//         fclose(summary);
        
//         // sends message to server 
//         strcpy(stringBuffer,"The receipt was added to the summary file!\n");
//         send(socket,stringBuffer,sizeof(stringBuffer),0);
//         stringBuffer[0] = 0;
//     }

//     // if day = tomorrow
//     if (nextCustomer.dayOfTravel = '2') {
        
//         // gets tomorrows date for summary file
//         char name2[20];
//         struct Date tomorrow = getTomorrowsDate();
//         sprintf(name2,tomorrow.tomorrow);

//         // creates summary file and writes customer info and ticket number
//         FILE * summary2 = fopen(name2,"a");
//         fprintf(summary2, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: /
//             %s\nModifications: \n", nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
//             nextCustomer.numberOfTravelers, nextCustomer.bookedSeats);
//         fclose(summary2);

//         // sends message to server
//         strcpy(stringBuffer,"The receipt was added to the summary file!\n");
//         send(socket,stringBuffer,sizeof(stringBuffer),0);
//         stringBuffer[0] = 0;
//     }
//     return 1;
// }

// int displayTicketInfo(int ticketNumber, int socket) { // searches summary files for ticketNumber 
    
//     // gets todays date for summary file
//     char name[20];
//     struct Date today = getTodaysDate();
//     sprintf(name,today.today);

//     // used to send output to server
//     char stringBuffer[STRING_BUFFER_MAX];

//     // open summary file 
//     FILE * summary = fopen(name,"r");
//     struct customerInfo read;
//     struct customerInfo *readPTR =
//     readPTR = &read;
//     char server_name[30];

//     // scan through summary file to find ticketNumber
//     while (fscanf(summary, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats /
//         Booked: %s\nModifications: \n", &readPTR->ticketNumber, server_name, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID, 
//         &readPTR->numberOfTravelers, readPTR->bookedSeats) != EOF) {

//         // send ticketNumber and customerInfo to server
//         if (read.ticketNumber == ticketNumber) {
//             strcpy(stringBuffer,"Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\n\
//                 Seats Booked: %s\n", read.ticketNumber, server_name, read.fullName, read.dateOfBirth, read.gender, read.governmentID, read.numberOfTravelers, 
//                 read.bookedSeats);
//             send(socket,stringBuffer,sizeof(stringBuffer),0);
//             stringBuffer[0] = 0;
//             break;
//         }
//     }

//     // gets tomorrows date for summary file
//     char name2[20];
//     struct Date tomorrow = getTomorrowsDate();
//     sprintf(name2,tomorrow.tomorrow);

//     // open summary file 
//     FILE * summary2 = fopen(name2,"r");
//     struct customerInfo read2;
//     struct customerInfo *read2PTR =
//     read2PTR = &read2;

//     // scan through summary file to find ticketNumber
//     while (fscanf(summary2, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: \
//         %s\nModifications: \n", &read2PTR->ticketNumber, server_name, read2PTR->fullName, read2PTR->dateOfBirth, read2PTR->gender, read2PTR->governmentID, 
//         &read2PTR->numberOfTravelers, read2PTR->bookedSeats) != EOF) {

//         // send ticketNumber and customerInfo to server
//         if (read2.ticketNumber == ticketNumber) {
//             strcpy(stringBuffer,"Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\n
//                 Seats Booked: %s\n", read2.ticketNumber, server_name, read2.fullName, read2.dateOfBirth, read2.gender, read2.governmentID, read2.numberOfTravelers, 
//                 read2.bookedSeats);
//             send(socket,stringBuffer,sizeof(stringBuffer),0);
//             stringBuffer[0] = 0;
//             break;
//         }
//     }
//     return 1;
// }




