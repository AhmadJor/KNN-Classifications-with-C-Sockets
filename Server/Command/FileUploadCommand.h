
#include "Command.h"

class FileUploadCommand : public Command {

    public:

        FileUploadCommand(DefaultIO* dio, int userId);

        virtual void execute() override;
};
