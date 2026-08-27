#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main()
{ 
    //this is to create the socket (domain, type, protocol)
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //struct sockaddr_in is used to store the address of the socket
    struct sockaddr_in address{};
    address.sin_family = AF_INET; // AF_INET is the address family for IPv4
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // INADDR_LOOPBACK needs htonl() to convert to network byte order (127.0.0.1)
    address.sin_port = htons(8080); // htons is used to convert the port number to network byte order 

    // connect(sock, (sockaddr *)&address, sizeof(address));
    
    int reuse = 1; // set the reuse = 1 to allow the socket to be reused immediately after it is closed
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse , sizeof(reuse)) < 0) // setsockopt is used to set the options for the socket 
    {
        std::cerr << "setsockopt failed\n"; 
        return 1;
    }

    if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0 ) // bind is used to bind the socket to the address and port specified in the address struct
    {
        std::cerr << "bind failed\n";
        return 1;
    }

    int connection_backlog = 5; // connection_backlog is the number of connections that can be queued up before the server starts rejecting new connections
    if (listen(sock, connection_backlog) != 0) // listen is used to listen for incoming connections on the socket
    {
        std::cerr << "listen failed\n";
        return 1;
    }

    struct sockaddr_in client_addr; // struct sockaddr_in is used to store the address of the client that connects to the server
    int client_addr_len = sizeof(client_addr); // client_addr_len is used to store the size of the client_addr struct

    std::cout << "Waiting for a client to connect...\n";

    int client_fd = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len); // accept returns the file descriptor for the connected client
    if (client_fd < 0) {
        std::cerr << "accept failed\n";
        close(sock);
        return 1;
    }
    std::cout << "Client connected!\n";

    // Read the incoming HTTP request from the client
    char buffer[1024] = {0};
    recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    std::cout << "Request:\n" << buffer << "\n";

    // Send an HTTP response back to the client
    const char* msg = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";
    send(client_fd, msg, strlen(msg), 0);

    close(client_fd); // close the client connection
    close(sock);      // close the server socket

    return 0;
}
