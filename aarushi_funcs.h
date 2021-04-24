#ifndef aarushi_funcs_h
#define aarushi_funcs_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "trainTicketMaster.h"
#include "server_tempFunctions.h"

//will have to comment out versions in server_tempFunctions .c and .h to with rest of system
void writeToSummaryFile(customerInfo,int server_name,int socket);
void displayTicketInfo(int ticketNumber, int socket);
customerInfo retrieveCustomersInfo(int ticketNumber);
void cancelReservation(customerInfo customerMods);

typedef struct Date {
     char today[20];
     char tomorrow[20];
} dates;

struct Date getTodaysDate() {
     struct Date date;
     time_t t = time(NULL);
     struct tm tm = *localtime(&t);
     sprintf(date.today,"%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
     return date;
}

struct Date getTomorrowsDate() {
    char name[20];
    struct Date today = getTodaysDate();
    sprintf(name,"%s",today.today);

    char *token;
    char *token1;
    char *token2;
    char *search = "-";

    token = strtok(name,search); //year
    int year = atoi(token);
    token1 = strtok(NULL, search); // month
    int month = atoi(token1);
    token2 = strtok(NULL, search); // date
    int day = atoi(token2);

    switch(month) {
        case 1:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 2:
            if (day == 28) { day = 1; month++; }
            else { day++; }
            break;
        case 3:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 4:
            if (day == 30) { day = 1; month++; }
            else { day++; }
            break;
        case 5:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 6:
            if (day == 30) { day = 1; month++; }
            else { day++; }
            break;
        case 7:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 8:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 9:
            if (day == 30) { day = 1; month++; }
            else { day++; }
            break;
        case 10:
            if (day == 31) { day = 1; month++; }
            else { day++; }
            break;
        case 11:
            if (day == 30) { day = 1; month++; }
            else { day++; }
            break;
        case 12:
            if (day == 31) { day = 1; month++; }
            else { day++;}
            break;
    }

#endif /* aarushi_funcs.h */
