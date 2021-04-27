 /*
 * Created by: Maxwell Meckling
 * Train Seating is designed to help manage everything to do with seating on the train.
 * This includes the creation of new seats each day through a struct.
 */



#include "trainSeating.h" //Include our own header file
#include "trainTicketMaster.h"

//calculates and then returns the number of available seats for a given day
int countNumberOfAvailableSeats(availableSeats *dayToCount) {
    int numberOfAvailableSeats = 0;
    for(int i = 0; i < sizeof(dayToCount->seats) / sizeof(int); i++) {
        if(dayToCount->seats[i] == 0) {
            numberOfAvailableSeats++;
        }
    }
    return numberOfAvailableSeats;
}

//Returns 0 or 1 based on the passed dayOfTravel variable to match which day we should be on.
//Looks at the int, not the string
int matchDayOfTravel(availableSeats *ptr, int dayOfTravel) {
    //if statement to compare which dayOfTravel we are on
    if((ptr)->dateInt == dayOfTravel) {
        //day 1 match
        return 0;
    } else {
        //day 2 match
        return 1;
    }
}

//Function for moving data to a new day:
//We copy day2 into day1 and reset day2.
void updateDays(availableSeats *ptr, char currentDate[15]) {
    //NOTE: It may not be very complex if they are just saved as "today" and "tomorrow"
    
    //Check if day1's date does not match the current date
    if(!strcmp((ptr+0)->dateStr, currentDate) == 0) {
        printf("---Updating Days---\n");
        
        //Copy Day2 dateStr to Day1 dateStr
        strcpy((ptr+0)->dateStr, (ptr+1)->dateStr);
        //Reset Day2 dateStr
        strcpy((ptr+1)->dateStr, "Tomorrow");
        
        //Reset Day1 dateInt
        (ptr+0)->dateInt = 1;
        //Reset Day2 dateInt
        (ptr+1)->dateInt = 2;
        
        //Reset Day1 ticketNumber
        (ptr+0)->ticketNumber = 1;
        //Reset Day2 ticketNumber
        (ptr+1)->ticketNumber = 1;
        
        //Copy Day2 array to Day1 array and reset the Day2 array
        for(int i = 0; i < sizeof((ptr+0)->seats) / sizeof(int); i++) {
            (ptr+0)->seats[i] = (ptr+1)->seats[i];
            (ptr+1)->seats[i] = 0;
        }
    } else {
        printf("---Days Match. No Update Performed---\n");
    }
}

//accesses shared memory struct member .nextTicketNumber to assign next available ticket number to customer
//then increments ticket number for next customer
int assignTicketNumber(customerInfo nextCustomer, int socket, availableSeats *ptr){
    printf("\nassignTicketNumber() called\n"); //for debugging
    
    //Variable to help match the day we are on to the proper struct in the shared memory pointer object: (ptr+currentDayModifier)
    int currentDayModifier = matchDayOfTravel(ptr, nextCustomer.dayOfTravel);
    
    //Get the nextTicketNumber from shared memory
    int nextTicketNumber = (ptr+currentDayModifier)->ticketNumber;
    
    //Update the ticketNumber in shared memory (just increment by 1)
    (ptr+currentDayModifier)->ticketNumber = (ptr+currentDayModifier)->ticketNumber + 1;
    
    return nextTicketNumber;
}

//needs to be synchronized
bool checkIfAvailableSeats(int dayOfTravel, int numberOfTravelers, int socket, availableSeats *ptr){
    printf("\ncheckIfavailableSeats() called\n"); //for debugging
    
    //Variable to help match the day we are on to the proper struct in the shared memory pointer object: (ptr+currentDayModifier)
    int currentDayModifier = matchDayOfTravel(ptr, dayOfTravel);
    
    int numberOfAvailableSeats = countNumberOfAvailableSeats((ptr+currentDayModifier));
    
    if(numberOfTravelers > numberOfAvailableSeats) {
        //more travelers than available seats
        return false;
    } else {
        //equal to or more than enough seats for the number of travelers
        return true;
    }
}

//needs to be synchronized
//shows seats customer selects starting index (seat) and #of travelers fills in seats
//accesses shared memory to read seats available and copies to string buffer and then sends to client via tcp
void displayAvailableSeats(int dayOfTravel, int numberOfTravelers, int socket, availableSeats *ptr){
    printf("\ndiplayAvailalbeSeats() called\n"); //for debugging
    
    //Variable to help match the day we are on to the proper struct in the shared memory pointer object: (ptr+currentDayModifier)
    int currentDayModifier = matchDayOfTravel(ptr, dayOfTravel);
    
    char messageOnEachRow[100] = "";
    char messageToPassToClient[300] = "";
    
    //Backend looking display
    for(int i = 0; i < 3; i++) { //i < sizeof(currentDay.seats) / sizeof(int) / 9;
        sprintf(messageOnEachRow, "%d:%d, %d:%d, %d:%d, %d:%d, %d:%d, %d:%d, %d:%d, %d:%d, %d:%d \n", 
                i, (ptr+currentDayModifier)->seats[i], i+3, (ptr+currentDayModifier)->seats[i+3], i+6, (ptr+currentDayModifier)->seats[i+6], 
                i+9, (ptr+currentDayModifier)->seats[i+9], i+12, (ptr+currentDayModifier)->seats[i+12], i+15, (ptr+currentDayModifier)->seats[i+15],
                i+18, (ptr+currentDayModifier)->seats[i+18], i+21, (ptr+currentDayModifier)->seats[i+21], i+24, (ptr+currentDayModifier)->seats[i+24]);
        strcat(messageToPassToClient, messageOnEachRow); //save each row onto the main message
    }
    printf("client message: \n%s", messageToPassToClient); //print debug
    
    //sendMessageToClient(char *message, int socket) method from Caleb's caleb_server.c file for sending the message through TCP.
    //sendMessageToClient(messageToPassToClient, socket);
}

customerInfo selectAvailableSeats(customerInfo nextCustomer,int socket,int addedSeatsIfModified, availableSeats *ptr) {
    printf("\nselectAvailalbeSeats() called\n"); //for debugging
    
    //When there are actual seats to change
    printf("\nWelcome to seat selection.");
    while(addedSeatsIfModified == 0) {
        printf("\nHow many seats would you like to select?: ");
        scanf("%d", &addedSeatsIfModified); //change the addedSeatsIfModified variable to match how many seats the user wants
        
        //check to make sure we have enough seats available based on what the user just entered.
        if(!checkIfAvailableSeats(nextCustomer.dayOfTravel, addedSeatsIfModified, socket, ptr)) {
            printf("Sorry, but there aren't %d seats available right now. Please enter a lower amount.", addedSeatsIfModified);
            addedSeatsIfModified = 0;
        }
    }
        
    //Declare variable to use
    int currentSelectedSeatNumber;
    
     //Variable to help match the day we are on to the proper struct in the shared memory pointer object: (ptr+currentDayModifier)
    int currentDayModifier = matchDayOfTravel(ptr, nextCustomer.dayOfTravel);

    //Begin gathering user input
    printf("\nFor the following prompt(s), please enter an integer (value 0 to 26) matching an available seat from above.\n");
    for(int i = 0; i < addedSeatsIfModified; i++) {
        printf("\nPlease select seat %d out of %d: ", i+1, addedSeatsIfModified);
        scanf("%d", &currentSelectedSeatNumber); //If the user doesn't enter an integer, an error will be thrown here.

        if(currentSelectedSeatNumber < 0 || currentSelectedSeatNumber > 26) {
            //catch possible problem of user entering an int outside our scope of seat numbers
            printf("\nError: Please try again and enter a seat number between 0 and 26.");
            //lower i by 1 so that the user has a chance to try again
            i--;
        } else if((ptr+currentDayModifier)->seats[currentSelectedSeatNumber] == 1) {
            //if the seat is already selected then the user will have to select another one
            printf("\nError: Seat already taken. Please select an open seat.");
            //lower i by 1 so that the user has a chance to try again
            i--;
        } else {
            //otherwise update the customer's booked seats array with their selected seat
            nextCustomer.bookedSeats[currentSelectedSeatNumber] = 1;
            //Modify the seats in to be later put into shared memory too!!!
            (ptr+currentDayModifier)->seats[currentSelectedSeatNumber] = 1;
        }
    }
    return nextCustomer;
}

customerInfo freeCustomersSeatsInSharedMem(customerInfo customerMods, int customersRequestedSeatReduction, availableSeats *ptr) {
    printf("\nfreeCustomersSeatsInSharedMem() called\n"); //for debugging
    
    //Variable to help match the day we are on to the proper struct in the shared memory pointer object: (ptr+currentDayModifier)
    int currentDayModifier = matchDayOfTravel(ptr, customerMods.dayOfTravel);
    
    if(customersRequestedSeatReduction != 0) {
        
        //Declare variables to use
        int currentSelectedSeatNumber;
        
        //Ask customer which seats they would like to free specifically
        printf("\nFor the following prompt(s), please enter an integer (value 0 to 26) of a seat you have already booked from above.\n");
        for(int i = 0; i < customersRequestedSeatReduction; i++) {
            printf("\nWhich seat would you like to free next? (freeing seat %d of %d): ", i+1, customersRequestedSeatReduction);
            scanf("%d", &currentSelectedSeatNumber);
            
            if(currentSelectedSeatNumber < 0 || currentSelectedSeatNumber > 26) {
                //catch possible problem of user entering an int outside our scope of seat numbers
                printf("\nError: Please try again and enter a seat number between 0 and 26.");
                //lower i by 1 so that the user has a chance to try again
                i--;
            } else if(customerMods.bookedSeats[currentSelectedSeatNumber] == 0) {
                //if the user selects a seat they don't own, then they will have to try again and select one they do own
                printf("\nError: You don't own seat %d. Please select a seat you already have selected to remove.", currentSelectedSeatNumber);
                //lower i by 1 so that the user has a chance to try again
                i--;
            } else {
                //otherwise reset the user selected seat
                customerMods.bookedSeats[currentSelectedSeatNumber] = 0;
                //Reset for shared memory too!!!
                (ptr+currentDayModifier)->seats[currentSelectedSeatNumber] = 0;
            }
        }
    } else {
        //reset bookedSeats completely for the customer and for shared memory object
        for(int i = 0; i < 27; i++) {
            customerMods.bookedSeats[i] = 0;
            //Reset for shared memory too!!!
            (ptr+currentDayModifier)->seats[i] = 0;
        }
    }
    
    return customerMods;
}

// int trainSeating() {
//     availableSeats day1; //Struct for the first day
//     availableSeats day2; //Struct for the second day
    
//     strcpy(day1.dateStr, "Yesterday"); //Create string the date for the first struct
//     strcpy(day2.dateStr, "Today"); //Create string the date for the second struct
    
//     day1.dateInt = 1; //Create the integer date for the first struct
//     day2.dateInt = 2; //Create the integer date for the second struct
    
//     day1.ticketNumber = 1; //Assign the ticketNumber for the first struct
//     day2.ticketNumber = 1; //Assign the ticketNumber for the second struct
    
//     //const int sizeOfSeatsArray = sizeof(day1.seats) / sizeof(int);
    
//     //Use for loop to initialize all array values to zero as every seat starts as being open
//     for(int i = 0; i < sizeOfSeatsArray; i++) {
//         day1.seats[i] = 0;
//         day2.seats[i] = 0;
//     }
    
//     //setUpSharedMemory(&day1, &day2);
//     availableSeats *ptr; //pointer to shared memory object
    
//     // size (in bytes) of shared memory object
//     const int SIZE = sizeof(availableSeats) * 2; //Size of our struct * 2 so we can hold two days of entries
//     // name of the shared memory object
//     const char *name = "CS4323";
//     // shared memory file descriptor 
//     int shm_fd;
    
//     // Create or open a shared memory object
//     shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
//     // Set the shared memory object size
//     ftruncate(shm_fd, SIZE);
//     // Map the shared memory object into the current address space
//     ptr = mmap(0, SIZE,  PROT_WRITE, MAP_SHARED, shm_fd, 0);
    
//     //store each newProduct into shared memory object 
//     *(ptr) = day1;
//     *(ptr + 1) = day2;
    
//     // memory map the shared memory object
//     ptr = (availableSeats *) mmap(0, SIZE, O_RDWR, MAP_SHARED, shm_fd, 0);
    
//     customerInfo testCustomer;
//     testCustomer.dayOfTravel = 1;
//     for(int i = 0; i < 27; i++) {
//         testCustomer.bookedSeats[i] = 0; 
//     }
//     testCustomer = selectAvailableSeats(testCustomer, 0, 0, ptr);
    
//     displayAvailableSeats(1, 0, 0, ptr);
    
//     updateDays(ptr, "Today"); //Call to update day
//     updateDays(ptr, "Today"); //Double check to confirm the update
    
    // // Unmap the shared memory
    // munmap(&ptr, SIZE);
    // // Close the shared memory object
    // close(shm_fd);
    // // Delete the shared memory object
    // shm_unlink(name);
    
//     return 0;
// }
