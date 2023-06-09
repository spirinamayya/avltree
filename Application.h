#ifndef COURSEPROJECT_APPLICATION_H
#define COURSEPROJECT_APPLICATION_H

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
}// namespace mvc

#endif//COURSEPROJECT_APPLICATION_H
