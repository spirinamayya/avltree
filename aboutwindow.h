#ifndef COURSEPROJECT_ABOUTWINDOW_H
#define COURSEPROJECT_ABOUTWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

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
}// namespace mvc


#endif//COURSEPROJECT_ABOUTWINDOW_H
