//
// Created by Ilan on 1/24/2023.
//

#ifndef ADVANCED_PROGRAMMING_EX4_CLASSIFIER_H
#define ADVANCED_PROGRAMMING_EX4_CLASSIFIER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Distances/DistanceFunction.h"
#include "Distances/Euclidean.h"
#include "Distances/Manhatin.h"
#include "Distances/Chebyshev.h"
#include "Distances/Canberra.h"
#include "Distances/Minkowski.h"
#include "Distances/Object.h"
#include <map>
#include <string>

class Classifier {
private:
    const int k;
    vector <Object> classified;
    vector <vector<float>> unclassified;
public:
    void predictFileByDist(const string &outputFile, DistanceFunction &distance) const;

    Classifier(int k, const string classifiedData,
               const string unclassifiedData);

    string classify(vector<float> &dataPoint, DistanceFunction &distance);

    vector <Object> read(const string path);
};

#endif //ADVANCED_PROGRAMMING_EX4_CLASSIFIER_H
