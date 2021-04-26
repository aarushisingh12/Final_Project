#include "aarushi_funcs.h"
#define STRING_BUFFER_MAX 300 //tcp string buffer, fixed size for send and receive

void writeToSummaryFile(customerInfo nextCustomer,int server_name,int socket) { // writes to appropriate day's summary file, ticket number will be used to search summary later on 
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
        if (readToday.ticketNumber == ticketNumber) {
            sprintf(stringBuffer,"\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",readToday.ticketNumber, server_name, readToday.fullName, readToday.dateOfBirth, readToday.gender, readToday.governmentID, readToday.numberOfTravelers,bookedseats);
            // send ticketNumber and customerInfo to server
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
        if (readTomorrow.ticketNumber == ticketNumber) {
            sprintf(stringBuffer,"\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",readTomorrow.ticketNumber, server_name, readTomorrow.fullName, readTomorrow.dateOfBirth, readTomorrow.gender, readTomorrow.governmentID, readTomorrow.numberOfTravelers,bookedseats);
            // send ticketNumber and customerInfo to server
            send(socket,stringBuffer,sizeof(stringBuffer),0);
            stringBuffer[0] = 0;
            break;
        }
    }
    fclose(summary1);
}

customerInfo retrieveCustomersInfo(int ticketNumber) { //uses ticket number to access sumary files and save and return customer struct
    // TODAY
    // gets todays date
    char name[20];
    struct Date today = getTodaysDate();
    sprintf(name,"%s",today.today);
    char stringBuffer[500];

    // open summary file
    FILE * summary = fopen(name,"r");
    // struct to read file
    struct customerInfo read;
    struct customerInfo *readPTR =
    readPTR = &read;
    int server_name;
    char bookedseats[100];
    memset(bookedseats,0,strlen(bookedseats));

    // scan through summary file to find ticketNumber
    while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
        Modifications: \n", &readPTR->ticketNumber, &server_name, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID,&readPTR->numberOfTravelers, bookedseats) != EOF) {
        if (read.ticketNumber == ticketNumber) {
            // turn bookedseats into an struct
            char *token;
            char * temp[10];
            token = strtok(bookedseats, ",");
            int i = 0;
            while( token != NULL ) {
                temp[i] = token;
                token = strtok(NULL, ",");
                i++;
            }
            for (int i = 0; i<10; i++) {
                read.bookedSeats[i] = atoi(temp[i]);
            }
            return read;
        }
    }

    // TOMORROW
    // gets tomorrows date
    char name2[20];
    struct Date tomorrow = getTomorrowsDate();
    sprintf(name2,"%s",tomorrow.tomorrow);
    
    // struct to read file
    struct customerInfo readTomorrow;
    struct customerInfo *readTomorrowPTR =
    readTomorrowPTR = &readTomorrow;

    // open summary file
    FILE * summary1 = fopen(name,"r");
    memset(bookedseats,0,strlen(bookedseats));

    // scan through summary file to find ticketNumber
    while (fscanf(summary1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
        Modifications: \n", &readTomorrowPTR->ticketNumber, &server_name, readTomorrowPTR->fullName, readTomorrowPTR->dateOfBirth, readTomorrowPTR->gender, readTomorrowPTR->governmentID,
            &readTomorrowPTR->numberOfTravelers, bookedseats) != EOF) {
        if (readTomorrow.ticketNumber == ticketNumber) {
            // turn bookedseats into an struct
            char *token;
            char * temp[10];
            token = strtok(bookedseats, ",");
            int i = 0;
            while( token != NULL ) {
                temp[i] = token;
                token = strtok(NULL, ",");
                i++;
            }
            for (int i = 0; i<10; i++) {
                readTomorrow.bookedSeats[i] = atoi(temp[i]);
            }
            return readTomorrow;
         }
    }
}

void cancelReservation(customerInfo customerMods, int socket) {
    char stringBuffer[STRING_BUFFER_MAX]; // used to send output to server
    // variables needed to read struct
    int server_name;
    char bookedseats[100];
    memset(bookedseats,0,strlen(bookedseats));
    
    // TODAY
    if (customerMods.dayOfTravel == 1) {
        // struct to read file
        struct customerInfo read;
        struct customerInfo *readPTR =
        readPTR = &read;

        // gets todays date for summary file
        char name[20];
        struct Date today = getTodaysDate();
        sprintf(name,"%s",today.today);

        // creates summary file and writes customer info and ticket number
        FILE * summary = fopen(name,"r");
        FILE * fdel = fopen("del.txt","w");

        // scan through summary file to find ticketNumber
        while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readPTR->ticketNumber, &server_name, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID,&readPTR->numberOfTravelers, bookedseats) != EOF) {
            // copy over other ticketNumbers to fdel file
            if (customerMods.ticketNumber != read.ticketNumber) {
                fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
                Modifications: \n",read.ticketNumber, server_name, read.fullName, read.dateOfBirth, read.gender, read.governmentID,
                read.numberOfTravelers, bookedseats);
            }
        }
        // change fdel to summary file
        fclose(summary);
        fclose(fdel);
        remove(name);
        sprintf(name,"%s",today.today);
        rename("del.txt",name);
    }

    // TOMORROW
    if (customerMods.dayOfTravel == 2) {
        // struct to read file
        struct customerInfo readTomorrow;
        struct customerInfo *readTomorrowPTR =
        readTomorrowPTR = &readTomorrow;

        // gets tomorrows date for summary file
        char name[20];
        struct Date tomorrow = getTomorrowsDate();
        sprintf(name,"%s",tomorrow.tomorrow);

        // creates summary file and writes customer info and ticket number
        FILE * summary = fopen(name,"r");
        FILE * fdel = fopen("del.txt","w");

        // scan through summary file to find ticketNumber
        while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readTomorrowPTR->ticketNumber, &server_name, readTomorrowPTR->fullName, readTomorrowPTR->dateOfBirth, readTomorrowPTR->gender, readTomorrowPTR->governmentID,&readTomorrowPTR->numberOfTravelers, bookedseats) != EOF) {
            // copy over other ticketNumbers to fdel file
            if (customerMods.ticketNumber != readTomorrow.ticketNumber) {
                fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
                Modifications: \n",readTomorrow.ticketNumber, server_name, readTomorrow.fullName, readTomorrow.dateOfBirth, readTomorrow.gender, readTomorrow.governmentID,readTomorrow.numberOfTravelers, bookedseats);
            }
        }
        // change fdel to summary file
        fclose(summary);
        fclose(fdel);
        remove(name);
        sprintf(name,"%s",tomorrow.tomorrow);
        rename("del.txt",name);
    }
    // sends message to server
    strcpy(stringBuffer,"\nThe receipt was removed from the summary file!\n");        
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    stringBuffer[0] = 0;
}

void modifyReservation(customerInfo customerMods, int server_name, int socket) { // modifies reservation on summary file
    // convert customerMods bookedseats into a string
    char seat[3];
    char bookedseatsUpdated[200];
    memset(bookedseatsUpdated,0,strlen(bookedseatsUpdated));
    for (int i = 0; i < 10; i++) {
        sprintf(seat,"%d\t",customerMods.bookedSeats[i]);
        strcat(bookedseatsUpdated,seat);
    }
    for(int i = 0; i < (strlen(bookedseatsUpdated)); i++){
        if(bookedseatsUpdated[i] == '\t') {
            bookedseatsUpdated[i] = ',';
        }
    }

    // variables to read server_name and bookedseats
    int server_name_read;
    char bookedseats[100];
    memset(bookedseats,0,strlen(bookedseats));

    // TODAY
    if (customerMods.dayOfTravel == 1) {
        // struct to read summary file
        struct customerInfo read;
        struct customerInfo *readPTR =
        readPTR = &read;

        // gets todays date for summary file
        char name[20];
        struct Date today = getTodaysDate();
        sprintf(name,"%s",today.today);

        // creates summary file and fdel file to hold modified info
        FILE * summary = fopen(name,"r");
        FILE * fdel = fopen("del.txt","w");

        // read through summary file
        while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readPTR->ticketNumber, &server_name_read, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID,&readPTR->numberOfTravelers, bookedseats) != EOF) {
            // copies all information (besides modified ticket) to fdel 
            if (customerMods.ticketNumber != read.ticketNumber) {
                fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",read.ticketNumber, server_name_read, read.fullName, read.dateOfBirth, read.gender, read.governmentID,
                read.numberOfTravelers, bookedseats);
            }
            // copies modified ticket to fdel
            else {
                fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: Made by server %d\n",customerMods.ticketNumber, server_name_read, customerMods.fullName, customerMods.dateOfBirth, customerMods.gender, customerMods.governmentID,
                customerMods.numberOfTravelers, bookedseatsUpdated, server_name);
            }
        }
        // if dayOfTravel changes, accesses tomorrows document
        // gets tomorrows date for summary1 file
        char name1[20];
        struct Date tomorrow = getTomorrowsDate();
        sprintf(name1,"%s",tomorrow.tomorrow);

        // creates struct to read summary1 file
        struct customerInfo readTomorrow;
        struct customerInfo *readTomorrowPTR =
        readTomorrowPTR = &readTomorrow;
        
        // creates summary1 file and fdel1 file to hold modified info           
        FILE * summary1 = fopen(name1,"r");
        FILE * fdel1 = fopen("del1.txt","w");

        // read through summary1 file
        while (fscanf(summary1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readTomorrowPTR->ticketNumber, &server_name_read, readTomorrowPTR->fullName, readTomorrowPTR->dateOfBirth, readTomorrowPTR->gender, readTomorrowPTR->governmentID,&readTomorrowPTR->numberOfTravelers, bookedseats) != EOF) {
            // copies modified ticket to fdel
            if (customerMods.ticketNumber == readTomorrow.ticketNumber) {
               fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: Made by server %d\n",customerMods.ticketNumber, server_name_read, customerMods.fullName, customerMods.dateOfBirth, customerMods.gender, customerMods.governmentID,
               customerMods.numberOfTravelers, bookedseatsUpdated, server_name);
            }
            // removes modified ticket from summary1
            else {
                fprintf(fdel1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: ",readTomorrow.ticketNumber, server_name_read, readTomorrow.fullName, readTomorrow.dateOfBirth, readTomorrow.gender, readTomorrow.governmentID,
                readTomorrow.numberOfTravelers, bookedseats);
            }
        }

        // changes fdel file to summary file
        fclose(summary);
        fclose(fdel);
        remove(name);
        sprintf(name,"%s",today.today);
        rename("del.txt",name);

        // changes fdel1 file to summary1 file
        fclose(summary1);
        fclose(fdel1);
        remove(name1);
        sprintf(name1,"%s",tomorrow.tomorrow);
        rename("del1.txt",name1);
    }

    // variables to read server_name and bookedseats
    server_name_read = 0;
    memset(bookedseats,0,strlen(bookedseats));

    // TOMORROW
    if (customerMods.dayOfTravel == 2) {
        // struct to read summary1 file
        struct customerInfo readTomorrow;
        struct customerInfo *readTomorrowPTR =
        readTomorrowPTR = &readTomorrow;

        // gets tomorrows date for summary1 file
        char name1[20];
        struct Date tomorrow = getTomorrowsDate();
        sprintf(name1,"%s",tomorrow.tomorrow);

        // creates summary1 file and fdel1 file to hold modified info
        FILE * summary1 = fopen(name1,"r");
        FILE * fdel1 = fopen("del1.txt","w");

        // read through summary1 file
        while (fscanf(summary1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readTomorrowPTR->ticketNumber, &server_name_read, readTomorrowPTR->fullName, readTomorrowPTR->dateOfBirth, readTomorrowPTR->gender, 
            readTomorrowPTR->governmentID,&readTomorrowPTR->numberOfTravelers, bookedseats) != EOF) {
            // copies all information (besides modified ticket) to fdel1 
            if (customerMods.ticketNumber != readTomorrow.ticketNumber) {
                fprintf(fdel1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: \n",readTomorrow.ticketNumber, server_name_read, readTomorrow.fullName, readTomorrow.dateOfBirth, readTomorrow.gender, readTomorrow.governmentID,
                readTomorrow.numberOfTravelers, bookedseats);
            }
            // copies modified ticket to fdel1
            else {
                fprintf(fdel1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: Made by server %d\n",customerMods.ticketNumber, server_name_read, customerMods.fullName, customerMods.dateOfBirth, customerMods.gender, customerMods.governmentID,
                customerMods.numberOfTravelers, bookedseatsUpdated, server_name);
            }
        }
        // if dayOfTravel changes, accesses todays document
        // gets todays date for summary file
        char name[20];
        struct Date today = getTodaysDate();
        sprintf(name,"%s",today.today);

        // creates struct to read summary file
        struct customerInfo read;
        struct customerInfo *readPTR =
        readPTR = &read;
        
        // creates summary1 file and fdel1 file to hold modified info           
        FILE * summary = fopen(name,"r");
        FILE * fdel = fopen("del.txt","w");

        // read through summary file
        while (fscanf(summary, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
            Modifications: \n", &readPTR->ticketNumber, &server_name_read, readPTR->fullName, readPTR->dateOfBirth, readPTR->gender, readPTR->governmentID,
            &readPTR->numberOfTravelers, bookedseats) != EOF) {
            // copies modified ticket to fdel
            if (customerMods.ticketNumber == read.ticketNumber) {
               fprintf(fdel1, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: Made by server %d\n",customerMods.ticketNumber, server_name_read, customerMods.fullName, customerMods.dateOfBirth, customerMods.gender, customerMods.governmentID,
               customerMods.numberOfTravelers, bookedseatsUpdated, server_name);
            }
            // removes modified ticket from summary
            else {
                fprintf(fdel, "\n\nTicket Number: %d\nServer ID: %d\nCustomer Name: %s\nDate of Birth: %s\nGender: %s\nGovernment ID: %s\nNumber of Travelers: %d\nSeats Booked: %s\n\
Modifications: ",read.ticketNumber, server_name_read, read.fullName, read.dateOfBirth, read.gender, read.governmentID,read.numberOfTravelers, bookedseats);
            }
        }

        // changes fdel file to summary file
        fclose(summary);
        fclose(fdel);
        remove(name);
        sprintf(name,"%s",today.today);
        rename("del.txt",name);

        // changes fdel1 file to summary1 file
        fclose(summary1);
        fclose(fdel1);
        remove(name1);
        sprintf(name1,"%s",tomorrow.tomorrow);
        rename("del1.txt",name1);
    }
    // sends message to server
    strcpy(stringBuffer,"\nThe receipt was modified in the  summary file!\n");        
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    stringBuffer[0] = 0;
}
