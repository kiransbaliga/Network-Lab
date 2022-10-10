#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // CREATE SOCKET
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - IPPROTO_TCP, indicates that the TCP protocol is to be used
    if (sock_fd < 0)
    {
        printf("Socket error\n");
        exit(1);
    }
    // CREATE ADDRESS
    struct sockaddr_in address;                       // sockaddr_in - structure for storing an IP address and port number.
    address.sin_family = AF_INET;                     // sin_family - address family (AF_INET - IPv4)
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // sin_addr.s_addr - IP address in network byte order (htonl - convert long integer to network byte order)
    address.sin_port = htons(8886);                   // sin_port - port number in network byte order (htons - convert short integer to network byte order)
    // CREATE CONNECT
    int conn_res = connect(sock_fd, (struct sockaddr *)&address, sizeof(address)); // connect - connect a socket to a remote address.
    if (conn_res < 0)
    {
        printf("Connect error\n");
        exit(1);
    }

    fd_set readfds; // fd_set - file descriptor set, used for select() function.
    int max_fd_val; // max_fd_val - maximum file descriptor value.
    while (1)
    {
        FD_ZERO(&readfds);         // FD_ZERO - clear the set of file descriptors.
        FD_SET(sock_fd, &readfds); // FD_SET - add a file descriptor to a set.
        FD_SET(0, &readfds);       // 0 - standard input file descriptor.

        max_fd_val = sock_fd;                               // max_fd_val - maximum file descriptor value.
        select(max_fd_val + 1, &readfds, NULL, NULL, NULL); // select - monitor a set of file descriptors for readability, writability, or error condition.

        for (int i = 0; i <= max_fd_val; i++)
        {                      // for - loop through the file descriptors.
            char buffer[1024]; // buffer - buffer for storing data.
            if (FD_ISSET(i, &readfds))
            { // FD_ISSET - check if a file descriptor is set in a set.
                if (i == 0)
                {                                             // i == 0 - standard input file descriptor.
                    fgets(buffer, 1024, stdin);               // fgets - read a line from a file.
                    send(sock_fd, buffer, strlen(buffer), 0); // send - send data to a socket.
                    printf("Msg sent to client\n");           // printf - print formatted output to stdout.
                }
                else
                {
                    int len = recv(sock_fd, buffer, 1024, 0); 
                    buffer[len] = '\0';  // recv - receive data from a socket.
                    printf("%c : ",buffer[len-1]);  
                    for (int i=0;i<len-1;i++){                   // buffer[len] - end of string.
                        printf("%c", buffer[i]);
                    }
                }
            }
        }
    }
}