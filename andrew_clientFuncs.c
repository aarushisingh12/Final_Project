
#include "andrew_clientFuncs.h"


// mainMenu func, sends of tcp and returns int
int mainMenu(int socket){
    printf("\nMain menu called.\n");
    char stringBuffer[STRING_BUFFER_MAX];

    //send printTrain string
    strcpy(stringBuffer,"Hello User! Welcome to the Group I train ticket reservation system!\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);
    strcpy(stringBuffer, "1. Make a reservation\n2. Inquiry about the ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program\n\n");
    send(socket,stringBuffer,sizeof(stringBuffer),0);

    //receive response via tcp
    strcpy(stringBuffer,"needint"); //code that customer will read and no to scanf for int
    send(socket,stringBuffer,sizeof(stringBuffer),0);

    int intInput; //int buffer to hold client main menu input
    recv(socket,&intInput,sizeof(int),0); 
    if (intInput == 5) {
        return 5;
    }
    else if (intInput == 4) {
        return 4;
    }
    else if (intInput == 3) {
        return 3;
    }
    else if (intInput == 2) {
        return 2;
    }
    else if (intInput == 1) {
        return 1;
    }
    else {
        strcpy(stringBuffer,"isn't a valid input, please try again!\n");
        send(socket,stringBuffer, sizeof(stringBuffer), 0);
        mainMenu(socket); //call itself recursively
    }
    return 0;
}



void reservationPortal(int sock){
      printf("\nclient's reservation portal called\n");
      
      int intBuffer = 0; //temp buffer to hold int from customer input to send to server
      //char inputString[STRING_BUFFER_MAX]; //temp string buffer to hold string from customer input to send to server
      //char messageFromServer[STRING_BUFFER_MAX]//holds message from server
      char stringBuffer[STRING_BUFFER_MAX];

      //RECEIVE LOOP FROM SERVER 
      //will be receiving fixed sized buffer strings from server until received string == "inputstring" or int is if received string == "inputint"
      //if received message is "end" or "receipt" custom activity ensues
      while (1){
            recv(sock, stringBuffer, sizeof(stringBuffer),0); //receives next message from server, stores in fixed size buffer

            if (strcmp(stringBuffer, "end") == 0){  //server send end message, indicating client sent exit program to main menu
                  printf("\nReceived end code from server.\n"); //gor debugging
                  sleep(1);
                  exit(0);
                  //close(sock);
            }
            if (strcmp(stringBuffer, "needstring") == 0){ //server will send this message when string input needed from client needed
                  printf("\nReceived needstring code from server.\n"); //for debugging
                  scanf("%s",stringBuffer);
                  send(sock, stringBuffer, sizeof(stringBuffer),0);
            }
            if (strcmp(stringBuffer, "needint") == 0){
                  printf("\nReceived need needint code from server.\n"); //for debugging
                  scanf("%d",&intBuffer);
                  send(sock, &intBuffer, sizeof(int),0);
            }
            if (strcmp(stringBuffer, "receipt") == 0){
                  acceptReceipt(sock); //function that opens file and prints recieved data (receipt) to
            }
            else {//diplay server messages
                  printf("%s",stringBuffer);
            }
      }
}



//called when client reads "receipt" string sent to buffer from server via tcp
//creates/opens receipt file
//receives receipt strings from server and fprints to receipt file until "receiptend" code from server read into buffer
void acceptReceipt(int sock){
      printf("\nAccept receipt called\n"); //for debugging
      char stringBuffer[STRING_BUFFER_MAX]; //buffer to hold string sent from server via tcp

      FILE *fp;
      fp = fopen ("My Receipt", "a");

      while(1){
            recv(sock, stringBuffer, sizeof(stringBuffer),0); //receives next message from server, stores in fixed size buffer
            if (strcmp(stringBuffer, "endreceipt") == 0){ //received endreceipt signal from server
                  fclose(fp);//close file
                  return;
            }
            fprintf(fp,"%s",stringBuffer); //prints file to receipt
      }
}