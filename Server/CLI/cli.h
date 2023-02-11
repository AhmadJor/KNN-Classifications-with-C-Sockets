//
// Created by Ilan on 1/24/2023.
//

#ifndef ADVANCED_PROGRAMMING_EX4_CLI_H
#define ADVANCED_PROGRAMMING_EX4_CLI_H

#include "../IO/DefaultIO.h"
#include "../Command/Command.h"
#include "../Command/Close.h"
#include "../Command/DisplayDataCommand.h"
#include "../Command/FileUploadCommand.h"
#include "../Command/RecieveDataCommand.h"
#include "../Command/KnnSettings.h"
#include "../Command/RunClassificationCommand.h"
#include <map>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>



class CLI {

private:
    DefaultIO* dio;
    int userId;
    map<int, Command *> commands;
public:
    CLI(DefaultIO* dio, int userId);
    void run();
    map<int, Command*> getCommands();
    void close();
    ~CLI();
};


#endif //ADVANCED_PROGRAMMING_EX4_CLI_H
