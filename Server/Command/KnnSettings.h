#include "Command.h"
#include <sstream>
#include "../Distances/Manhatin.h"
#include "../Distances/Minkowski.h"
#include "../Distances/Euclidean.h"
#include "../Distances/Chebyshev.h"

class KnnSettings : public Command {

    public:

        KnnSettings(DefaultIO* dio, int userId);

        void execute() override;
};


