#include "vector"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ServerSocket.h"
#include "CLI/cli.h"
#include "RunnerThread.h"
#include "main.h"

bool dirIsEmpty(string dirname) {
    int n = 0;
    struct dirent *d;
    DIR *dir = opendir(dirname.c_str());
    if (dir == NULL) //Not a directory or doesn't exist
        return true;
    while ((d = readdir(dir)) != NULL) {
        if(++n > 2)
            break;
    }

    closedir(dir);
    if (n <= 2) //Directory Empty
        return true;
    else
        return false;
}

bool dirExists(string dirname) {
    DIR *dir = opendir(dirname.c_str());
    bool flag = dir != NULL;
    free(dir);
    return flag;
}

int main() {
    //make sure dir exists
    if (!dirExists(dataDirectory)) {
        mkdir(dataDirectory.c_str(), 0777);
    }

    int maxId = 0;
    ServerSocket *serverSocket = new ServerSocket();

    while (true) {
        try {
            if (!serverSocket->isTimedOut()) {
                SocketIO *socketIO = serverSocket->accept();
                pthread_t thread_id;
                maxId++;
                CLI *server = new CLI(socketIO, maxId);

                pthread_create(&thread_id, NULL, RunnerThread, (void *) server);
                pthread_detach(thread_id);
            }
        } catch (...) {
            break;
        }
    }

    delete serverSocket;
}