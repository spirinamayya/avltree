#ifndef COURSEPROJECT_CONTROLLER_H
#define COURSEPROJECT_CONTROLLER_H

#include <memory>

#include "Model.h"
#include "View.h"

namespace mvc {
    class Controller {
    private:
        using ViewData = View::Command;
        using Observer = NSLibrary::CObserver<ViewData >;
        using Input = NSLibrary::CColdInput<ViewData >;

    public:
        Controller(AVLTree *ptr);
        Observer *input() { return &observer_; }

    private:
        void action(const ViewData& data);

        AVLTree *model_;
        Input observer_ = [this](const ViewData &data) { action(data); };
    };
}

#endif //COURSEPROJECT_CONTROLLER_H
