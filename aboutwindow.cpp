#include "aboutwindow.h"
#include "ui_AboutWindow.h"

namespace mvc {
    AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AboutWindow) {
        ui->setupUi(this);
    }

    AboutWindow::~AboutWindow() {
        delete ui;
    }
}
