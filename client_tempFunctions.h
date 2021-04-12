#ifndef client_tempFunctions_h
#define client_tempFunctions_h

#define STRING_BUFFER_MAX 300//for tcp fixed max buffer size for sending and receiving strings

#include <stdio.h>
#include <stdlib.h>

void reservationPortal(int sock);
void acceptReceipt(int sock);


#endif /* client_tempFunctions.h */
