#include <set>
#include <map>
#include "Command.h"
#include "../main.h"

Command::Command(DefaultIO *dio, int userId, string description) : dio(dio), userId(userId), description(description) {}

void Command::writeCSVFile(string filepath, string fileContent) const {
    ofstream ostream(filepath);
    if (!ostream.is_open()) {
        //TODO: print error
    }
    ostream << fileContent;
    ostream.close();
}

int Command::getK() const {
    string filepath = dataDirectory + "/user_" + std::to_string(userId) + ".csv";
    // Open the file
    std::ifstream file(filepath);
    // Check if the file can be opened
    if (!file.is_open()) {
        //TODO: print error
    }
    // Check if the file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::ofstream out_file(filepath);
        if (!out_file.is_open()) {
            //TODO: print error
        }
        // Write default values to the file
        out_file << "5\n";
        out_file << "EUC";
        out_file.close();
        return 5;
    }
    // Read the first line of the file
    std::string line;
    std::getline(file, line);
    file.close();
    // Convert the line to an integer and return it
    return std::stoi(line);
}


DistanceFunction *Command::getDistance() const {
    string filepath = dataDirectory + "/user_" + std::to_string(userId) + ".csv";
    // Open the file
    std::ifstream file(filepath);
    // Check if the file can be opened
    if (!file.is_open()) {
        //TODO: print error
    }
    // Check if the file is empty
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::ofstream out_file(filepath);
        if (!out_file.is_open()) {
            //TODO: print error
        }
        // Write default values to the file
        out_file << "5\n";
        out_file << "EUC";
        out_file.close();
        return new Euclidean;
    }
    // Read the 2nd line of the file
    std::string distanceInput;
    std::getline(file, distanceInput);
    std::getline(file, distanceInput);
    file.close();
    DistanceFunction *function;
    if (distanceInput.compare("EUC") == 0) {
        function = new Euclidean;
    } else if (distanceInput.compare("MAN") == 0) {
        function = new Manhatin;
    } else if (distanceInput.compare("CHB") == 0) {
        function = new Chebyshev;
    } else if (distanceInput.compare("CAN") == 0) {
        function = new Canberra;
    } else if (distanceInput.compare("MIN") == 0) {
        function = new Minkowski;
    } else {
        //std::cout << "Distance Function does not exist" << std::endl;
        return nullptr;
    }
    return function;
}


bool Command::isDataClassified() const {
    string testPredict = dataDirectory + "/user_" + to_string(userId) + "_test.csv";
    ifstream testPredictStream(testPredict);
    char v = testPredictStream.peek();

    return !(testPredictStream.peek() == std::ifstream::traits_type::eof());
}

string Command::getDescription() const {
    return description;
}