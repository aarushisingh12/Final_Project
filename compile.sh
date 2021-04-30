gcc aarushi_funcs.c  andrew_serverFuncs.c andrew_trainTicketMaster.c andrew_server_main.c caleb_server.c max_trainSeating.c  -o server_main -lpthread -lrt
gcc andrew_server_driver.c -o server_driver -lpthread
gcc andrew_client_main.c andrew_clientFuncs.c -o client

