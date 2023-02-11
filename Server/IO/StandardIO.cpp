#include "StandardIO.h"

string StandardIO::read() const {
    string str;
    getline(cin, str);
    return str;
}

void StandardIO::write(string str) const {
    cout << str << endl;
}

void StandardIO::close() const {}