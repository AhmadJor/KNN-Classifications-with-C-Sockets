
#ifndef ADVANCED_PROGRAMMING_EX4_CLIENTSOCKET_H
#define ADVANCED_PROGRAMMING_EX4_CLIENTSOCKET_H

#include <string>

using namespace std;

class ClientSocket {
private:
    const int sock;

public:
    static const int BUFFER_SIZE = 4096;
    static const char END_OF_MESSAGE = '\003';

    ClientSocket(const string ip = "127.0.0.1", const int port = 5555);

    void writeLine(const string str) const;

    string readLine() const;

    void closeConnection() const;
};

#endif //ADVANCED_PROGRAMMING_EX4_CLIENTSOCKET_H
