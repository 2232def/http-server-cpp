#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "socket failed\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // htonl converts loopback address to network byte order
    address.sin_port = htons(8080);

    if (connect(sock, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "connect failed\n";
        close(sock);
        return 1;
    }

    std::cout << "Connected to server!\n";

    // Receive the server's message
    char buffer[1024] = {0};
    int bytes_read = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read > 0) {
        std::cout << "Server says: " << buffer;
    }

    close(sock);
    return 0;
}