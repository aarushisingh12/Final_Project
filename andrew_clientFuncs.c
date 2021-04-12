
#include "andrew_clientFuncs.h"


void reservationPortal(int sock){
      
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
                  printf("\nReceived needint code from server.\n"); //for debugging
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
}