
#include "Command.h"

class Close : public Command {

    public:
        Close(DefaultIO* dio, int userId);
        virtual void execute() override;
};

