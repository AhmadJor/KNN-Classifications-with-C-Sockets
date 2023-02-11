
#include "Command.h"

class RunClassificationCommand : public Command {

    public:
        RunClassificationCommand(DefaultIO* dio, int userId);
        virtual void execute() override;

};


