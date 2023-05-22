#ifndef COURSEPROJECT_VIEW_H
#define COURSEPROJECT_VIEW_H

#include <QBoxLayout>
#include <QCheckBox>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGroupBox>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QValidator>
#include <QTimer>
#include <QCoreApplication>
#include <QTime>
#include <QTextEdit>
#include <QLabel>
#include <QSpacerItem>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>

#include "/Users/mayyaspirina/Documents/CourseProject/Observer/Observer.h"
#include "InfoTree.h"
#include "mainwindow.h"
#include "aboutwindow.h"

namespace mvc {

    class View : public QGraphicsScene{
        Q_OBJECT
    public:
        View();

        enum class Operation {
            Add, Delete, Search, Traversal
        };
        enum class Type{
            InOrder, PreOrder, PostOrder
        };
        struct Command {
            int& value;
            Operation& operation;
            Type& type;
        };

        void subscribe(NSLibrary::CObserver<Command> *observer) {
            assert(observer);
            commandPort.subscribe(observer);
        }

    private:
        using ObserverAVL = NSLibrary::CObserver<AVLTree::Data>;
        using ObserverCommand = NSLibrary::CObservableData<Command>;
        using Input = NSLibrary::CHotInput<AVLTree::Data>;
    public:
        ObserverAVL* input() { return &observer; }

    private:
        void drawTree(Info* treeInfo, AVLTree::Operation& operation, int passing);
        void drawPrep(const AVLTree::Data& data);
        void deleteClicked(QPointF& point);

    private slots:
        void addNode();
        void deleteNode();
        void searchNode();
        void inOrder();
        void preOrder();
        void postOrder();
        void aboutMenu();

    public:

        class CustomScene : public QGraphicsScene{
        public:
            CustomScene(View* ptr)
                    :ptr(ptr){};
            ~CustomScene() = default;
            virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        private:
            View* ptr;
        };

    private:
        MainWindow* mainWindow;
        AboutWindow* secondWindow_;

        QPushButton *addButton_;
        QPushButton *deleteButton_;
        QPushButton* searchButton_;
        QPushButton* inOrderButton_;
        QPushButton* preOrderButton_;
        QPushButton* postOrderButton_;
        QLineEdit *editText_;
        QLineEdit* count_;
        QSlider* slider_;
        QGraphicsEllipseItem* ellipse_;

        QGraphicsView *treeSpot_;
        CustomScene* scene_;

        int value_;
        Operation operation_;
        Type type_;
        InfoTree* treeInfo_ = nullptr;
        int speed_ = 750;
        static constexpr int RADIUS = 40;
        ObserverCommand commandPort = Command{value_, operation_, type_};

        Input observer = [this](const AVLTree::Data &data) { drawPrep(data); };
    };
}

#endif//COURSEPROJECT_VIEW_H
