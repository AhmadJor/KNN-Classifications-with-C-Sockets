#include "Classifier.h"

using namespace std;

map<float, string>
CalculateDistances(DistanceFunction &distanceFunction, vector <Object> classified, vector<float> inputVector) {
    map<float, string> distances;
    for (int i = 0; i < classified.size(); ++i) {
        float distance = distanceFunction.Distance(classified[i].getData(), inputVector);
        distances.insert(pair<float, string>(distance, classified[i].getName()));
    }
    return distances;
}

map<string, int> CountKClosestObjects(int k, map<float, string> distances) {
    //count closest k names according to their names
    map<string, int> kth_elements;
    //run over k closest objects
    for (int i = 0; i < k; ++i) {
        //if first occurrence
        if (kth_elements.count(distances.begin()->second) == 0)
            kth_elements[distances.begin()->second] = 1;
        else
            kth_elements[distances.begin()->second]++;
        //erase the lowest distance
        distances.erase(distances.begin()->first);
    }
    return kth_elements;
}

//returns maximum occurred name in closestK (map<string, int> = <name, numOccurrences>)
string GetMaximumOccurrences(map<string, int> closestK) {
    pair<string, int> max = *closestK.begin();
    closestK.erase(closestK.begin()->first);
    for (int i = 0; i < closestK.size(); ++i) {
        if (max.second < closestK.begin()->second)
            max = *closestK.begin();
        closestK.erase(closestK.begin()->first);
    }
    return max.first;
}

vector<float> convertVector(vector <string> arr) {
    vector<float> v1;
    for (int i = 0; i < arr.size(); ++i) {
        v1.push_back(atof(arr[i].c_str()));
    }
    return v1;
}


Object convert(vector <string> arr) {
    vector<float> v1;
    for (int i = 0; i < arr.size() - 1; ++i) {
        v1.push_back(atof(arr[i].c_str()));
    }
    Object object = Object(arr[arr.size() - 1], v1);
    return object;
}


vector <string> split(string str, char delim) {
    vector <string> arr;
    string temp = "";
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != delim)
            temp += str[i];
        else {
            arr.push_back(temp);
            temp = "";
        }
    }
    arr.push_back(temp);
    return arr;
}

vector <Object> readClassified(const string path) {
    vector <Object> result;
    fstream file;
    file.open(path, ios::in);
    if (!file) {
        cout << "No such file" << endl;
        exit(1);
    }

    int lineSize = -1;
    string line;
    while (getline(file, line)) {
        vector <string> splitted = split(line, ',');
        if (lineSize == -1)
            lineSize = splitted.size();
        else {
            if (splitted.size() != lineSize) {
                cout << "Error reading file" << endl;
                exit(1);
            }
        }
        Object temp = convert(splitted);
        result.push_back(temp);
    }
    return result;
}

vector <vector<float>> readUnClassified(const string path) {
    vector <vector<float>> result;
    fstream file;
    file.open(path, ios::in);
    if (!file) {
        cout << "No such file" << endl;
        exit(1);
    }

    int lineSize = -1;
    string line;
    while (getline(file, line)) {
        vector <string> splitted = split(line, ',');
        if (lineSize == -1)
            lineSize = splitted.size();
        else {
            if (splitted.size() != lineSize) {
                cout << "Error reading file" << endl;
                exit(1);
            }
        }
        vector<float> temp = convertVector(splitted);
        result.push_back(temp);
    }
    return result;
}

Classifier::Classifier(int k, const string classifiedData,
                       const string unclassifiedData) : k(k) {
    classified = readClassified(classifiedData);
    unclassified = readUnClassified(unclassifiedData);
}

void Classifier::predictFileByDist(const string &outputFile, DistanceFunction &distance) const {
    ofstream outfile;
    outfile.open(outputFile, ios::out);
    for (vector<float> inputVector: unclassified) {
        //check if vector of correct size
        if (inputVector.size() != classified[0].getData().size()) {
            cout << "Vector of incorrect size" << endl;
            continue;
        }

        map<float, string> distances = CalculateDistances(distance, classified, inputVector);
        map<string, int> closestK = CountKClosestObjects(k, distances);
        string name = GetMaximumOccurrences(closestK);

        //write to file
        outfile << name << endl;
    }
    outfile.close();
}