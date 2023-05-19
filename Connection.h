#ifndef COURSEPROJECT_CONNECTION_H
#define COURSEPROJECT_CONNECTION_H

#include "Controller.h"

namespace mvc {
    class Application {
    public:
        Application();

    private:
        AVLTree model_;
        View view_;
        Controller controller_{&model_};
    };
}
#endif //COURSEPROJECT_CONNECTION_H
