#ifndef COURSEPROJECT_MAINWINDOW_H
#define COURSEPROJECT_MAINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

namespace mvc {
    class MainWindow : public QWidget {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);

        ~MainWindow() override;

    private:
        Ui::MainWindow *ui;
    };
}// namespace mvc

#endif//COURSEPROJECT_MAINWINDOW_H
