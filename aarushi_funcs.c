// #include "aarushi_funcs.h"


// // need to pass struct here - not sure how?
// int writeToSummaryFile(customerInfo nextCustomer,int server_name) {//writes to appropriate day's summary file, ticket number will be used to search summary later on {
 
//     if (nextCustomer.dayOfTravel = '1') {
//         char name[20];
//         struct Date today = getTodaysDate();
//         sprintf(name,today.today);
//         FILE * summary = fopen(name,"a");
//         fprintf(summary, "Ticket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: /
//             %s\nModifications: \n", nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
//             nextCustomer.numberOfTravelers, nextCustomer.bookedSeats);
//         fclose(summary);
//     }

//     if (nextCustomer.dayOfTravel = '2') {
//         char name2[20];
//         struct Date tomorrow = getTomorrowsDate();
//         sprintf(name2,tomorrow.tomorrow);
//         FILE * summary2 = fopen(name2,"a");
//         fprintf(summary2, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: /
//             %s\nModifications: \n", nextCustomer.ticketNumber, server_name, nextCustomer.fullName, nextCustomer.dateOfBirth, nextCustomer.gender, nextCustomer.governmentID,
//             nextCustomer.numberOfTravelers, nextCustomer.bookedSeats);
//         fclose(summary2);
//     }
//     return 1;
// }

// int displayTicketInfo(int ticketNumber) {
//     char name[20];
//     struct Date today = getTodaysDate();
//     sprintf(name,today.today);

//     FILE * summary = fopen(name,"r");

//     struct customerInfo read;
//     struct customerInfo *readPTR =
//     readPTR = &read;

//     char server_name[30];

//     while (fscanf(summary, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats /
//         Booked: %s\nModifications: \n", &readPTR->ticketNumber, server_name, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID, 
//         &readPTR->numberOfTravelers, readPTR->bookedSeats) != EOF) {

//         printf("%d\n",read.ticketNumber);

//         if (read.ticketNumber == ticketNumber) {
//             printf("Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n",
//                 read.ticketNumber, server_name, read.fullName, read.dateOfBirth, read.gender, read.governmentID, read.numberOfTravelers, read.bookedSeats);
//             break;
//         }
//     }

//     char name2[20];
//     struct Date tomorrow = getTomorrowsDate();
//     sprintf(name2,tomorrow.tomorrow);

//     FILE * summary2 = fopen(name2,"r");

//     struct customerInfo read2;
//     struct customerInfo *read2PTR =
//     read2PTR = &read2;

//     while (fscanf(summary2, "Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: \
//         %s\nModifications: \n", &read2PTR->ticketNumber, server_name, read2PTR->fullName, read2PTR->dateOfBirth, read2PTR->gender, read2PTR->governmentID, 
//         &read2PTR->numberOfTravelers, read2PTR->bookedSeats) != EOF) {

//         if (read2.ticketNumber == ticketNumber) {
//             printf("Ticket Number: %d\nServer ID: %s\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n",
//                 read2.ticketNumber, server_name, read2.fullName, read2.dateOfBirth, read2.gender, read2.governmentID, read2.numberOfTravelers, read2.bookedSeats);
//             break;
//         }
//     }
//     return 1;
// }




