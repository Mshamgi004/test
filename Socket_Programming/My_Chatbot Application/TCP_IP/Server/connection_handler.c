#include "server.h"

// Function defination to handle the client
void handle_connection(struct sockaddr_in client_information, int new_server_sockfd)
{
    // get the name, IP Address and port no: client
    char ip[INET_ADDRSTRLEN] = {0};            // char buffer to store the ip address of connected clients
    char client_buffer[MAX_BUFFER_SIZE] = {0}; // char buffer to store the name of connected clients
    int port = ntohs(client_information.sin_port);
    char port_number[MAX_BUFFER_SIZE];

    inet_ntop(AF_INET, &(client_information.sin_addr), ip, INET_ADDRSTRLEN);

    server_recv_from_client(new_server_sockfd, client_buffer); // Function call to recieve the name from client

    // Updation on reciveing the name and port number on server without cmd
    printf("_________________________________\n");
    printf("\n[CLIENT NAME] : %s\n", client_buffer);
    printf("_________________________________\n");
    printf("\n[IP ADDRESS]  : %s\n", ip);
    printf("_________________________________\n");
    sprintf(port_number, "%d", port);
    printf("\n[Port NUMBER] : %s\n", port_number);
    printf("_________________________________\n");

    printf("Storing client data in CLIENT_INFO.txt\n");

    client_handle_list(client_buffer, ip, port_number);
    // To check for the no. of clients connected
    if (server.total_client >= NO_OF_CLIENTS)
    {
        printf("****ERROR : No more space for client to save****\n");
    }

    // populate the new client data and saving it in client_list
    strncpy(server.client_list[server.total_client].client_name, client_buffer, strlen(client_buffer));
    server.client_list[server.total_client].port = port;
    strcpy(server.client_list[server.total_client].ip, ip);
    server.client_list[server.total_client].file_des = new_server_sockfd;

    server.total_client++;
}
