#include "Close.h"

Close::Close(DefaultIO *dio, int userId) : Command(dio, userId, "exit") {}

void Close::execute() {
    dio->close();
}