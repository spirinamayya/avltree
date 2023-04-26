#include <QApplication>
#include "mainwindow.h"
#include "Connection.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    Connection c(&w);
    w.show();
    return QApplication::exec();
}
