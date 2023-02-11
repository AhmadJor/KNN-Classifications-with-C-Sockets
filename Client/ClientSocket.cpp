#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "ClientSocket.h"

ClientSocket::ClientSocket(const std::string server_ip, const int port) : sock(socket(AF_INET, SOCK_STREAM, 0)) {
    if (sock < 0) {
        perror("Error creating socket.\n");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(server_ip.c_str());
    sin.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error connecting to server.\n");
    }
}

void ClientSocket::writeLine(const std::string str) const {
    //copy string
    string s(str);

    //add end of message chars
    if (s.length() < BUFFER_SIZE) {
        s.insert(str.length(), BUFFER_SIZE - str.length(), END_OF_MESSAGE);
    }

    //send message
    int sent_bytes = send(sock, s.c_str(), s.length(), 0);
    if (sent_bytes < 0) {
        perror("Error sending message to server.\n");
    }
}

string ClientSocket::readLine() const {
    char buffer[BUFFER_SIZE] = {0};
    int readBytes = recv(sock, buffer, BUFFER_SIZE, 0);
    if (readBytes == 0) {
        perror("Connection is not open\n");
        exit(2);
    } else if (readBytes < 0) {
        perror("Error reading bytes\n");
        exit(3);
    }

    buffer[BUFFER_SIZE - 1] = '\0';
    string s = string(buffer);
    return s.substr(0, s.find(END_OF_MESSAGE));
}

void ClientSocket::closeConnection() const {
    close(sock);
}
