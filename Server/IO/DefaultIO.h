#ifndef ADVANCED_PROGRAMMING_EX4_DEFAULTIO_H
#define ADVANCED_PROGRAMMING_EX4_DEFAULTIO_H

#include <string>

using namespace std;

class DefaultIO {

    public:
        virtual string read() const = 0;

        virtual void write(string str) const = 0;

        virtual void close() const = 0;

};

#endif //ADVANCED_PROGRAMMING_EX4_DEFAULTIO_H
