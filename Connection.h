#ifndef COURSEPROJECT_CONNECTION_H
#define COURSEPROJECT_CONNECTION_H

#include "Controller.h"

class Connection{
public:
    Connection(MainWindow* mainWindow);
    //~Connection();

private:
    AVLTree _model;
    View _view;
    Controller _controller;
};

#endif //COURSEPROJECT_CONNECTION_H
