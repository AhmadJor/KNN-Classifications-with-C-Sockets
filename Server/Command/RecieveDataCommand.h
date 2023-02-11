
#include "Command.h"
#include <string>


class RecieveDataCommand : public Command {
    public:
        RecieveDataCommand(DefaultIO* dio, int userId);
        virtual void execute() override;
};

