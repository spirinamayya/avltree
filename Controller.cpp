#include "Controller.h"

Controller::Controller(AVLTree* ptr)
    :ptr(ptr)
{

}

void Controller::action(const View::SendData &data) {
    const std::vector<int> vec = data.addValue;
    if(vec.size() == 0)
        return;
    if(vec.back() == 0)
        ptr->insert(vec[0]);
    else
        ptr->deleteNode(vec[0]);
}