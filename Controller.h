#ifndef COURSEPROJECT_CONTROLLER_H
#define COURSEPROJECT_CONTROLLER_H

#include <memory>

#include "Model.h"
#include "View.h"

class Controller {
public:
    Controller() = default;
    Controller(AVLTree* ptr);

    ///what to do with data
    void action(const View::SendData& data);

    ///subscribe controller to view
    NSLibrary::CObserver<View::SendData>* input() { return &observerAdd; }

    ///public, but let it be like that
    AVLTree* ptr;

private:
    NSLibrary::CHotInput<View::SendData> observerAdd = [this](const View::SendData& data)
            { action(data); };
    NSLibrary::CHotInput<View::SendData> observerDelete = [this](const View::SendData& data)
    { action(data); };
};


#endif //COURSEPROJECT_CONTROLLER_H
