#ifndef andrew_clientFuncs_h
#define andrew_clientFuncs_h

#define STRING_BUFFER_MAX 300//for tcp fixed max buffer size for sending and receiving strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void reservationPortal(int sock);
void acceptReceipt(int sock);


#endif /* andrew_clientFuncs.h */
