#include <QApplication>
#include "mainwindow.h"
#include "Connection.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mvc::Application c;
    return QApplication::exec();
}
