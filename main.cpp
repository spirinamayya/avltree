#include <QApplication>
#include "Application.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mvc::Application c;
    return QApplication::exec();
}
