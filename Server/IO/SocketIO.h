#ifndef ADVANCED_PROGRAMMING_EX4_SOCKETIO_H
#define ADVANCED_PROGRAMMING_EX4_SOCKETIO_H

#include "DefaultIO.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>

class SocketIO : public DefaultIO {
    private:
        int sock;

    public:
        static const int BUFFER_SIZE = 4096;
        static const char END_OF_MESSAGE = '\003';

        SocketIO(int clientSock);

        virtual string read() const override;
        virtual void write(string str) const override;
        void close() const override;
};


#endif //ADVANCED_PROGRAMMING_EX4_SOCKETIO_H