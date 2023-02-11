#ifndef ADVANCED_PROGRAMMING_EX4_STANDARDIO_H
#define ADVANCED_PROGRAMMING_EX4_STANDARDIO_H

#include "DefaultIO.h"
#include <iostream>

/**
 * @brief The StandardIO class
 *
 * This class is Responsible for communicating with the client via the terminal.
 * It is an IO class, and thus it inherits from the DefaultIO class.
 */
class StandardIO : public DefaultIO {

    public:
        virtual string read() const override;
        virtual void write(string str) const override;
        virtual void close() const override;
};


#endif //ADVANCED_PROGRAMMING_EX4_STANDARDIO_H
