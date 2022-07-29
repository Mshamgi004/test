#include "server.h"

// Function defination for recieving the name from client
int server_recv_from_client(int client_socket, char *recv_msg) 
{
	int read_bytes = 0;   // Variable use to store the read_bytes
	memset(recv_msg,0,strlen(recv_msg));  // Clearing the buffer initially
    
	// recv() call
	if((read_bytes = recv(client_socket, recv_msg, MAX_BUFFER_SIZE, 0)) > 0) 
	{
		process_recv_data(client_socket, recv_msg);
    }
    else if(read_bytes == 0) 
    {
		printf("*****Client Disconnected*****\n");
		server_delete_client(client_socket);          // Function call for server delete the client
	}
    else 
    {
		printf("*****ERROR: recv() failed*****\n");
	}
    
	return 0;
}
