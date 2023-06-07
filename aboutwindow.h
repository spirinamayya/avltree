#ifndef COURSEPROJECT_ABOUTWINDOW_H
#define COURSEPROJECT_ABOUTWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutWindow;
}
QT_END_NAMESPACE

namespace mvc {
    class AboutWindow : public QDialog {
        Q_OBJECT

    public:
        explicit AboutWindow(QWidget *parent = nullptr);
        ~AboutWindow();

    private:
        Ui::AboutWindow *ui;
    };
}


#endif//COURSEPROJECT_ABOUTWINDOW_H
