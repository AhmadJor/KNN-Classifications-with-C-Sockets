#include "RecieveDataCommand.h"
#include "../main.h"

RecieveDataCommand::RecieveDataCommand(DefaultIO* dio, int userId) : Command(dio, userId, "upload an unclassified csv data file") {}

void RecieveDataCommand::execute() {
    string trainFileContents = dio->read();
    writeCSVFile(dataDirectory + "/user_" + to_string(userId) + "_train.csv", trainFileContents);
    dio->write("Upload complete.\n");

    string testFileContents = dio->read();
    writeCSVFile(dataDirectory + "/user_" + to_string(userId) + "_test.csv" , testFileContents);
    dio->write("Upload complete.\n");

    string trainPredict = dataDirectory + "/user_" + to_string(userId) + "_train_prediction.csv";
    writeCSVFile(trainPredict, "");
    string testPredict = dataDirectory + "/user_" + to_string(userId) + "_test_prediction.csv";
    writeCSVFile(testPredict, "");
}