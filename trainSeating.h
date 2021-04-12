/*
 * Created by: Maxwell Meckling
 */


#include <string.h>

#ifndef TRAINSEATING_H
#define TRAINSEATING_H

#define STRING_BUFFER_MAX 300//for tcp 

typedef struct StructForSeating {
    //string for the date.
    char date[15];
    //int array for the seats. 
    //0 means the seat is open and 1 means it is already taken.
    //There are 27 seats total in three rows and nine columns
    //(just like the assignment document shows).
    int seats[27]; 
    int nextTicketNumber; //to be assigned to customer with int assignTicketNumber() just use day 1's
}availableSeats;

int trainSeating();

#endif /* TRAINSEATING_H */

