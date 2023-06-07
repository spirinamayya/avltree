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
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QThread>
#include <QFileDialog>

#include "/Users/mayyaspirina/Documents/CourseProject/Observer/Observer.h"
#include "InfoTree.h"
#include "mainwindow.h"
#include "aboutwindow.h"

namespace mvc {

    class View : public QGraphicsScene{
        Q_OBJECT
    public:
        View();
        ~View() = default;

        enum class Operation {
            Add, Delete, Search, DeleteAll
        };
        struct Command {
            int& value;
            Operation& operation;
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
        void addMenu();
        void addControlPannel();
        void adjustMainWindow();
        void connectObjects();

        void drawNode(Info* cur, std::queue<Info*>& que, int& count, AVLTree::Operation& operation, int passing);
        void drawTree(Info* treeInfo, AVLTree::Operation& operation, int passing);
        void draw(const AVLTree::Data& data);
        void deleteClicked(QPointF& point);

        void inOrderTraversal(Info* node);
        void preOrderTraversal(Info* node);
        void postOrderTraversal(Info* node);

        void getDataFromFile(QString& fileName);

    private slots:
        void addNode();
        void deleteNode();
        void searchNode();
        void inOrder();
        void preOrder();
        void postOrder();
        void aboutMenu();
        void loadMenu();
        void stepBack();

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
        static constexpr int kRadius_ = 40;
    private:
        MainWindow* mainWindow_;
        std::unique_ptr<AboutWindow> secondWindow_;

        QPushButton *addButton_;
        QPushButton *deleteButton_;
        QPushButton* searchButton_;
        QPushButton* inOrderButton_;
        QPushButton* preOrderButton_;
        QPushButton* postOrderButton_;
        QPushButton* stepBackButton_;
        QLineEdit *editText_;
        QLineEdit* count_;
        QSlider* slider_;
        QGraphicsView *treeSpot_;
        CustomScene* scene_;

        std::vector<std::pair<int, Operation>> history_;

        int value_;
        Operation operation_;
        bool load_ = false;
        bool hist_ = false;
        std::unique_ptr<InfoTree> treeInfo_ = nullptr;
        int speed_ = 750;
        ObserverCommand commandPort = Command{value_, operation_};

        Input observer = [this](const AVLTree::Data &data) { draw(data); };
    };
}

#endif//COURSEPROJECT_VIEW_H
