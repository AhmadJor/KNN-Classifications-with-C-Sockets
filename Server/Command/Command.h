#ifndef ADVANCED_PROGRAMMING_COMMAND_H
#define ADVANCED_PROGRAMMING_COMMAND_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../IO/DefaultIO.h"
#include "Command.h"
#include "../Distances/DistanceFunction.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Manhatin.h"
#include "../Distances/Minkowski.h"
#include "../Distances/Canberra.h"
#include "../Distances/Chebyshev.h"

using namespace std;
class Command {
    protected:
        DefaultIO* dio;
        int userId;
        string description;
        int getK() const;
        DistanceFunction* getDistance() const;
        void writeCSVFile(string filepath, string fileContent) const;
        bool isDataClassified() const;
    public:
        Command(DefaultIO* dio, int userId, string description);
        virtual void execute() = 0;
        string getDescription() const;
};

#endif //ADVANCED_PROGRAMMING_COMMAND_H
