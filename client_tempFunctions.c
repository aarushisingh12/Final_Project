
#include "client_tempFunctions.h"

void reservationPortal(int sock){

   int inputInt;
   //char[STRING_BUFFER] inputString;

   //RECEIVE LOOP FROM SERVER 
//will be receiving fixed sized buffer strings from server until received string == "input"
   //while 1
         //buffer = receive(sock, messageFromServer, sizeof(buffer))
         //if buffer == "end"  //server send end message, indicating client sent exit program to main menu
               //close(sock);
               //return 0;
         //if buffer == "needstring"  //server will send this message when input needed
               //scanf(%s,inputString)
               //send(sock, input, sizeof(buffer))
         //if buffer == "needint"
               //scanf(%d,inputInt)
               //send(sock,)
         //if buffer == "receipt"
               //call acceptReceipt() //function that opens file and prints recieved data (receipt) to
         //else //diplay server messages
            //printf("%s",buffer)

}

void acceptReceipt(int sock){
   //called when client reads "receipt" string sent to buffer from server via tcp
   //opens receipt file
   //receives receipt strings from server and fprints to receipt file until "receiptend" read in buffer

}