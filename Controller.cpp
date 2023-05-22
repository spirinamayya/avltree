#include "Controller.h"

namespace mvc {
    Controller::Controller(AVLTree *model)
        : model_(model) {
    }

    void Controller::action(const ViewData &data) {
        if(data.operation == View::Operation::Add)
            model_->insert(data.value);
        else if(data.operation == View::Operation::Delete)
            model_->deleteNode(data.value);
        else if(data.operation == View::Operation::Search)
            model_->search(data.value);
        else if(data.operation == View::Operation::Traversal && data.type == View::Type::InOrder)
            model_->inOrder();
        else if(data.operation == View::Operation::Traversal && data.type == View::Type::PreOrder)
            model_->preOrder();
        else
            model_->postOrder();
    }
}
