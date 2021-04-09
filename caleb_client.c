#include "caleb_client.h"

int main(int argc, char const *argv[]) {
  // This is is a test file for creating a user UI
  readFromUser();

  return 0;
}

int readFromUser(){
  printTrain();
  printf("Hello User! Welcome to the Group I train ticket reservation system!\n");
  //Options presented to user infinitely
  while (1) {
    printf("\n\nPick one of the following options:\n\n");
    printf("1. Make a reservation\n2. Inquiry about the ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program\n\n");

    char input[500];
    scanf("%s", input);
    if (strcmp(input, "5") == 0) {
      printf("Exiting . . . \n");
      return 0;
    }
    else if (strcmp(input, "4") == 0) {
      int ticketNumber = 0;
      printf("\nEnter your ticket number: ");
      scanf("%d", &ticketNumber);
      cancelTicket(ticketNumber);
    }
    else if (strcmp(input, "3") == 0) {
      int ticketNumber = 0;
      printf("\nEnter your ticket number: ");
      scanf("%d", &ticketNumber);
      modifyTicket(ticketNumber);
    }
    else if (strcmp(input, "2") == 0) {
      int ticketNumber = 0;
      printf("\nEnter your ticket number: ");
      scanf("%d", &ticketNumber);
      inquiry(ticketNumber);
    }
    else if (strcmp(input, "1") == 0) {
      reservation();
    }
    else {
      printf("%s isn't a valid input, please try again!\n", input);
      sleep(2);
    }
  }
}

int reservation() {
  // End code
  char yesInput[3];
  printf(ANSI_COLOR_GREEN "Make A reservation? (yes/no)" ANSI_COLOR_RESET "\n");
  scanf("%s",yesInput);

  if (strcmp(yesInput, "yes\n") == 1) {
    printf("Reservation Complete!\n");
    sleep(2);
  }
  return 0;
}

int inquiry(int ticketNumber) {
  printf("\nDisplaying ticket #%d\n",ticketNumber);
  sleep(2);
  return 0;
}

int modifyTicket(int ticketNumber) {
  inquiry(ticketNumber);
  while (1) {
    int option;
    printf("How would you like to modify ticket #%d\n", ticketNumber);
    printf("1. Change seat\n2. Change travel date\n3. Number of Travelers\n4. Confirm Changes\n\n");
    scanf("%d", &option);

    if (option == 1) {
      printf("Seat Changed!\n");
    }
    else if (option == 2) {
      printf("Change travel date to?\n");
    }
    else if (option == 3) {
      printf("How many travelers?\n");
    }
    else if (option == 4) {
      printf("Confirming Changes . . . \n");
      sleep(1);
      printf("Changes confirmed!\n");
      return 0;
    }
    sleep(1);
  }
  return 0;
}

int cancelTicket(int ticketNumber) {
  char yesInput[3];
  printf("Are you sure? (yes/no)\n");
  scanf("%s",yesInput);

  if (strcmp(yesInput, "yes") == 0) {
    printf("Reservation #%d Canceled!\n", ticketNumber);
    sleep(2);
  }

  return 0;
}

void printTrain() {
    printf("\n\n\n\n\n\n\n\n\n\n      __        __________\n     /  \\         ========   _____________\n      ||          =      =  /           ]\n  ___==============      = /            ]\n  \\_[ Group I    ========= [            ]\n    [\\=====================^==============\n___//_(_)_(_)_(_)___\\__/_____(_)_(_)_(_)\n========================================\n\n\n");
}
