
#include "Command.h"


class DisplayDataCommand : public Command {

    public:
        DisplayDataCommand(DefaultIO* dio, int userId);

        virtual void execute() override;
};
