#include "RunnerThread.h"
#include "CLI/cli.h"

void *RunnerThread(void *arg) {
    CLI *server = (CLI *) arg;

    server->run();
    server->close();

    delete server;
}
