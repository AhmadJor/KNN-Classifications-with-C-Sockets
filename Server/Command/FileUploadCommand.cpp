#include "FileUploadCommand.h"
#include "../main.h"
#include <iterator>

using namespace std;

FileUploadCommand::FileUploadCommand(DefaultIO *dio, int userId) : Command(dio, userId, "download results") {}

void FileUploadCommand::execute() {
    if (!isDataClassified()) {
        dio->write("The data hasn't been classified.\nTo classify the data "
                   "choose option 3 from the options screen.\n");
        return;
    } else dio->write("Sending data.\n");
    ifstream istream;
    string testFileContent;
    // Attempts to open file "user_[userId]_test_prediction.csv" from the "server/data" directory.
    istream.open(dataDirectory + "/user_" + to_string(userId) + "_test_prediction.csv");
    if (!istream.good()) {
        //TODO: print error
    }
    std::vector <std::string> lines;
    string line;
    while (getline(istream, line)) {
        lines.push_back(line);
    }

    for (const auto &line: lines)
        testFileContent += line + "\n";

    dio->write(testFileContent);
}
