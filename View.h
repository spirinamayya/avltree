#ifndef COURSEPROJECT_VIEW_H
#define COURSEPROJECT_VIEW_H

#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>
#include <queue>

#include "mainwindow.h"
#include "/Users/mayyaspirina/Documents/CourseProject/Observer/Observer.h"
#include "Model.h"

class View : public QObject
{
    Q_OBJECT
public:
    View(MainWindow* mainWindow);

    bool checkEditorForInteger(QLineEdit* edt, int& res);

    /// Controller to view
    ///struct with data to share with controller, for addition
    struct SendData{
        std::reference_wrapper<const std::vector<int>> addValue;
    };
    ///subscribe controller to view
    void subscribe(NSLibrary::CObserver<SendData>* observer)
    {
        assert(observer);
        addPort.subscribe(observer);
    }


    class Info{
    public:
        Info(){}
        Info(int key, int x, int y)
                : key(key), x(0), y(0), left(nullptr), right(nullptr)
        {}
        int x;
        int y;
        int key;
        Info* left;
        Info* right;
        int width;
    };

    /// View to model
    void drawTree(const AVLTree::ModAddData& data);
    NSLibrary::CObserver<AVLTree::ModAddData>* input() { return &observerAdd; }
    void calcYCoord(const Node* root);
    void postOrder(Info* cur);
    void calcXCoord(Info* root);
    void clear(Info* treeInfo);
    Info* copy(const Node* root);

    void drawCircles();
    void paintEvent(QPaintEvent *event);


private slots:
    void addNode();
    void deleteNode();

private:

    const int R = 40;
    const int H = 30;
    const int W = 20;

    MainWindow* mainWindow;

    QPushButton *addButton;
    QPushButton* deleteButton;
    QLineEdit* editText;

    QGraphicsView* treeSpot;
    QGraphicsScene* scene;

//    std::vector<Info> treeInfo;
    Info* treeInfo;

    std::vector<int> addValue;
    NSLibrary::CObservableData<SendData> addPort = SendData{addValue};

//    NSLibrary::CHotInput<AVLTree::MyData> observerDrawAdd = [this](const AVLTree::MyData& data)
//    { drawAdd(data); };

    NSLibrary::CHotInput<AVLTree::ModAddData> observerAdd = [this](const AVLTree::ModAddData& data)
    { drawTree(data); };
};

#endif //COURSEPROJECT_VIEW_H
