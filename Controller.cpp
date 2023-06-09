#include "Controller.h"

namespace mvc {
    Controller::Controller(AVLTree *model)
        : model_(model) {
    }

    void Controller::action(const ViewData &data) {
        switch (data.operation) {
            case View::Operation::Add: {
                model_->insert(data.value);
                break;
            }
            case View::Operation::Delete: {
                model_->deleteNode(data.value);
                break;
            }
            case View::Operation::Search: {
                model_->search(data.value);
                break;
            }
            case View::Operation::DeleteAll: {
                model_->deleteAll();
            }
            default:
                break;
        }
    }
}// namespace mvc
