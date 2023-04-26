#include "Connection.h"

Connection::Connection(MainWindow *mainWindow)
    : _view(mainWindow)
{
    _controller.ptr = &_model;
    _view.subscribe(_controller.input());
    _model.subscribe(_view.input());
}