#include <stdio.h>      // printf, scanf
#include <sys/socket.h> // socket
#include <stdlib.h>     // exit
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#include <string.h>
#define PORT 8886
#define IP_ADDR "127.0.0.1"
int main()
{
    // CREATE SOCKET
    int main_socket_fd;
    main_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET - IPv4, SOCK_STREAM - TCP, 0 - IPPROTO_TCP,indicates that the TCP protocol is to be used
    if (main_socket_fd < 0)
    {
        printf("Socket error\n");
        exit(1);
    }
    // CREATE ADDRESS
    struct sockaddr_in address;                   // sockaddr_in - structure for storing an IP address and port number.
    address.sin_family = AF_INET;                 // sin_family - address family (AF_INET - IPv4)
    address.sin_addr.s_addr = inet_addr(IP_ADDR); // sin_addr.s_addr - IP address in network byte order (htonl - convert long integer to network byte order)
    address.sin_port = htons(PORT);               // sin_port - port number in network byte order (htons - convert short integer to network byte order)
    // BIND SOCKET WITH PORT
    int bind_res = bind(main_socket_fd, (struct sockaddr *)&address, sizeof(address)); // bind - bind a socket to an address.
    if (bind_res < 0)
    {
        printf("Bind error\n");
        exit(1);
    }
    // PREPARE THE SOCKET TO CONNECT WITH CLIENT
    int listen_res = listen(main_socket_fd, 3); // listen - listen for connections on a socket., main_socket_fd - socket file descriptor, 3 - backlog, maximum number of queued connections.
    if (listen_res < 0)
    {
        printf("Listen error\n");
        exit(1);
    }
    fd_set readfds; // fd_set - file descriptor set, used for select() function.
                    /*
                       An fd_set is a set of sockets to "monitor" for some activity. There are four useful macros : FD_CLR, FD_ISSET, FD_SET, FD_ZERO for dealing with an fd_set.
                
                       FD_ZERO - Clear an fd_set
                       FD_ISSET - Check if a descriptor is in an fd_set
                       FD_SET - Add a descriptor to an fd_set
                       FD_CLR - Remove a descriptor from an fd_set
                   */
    int new_sockets[30] = {0};
    int max_fd_val = 0;
    while (1)
    {
        // ADDING ALL SOCKETS TO readfds
        FD_ZERO(&readfds);                // FD_ZERO - Clear an fd_set
        FD_SET(main_socket_fd, &readfds); // FD_SET - Add a descriptor to an fd_set, main_socket_fd - socket file descriptor., &readfds - pointer to an fd_set.
        max_fd_val = main_socket_fd;      // max_fd_val - maximum file descriptor value., main_socket_fd - socket file descriptor.
        /* Here is the explanation for the code above:
            1. We create a new fd_set and initialize it with the new_sockets array.
            2. We check if the new_sockets array has a value greater than 0. If it does, we add it to the readfds fd_set.
            3. We check if the new_sockets array has a value greater than max_fd_val. If it does, we set max_fd_val to that value.
        */
        for (int i = 0; i < 30; i++)
        {
            if (new_sockets[i] > 0)
            {
                FD_SET(new_sockets[i], &readfds);
                if (new_sockets[i] > max_fd_val)
                {
                    max_fd_val = new_sockets[i];
                }
            }
        }
        // CHECKING FOR ACTIVITY
        /*
        The select method takes a list of socket for monitoring them. Here is how :

        activity = select( max_fd + 1 , &readfds , NULL , NULL , NULL);

        The select function blocks , till an activity occurs.
        For example when a socket is ready to be read ,
        select will return and readfs will have those sockets
        which are ready to be read.
        */
        select(max_fd_val + 1, &readfds, NULL, NULL, NULL);
        // IS ACTIVITY IN MAIN SOCKET
        if (FD_ISSET(main_socket_fd, &readfds))
        {                                                                                                 // FD_ISSET - Check if a descriptor is in an fd_set
            int addrlen = sizeof(address);                                                                // addrlen - length of the structure sockaddr.
            int new_sock_fd = accept(main_socket_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen); // accept - accept a connection on a socket.
            if (new_sock_fd < 0)
            { // new_sock_fd - new socket file descriptor.
                printf("Connection error\n");
                exit(1);
            }
            printf("New connection established");
            /* Here is the explanation for the code above:
                1. We create a new array of sockets.
                2. We loop through the array of sockets and check if there is a socket with a value of 0.
                3. If there is a socket with a value of 0, we set the value of that socket to the new socket.
                4. We break out of the loop.
                5. We return the new socket. */
            for (int i = 0; i < 30; i++)
            {
                if (new_sockets[i] == 0)
                {
                    new_sockets[i] = new_sock_fd;
                    break;
                }
            }
        }
        // IS ACTIVITY IN OTHER SOCKETS
        for (int i = 0; i < 30; i++)
        {
            int fd = new_sockets[i]; // fd - socket file descriptor.
            // RECV DATA
            if (FD_ISSET(fd, &readfds))
            {                                        // FD_ISSET - Check if a descriptor is in an fd_set
                char buffer[1024];  
                                 // buffer - buffer for storing data.
                int len = recv(fd, buffer, 1024, 0); // len - length of the data received.,recv - receive a message on a socket.
                buffer[len]= i+'0';
                buffer[len+1] = '\0';                  // buffer[len] - null character.
               // printf("%d: %s\n", fd, buffer);
                // BROADCAST DATA
                for (int i = 0; i < 30; i++)
                {
                    int fd2 = new_sockets[i];
                    if (fd2 != fd && fd2 != 0)
                    {                                         // the condition checks if the socket is not the same as the current socket and if the socket is not 0.
                        send(fd2, buffer, strlen(buffer), 0); // send - send a message on a socket.
                       // printf("Sent to %d\n", fd2);
                    }
                }
            }
        }
    }
}