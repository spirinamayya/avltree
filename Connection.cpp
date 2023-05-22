#include "Connection.h"

namespace mvc {
        Application::Application() {
        view_.subscribe(controller_.input());
        model_.subscribe(view_.input());
    }
}
