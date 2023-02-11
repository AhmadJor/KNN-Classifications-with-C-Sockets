#include "../Server/Distances/DistanceFunction.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include "ClientSocket.h"
#include <thread>
#include "main.h"

ClientSocket *sock;

void writeDataToFile(string *filepath, string *fileContents) {
    ofstream s;
    s.open(*filepath);
    if (!s.is_open()) {
        cout << "Error opening file : " + *filepath << endl;
    } else {
        s << *fileContents;
        s.close();
    }

    delete filepath;
    delete fileContents;
}

void run() {
    int commandId = 1;

    while (commandId != 8) {
        bool validInput = false;

        do {
            cout << sock->readLine();
            string in;
            cin >> in;

            if (!in.empty()) {
                try {
                    commandId = stoi(in);
                } catch (...) {
                    //invalid input
                    commandId = -1;
                }
                validInput = (0 < commandId && commandId <= 8);
                sock->writeLine(to_string(commandId));
            }
        } while (!validInput);

        switch (commandId) {
            case 1:
                uploadData();
                break;
            case 2:
                setKnnSettings();
                break;
            case 3:
                classifyData();
                break;
            case 4:
                displayData();
                break;
            case 5:
                downloadData();
                break;
            default:
                break;
        }
    }
}

void uploadData() {
    ifstream is;
    string filePath;
    while (true) {
        cout << "Please upload your local train csv file." << endl;
        cin >> filePath;
        is.open(filePath);

        if (!is) {
            cout << "File not found. ";
            is.close();
        } else {
            break;
        }
    }

    if (!is.is_open()) {
        perror("Error opening file");
    }

    string fileContents;
    fileContents.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());
    is.close();

    sock->writeLine(fileContents);

    cout << sock->readLine();

    while (true) {
        cout << "Please upload your local test csv file." << endl;
        cin >> filePath;
        is.open(filePath);

        if (!is) {
            cout << "File not found. ";
            is.close();
        } else {
            break;
        }
    }

    is.open(filePath);
    if (!is.is_open()) {
        perror("Error opening file");
    }

    fileContents.assign(istreambuf_iterator<char>(is), istreambuf_iterator<char>());
    sock->writeLine(fileContents);
    is.close();

    sock->readLine();
}

void setKnnSettings()  {
    cout << sock->readLine();

    string input;
    string serverMessage = "";

    do {
        cin.clear();
        cin.ignore();
        string strk, distance;
        char c = cin.get();

        if (c == '\n') {
            input = "NONE";
        } else {
            cin.putback(c);
            cin >> strk;
            cin >> distance;

            input = strk + " " + distance;
        }

        sock->writeLine(input);

        serverMessage = sock->readLine();

        if (serverMessage.compare("DONE\n")) {
            cout << serverMessage;
        }
    } while (serverMessage.compare("DONE\n"));
}

void classifyData()  {
    cout << sock->readLine();
}

void displayData()  {
    string str = sock->readLine();

    if (str.compare("Sending data.\n")) {
        cout << str;
    } else {
        while (str.compare("Done.\n")) {
            str = sock->readLine();
            cout << str;
        }
    }

    char c;
    do {
        cin.clear();
        cin.ignore();
        c = cin.get();
    } while (c != '\n');
}

void downloadData() {
    string str = sock->readLine();

    if (equal(str.begin(), str.end(), "The data hasn't been classified.\nTo classify the data "
                                           "choose option 3 from the options screen.\n")) {
        cout << str;

        char c;
        do {
            cin.clear();
            cin.ignore();
            c = cin.get();
        } while (c != '\n');

        return;
    }

    cout << "Enter path for data-file:\n";
    string filepath;
    cin >> filepath;

    ofstream s;
    s.open(filepath);
    bool is_open = s.is_open();
    s.close();

    while (!is_open) {
        cout << "The path you entered was not valid." << endl;
        cout << "Please enter a valid path for data-file:\n";

        cin >> filepath;

        ofstream st;
        st.open(filepath);
        is_open = st.is_open();
        st.close();
    }

    thread thread(writeDataToFile, new string(filepath), new string(sock->readLine()));
    thread.detach();
}

int main() {
    sock = new ClientSocket();
    run();
    sock->closeConnection();

    delete sock;
}
