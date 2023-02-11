//
// Created by Ilan on 1/21/2023.
//

#ifndef ADVANCED_PROGRAMMING_EX4_SERVERSOCKET_H
#define ADVANCED_PROGRAMMING_EX4_SERVERSOCKET_H

#include "IO/SocketIO.h"

class ServerSocket {
private:
    int sock;
    fd_set fdSet;
    struct timeval timeval;

public:
    static const int TIMEOUT_SECONDS = 30;

    ServerSocket(int port = 5555); //create ServerSocket on port 5555
    bool isTimedOut();
    SocketIO* accept();
    void close();
};


#endif //ADVANCED_PROGRAMMING_EX4_SERVERSOCKET_H
