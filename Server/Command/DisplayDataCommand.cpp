#include "DisplayDataCommand.h"
#include "../main.h"

DisplayDataCommand::DisplayDataCommand(DefaultIO *dio, int userId) : Command(dio, userId, "display results") {}

void DisplayDataCommand::execute() {
    string train = dataDirectory + "/user_" + to_string(userId) + "_train.csv";
    bool trainIsEmpty = false;
    ifstream trainContentStream(train);
    trainIsEmpty = trainContentStream.peek() == std::ifstream::traits_type::eof();

    string test = dataDirectory + "/user_" + to_string(userId) + "_test.csv";
    bool testIsEmpty = false;
    ifstream testContentStream(train);
    testIsEmpty = testContentStream.peek() == std::ifstream::traits_type::eof();

    if (trainIsEmpty || testIsEmpty) {
        string s = "please upload data\n";
        dio->write(s);
        return;
    }

    if (!isDataClassified()) {
        dio->write("please classify the data\n");
        return;
    } else {
        dio->write("Sending data.\n");
    }
    ifstream istream(dataDirectory + "/user_" + to_string(userId) + "_test_prediction.csv");
    string word;
    int lineNumber = 1;
    while(getline(istream, word)) {
        dio->write(to_string(lineNumber) + " " + word + "\n");
        lineNumber++;
    }

    dio->write("Done.\n");
}