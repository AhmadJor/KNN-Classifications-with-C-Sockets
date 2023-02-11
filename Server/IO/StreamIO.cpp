#include "StreamIO.h"

StreamIO::StreamIO(std::stringstream &input, std::stringstream &output) : input(input), output(output) {}

string StreamIO::read() const {
    string str;
    input >> str;
    return str;
}

void StreamIO::write(string str) const {
    output << str;
}

void StreamIO::close() const {}