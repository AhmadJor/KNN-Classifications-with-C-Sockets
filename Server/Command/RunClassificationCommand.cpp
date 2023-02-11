#include <vector>
#include "RunClassificationCommand.h"
#include "../Distances/DistanceFunction.h"
#include "../Classifier.h"
#include "../main.h"

RunClassificationCommand::RunClassificationCommand(DefaultIO* dio, int userId) : Command(dio, userId, "classify data") {}

void RunClassificationCommand::execute() {
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

    } else {
        Classifier *c = new Classifier(getK(), train, test);

        DistanceFunction *d = getDistance();
        c->predictFileByDist(dataDirectory + "/user_" + to_string(userId)
                             + "_test_prediction.csv", *d);
        delete d;
        delete c;
        dio->write("classifying data complete.\n");
    }
}