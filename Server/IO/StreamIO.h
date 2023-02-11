#ifndef ADVANCED_PROGRAMMING_EX4_STREAMIO_H
#define ADVANCED_PROGRAMMING_EX4_STREAMIO_H

#include "DefaultIO.h"
#include <sstream>

class StreamIO : public DefaultIO {
    private:
        stringstream& input;
        stringstream& output;

    public:
        StreamIO(stringstream& input, stringstream& output);

        virtual string read() const override;
        virtual void write(string str) const override;
        virtual void close() const override;
};

#endif //ADVANCED_PROGRAMMING_EX4_STREAMIO_H
