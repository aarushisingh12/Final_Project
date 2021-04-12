/*
 * Created by: Maxwell Meckling
 * Train Seating is designed to help manage everything to do with seating on the train.
 * This includes the creation of new seats each day through a struct.
 */
#include <stdio.h>
#include <stdlib.h>

#include "trainSeating.h" //Include our own header file

//Function for moving data to a new day:
//We copy day2 into day1 and reset day2.
void updateDays(availableSeats *day1, availableSeats *day2, int sizeOfSeatsArray, char currentDate[15]) {
    //NOTE: It may not be very complex if they are just saved as "today" and "tomorrow"
    
    //Check if day1's date does not match the current date
    if(!strcmp(day1->date, currentDate) == 0) {
        printf("---Updating Days---\n");
        //Copy Day2 date to Day1 date
        strcpy(day1->date, day2->date);
        //Reset Day2 date
        strcpy(day2->date, "Tomorrow");
        //Copy Day2 array to Day1 array and reset the Day2 array
        for(int i = 0; i < sizeOfSeatsArray; i++) {
            day1->seats[i] = day2->seats[i];
            day2->seats[i] = 0;
        }
    } else {
        printf("---Days Match. No Update Performed---\n");
    }
}

int trainSeating() {
    availableSeats day1; //Struct for the first day
    availableSeats day2; //Struct for the second day
    
    strcpy(day1.date, "Yesterday"); //Create the date for the first struct
    strcpy(day2.date, "Today"); //Create the date for the second struct
    
    const int sizeOfSeatsArray = sizeof(day1.seats) / sizeof(int);
    
    //Use for loop to initialize all array values to zero as every seat starts as being open
    for(int i = 0; i < sizeOfSeatsArray; i++) {
        day1.seats[i] = 0;
        day2.seats[i] = 0;
    }
    
    printf("%s\n", day1.date);
    printf("%s\n", day2.date);
    
    //Display array for a day in a 3 x 9 format:
    //this will need to be sent to client over tcp socket
    //to become function displayAvailableSeats()
    for(int i = 0; i < sizeOfSeatsArray / 9; i++) {
        //Print each column (which is +3 more with each column over)
        printf("A%d:%d, B%d:%d, C%d:%d, D%d:%d, E%d:%d, F%d:%d, G%d:%d, H%d:%d, I%d:%d \n", 
                i+1, day1.seats[i], i+1, day1.seats[i+3], i+1, day1.seats[i+6], 
                i+1, day1.seats[i+9], i+1, day1.seats[i+12], i+1, day1.seats[i+15],
                i+1, day1.seats[i+18], i+1, day1.seats[i+21], i+1, day1.seats[i+24]);
    }
    
    updateDays(&day1, &day2, sizeOfSeatsArray, "Today"); //Call to update day
    updateDays(&day1, &day2, sizeOfSeatsArray, "Today"); //Double check to confirm the update
    
    printf("%s\n", day1.date);
    printf("%s\n", day2.date);
    
    return 0;
}
