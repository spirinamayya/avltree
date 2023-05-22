#include "mainwindow.h"
#include "ui_MainWindow.h"

namespace mvc {
    MainWindow::MainWindow(QWidget *parent)
        : QWidget(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        this->setAttribute(Qt::WA_AcceptTouchEvents, true);
    }

    MainWindow::~MainWindow() {
        delete ui;
    }

}
