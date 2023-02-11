
#include "ServerSocket.h"
#include <string.h>

ServerSocket::ServerSocket(int port) {
    this->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Error creating socket\n");
    }

    int enableBind = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enableBind, sizeof(int)) < 0) {
        perror("setsockopt failed\n");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error binding socket\n");
    }

    if (listen(sock, 5) < 0) {
        perror("Error listening to socket\n");
    }

    FD_ZERO(&fdSet);
    FD_SET(sock, &fdSet);

    this->timeval.tv_sec = TIMEOUT_SECONDS;
    this->timeval.tv_usec = 0;
}

bool ServerSocket::isTimedOut() {
    int error = 0;
    socklen_t len = sizeof(error);
    int returnVal = getsockopt(this->sock, SOL_SOCKET, SO_ERROR, &error, &len);
    if (returnVal != 0) {
        perror("getsockopt failed\n");
        return true;
    }
    if (error != 0) {
        // Socket has a non zero error status
        return true;
    }
    return false;
}

SocketIO *ServerSocket::accept() {
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);

    int client_sock = ::accept(sock, (struct sockaddr *) &client_sin, &addr_len);

    if (client_sock < 0) {
        perror("Error accepting client\n");
    }

    this->timeval.tv_sec = TIMEOUT_SECONDS;
    this->timeval.tv_usec = 0;
    return new SocketIO(client_sock);
}

void ServerSocket::close() {
    ::close(sock);
}