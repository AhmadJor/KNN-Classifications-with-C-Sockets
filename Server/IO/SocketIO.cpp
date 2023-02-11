#include "SocketIO.h"

SocketIO::SocketIO(int clientSock) : sock(clientSock) {}

string SocketIO::read() const {
    char buffer[BUFFER_SIZE] = {0};
    int read_bytes = recv(sock, buffer, BUFFER_SIZE, 0);
    if (read_bytes == 0) {
        return "";
    } else if (read_bytes < 0) {
        perror("Error receiving message from client.\n");
    }

    buffer[BUFFER_SIZE - 1] = '\0';
    string s = string(buffer);
    return s.substr(0, s.find(END_OF_MESSAGE));
}

void SocketIO::write(string str) const {
    string s(str);

    if (s.length() < BUFFER_SIZE) {
        s.insert(str.length(), BUFFER_SIZE - str.length(), END_OF_MESSAGE);
    }

    int sent_bytes = send(sock, s.c_str(), s.length(), 0);
    if (sent_bytes < 0) {
        perror("Error sending message to client.\n");
    }
}

void SocketIO::close() const {
    ::close(sock);
}
