#include "cli.h"
#include "../main.h"

using namespace std;


CLI::CLI(DefaultIO *dio, int userId) : dio(dio), userId(userId) {
    commands.insert(make_pair(1, new RecieveDataCommand(dio, userId)));
    commands.insert(make_pair(2, new KnnSettings(dio, userId)));
    commands.insert(make_pair(3, new RunClassificationCommand(dio, userId)));
    commands.insert(make_pair(4, new DisplayDataCommand(dio, userId)));
    commands.insert(make_pair(5, new FileUploadCommand(dio, userId)));
    commands.insert(make_pair(8, new Close(dio, userId)));
}

map<int, Command *> CLI::getCommands() {
    return commands;
}

void CLI::run() {
    map<int, Command*> commands = getCommands();
    int op = 1;

    while (op != 8) {
        bool validInput = false;

        do {
            string options;

            std::for_each(commands.begin(), commands.end(), [&](std::pair<const int, Command*>& pair) {
                options += (to_string(pair.first) + ". " + pair.second->getDescription() + "\n");
            });

            dio->write(options);

            string in = dio->read();

            if (!in.empty() && std::all_of(in.begin(), in.end(), ::isdigit)) {
                op = stoi(in);
                validInput = (0 < op && op <= 8);
            }
        } while (!validInput);

        commands.at(op)->execute();
    }

    for(int i = 1; i <= 5; i++) {
        delete commands.at(i);
    }
    delete commands.at(8);
}


void CLI::close() {
    vector<string> files = {
            dataDirectory + "/user_" + to_string(userId) + ".csv",
            dataDirectory + "/user_" + to_string(userId) + "_train.csv",
            dataDirectory + "/user_" + to_string(userId) + "_test.csv",
            dataDirectory + "/user_" + to_string(userId) + "_train_prediction.csv",
            dataDirectory + "/user_" + to_string(userId) + "_test_prediction.csv"
    };

    for (const string& file : files) {
        ifstream stream(file);
        if (stream && remove(file.c_str())) {
            perror(file.c_str());
        }
    }
    dio->close();
}

CLI::~CLI() {
    delete dio;
}