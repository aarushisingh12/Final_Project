# Final_Project

How to build:

gcc aarushi_funcs.c  andrew_serverFuncs.c andrew_trainTicketMaster.c andrew_server_main.c caleb_server.c max_trainSeating.c  -o server_main -lpthread -lrt

gcc andrew_server_driver.c -o server_driver -lpthread

gcc andrew_client_main.c andrew_clientFuncs.c -o client


To run: 

./server_driver

GIVE MOMENT FOR ALL 3 SERVERS TO PRINT "SERVER # ALIVE AND NAMED":

then (in separate terminal):

./client

IMPORTANT: In order to shut down properly so servers will release port, have to run client then select option "5" on main menu then option "2" in order to close client AND server. This will close currently connected server. Must run ./client twice more to shut down remaining servers. Need to give each of 3 servers a second to print "server about to exit" as you go along. You will have been successful once you try to run client and it says "There is an issue with connection!!!"

