#include <algorithm>
#include "KnnSettings.h"
#include "../main.h"

KnnSettings::KnnSettings(DefaultIO* dio, int userId) : Command(dio, userId, "algorithm settings") {}



void KnnSettings::execute() {
    int k = getK();
    DistanceFunction* d = getDistance();
    dio->write("The current KNN parameters are: K = " + to_string(k) + ", distance metric = " + d->getName() + "\n");
    delete d;
    string input = "";
    bool validInput = false;
    string strk;
    string distance;
    do {
        input = dio->read();
        if (!input.compare("NONE")) {
            dio->write("DONE\n");
            return;
        }
        stringstream ss(input);
        getline(ss, strk, ' ');
        getline(ss, distance);
        bool strkValid  = false;
        bool distanceValid = false;
        if (!strk.empty() && std::all_of(strk.begin(), strk.end(), ::isdigit)) {
            int vk = stoi(strk);
            strkValid = 0 < vk && vk < 11;
        }
        distanceValid = !distance.compare("EUC")
                     || !distance.compare("MAN")
                     || !distance.compare("CHB")
                     || !distance.compare("CAN")
                     || !distance.compare("MIN");
        if (!strkValid && !distanceValid) dio->write("invalid value for K.\ninvalid value for metric.");
        else if (!strkValid) dio->write("invalid value for K.");
        else if (!distanceValid) dio->write("invalid value for metric.");
        validInput = strkValid && distanceValid;
    } while (!validInput);

    string knnSettingContents = strk + "\n" + distance;
    writeCSVFile(dataDirectory + "/user_" + to_string(userId) + ".csv", knnSettingContents);
    dio->write("DONE\n");
}