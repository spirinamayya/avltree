#include "View.h"

View::View(MainWindow* mainWindow)
        : mainWindow(mainWindow)
{
    addButton = new QPushButton("Add node");
    deleteButton = new QPushButton("Delete node");
    editText = new QLineEdit();

    treeSpot = new QGraphicsView();
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::white);
    treeSpot->setScene(scene);

    QVBoxLayout *layout = new QVBoxLayout(mainWindow);

    layout->addWidget(editText);
    layout->addWidget(addButton);
    layout->addWidget(deleteButton);
    layout->addWidget(treeSpot);

    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addNode()));
    QObject::connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteNode()));

}

bool View::checkEditorForInteger(QLineEdit* edt, int& res)
{
    bool convOk;
    res = edt->text().toInt(&convOk);
    if (!convOk)
    {
        QMessageBox msgBox;
        msgBox.setText(edt->objectName() + " not integer");
        msgBox.exec();
        return false;
    }
    return true;
}

void View::addNode()
{
    addValue.clear();
    int val;
    if (!checkEditorForInteger(editText, val)) {
        editText->clear();
        return;
    }
    addValue.push_back(editText->text().toInt());
    addValue.push_back(0);
    editText->clear();
    addPort.notify();
}

void View::deleteNode()
{
    addValue.clear();
    int val;
    if (!checkEditorForInteger(editText, val)) {
        editText->clear();
        return;
    }
    addValue.push_back(editText->text().toInt());
    addValue.push_back(1);
    editText->clear();
    addPort.notify();
}

void View::clear(Info* treeInfo)
{
    if(treeInfo != nullptr)
    {
        clear(treeInfo->left);
        clear(treeInfo->right);
        delete treeInfo;
    }
}

View::Info* View::copy(const Node* root)
{
    if(root == nullptr)
        return nullptr;
    else{
        Info* temp = new Info;
        temp->key = root->key;
        temp->left = copy(root->leftCh);
        temp->right = copy(root->rightCh);
        return temp;
    }
}

void View::calcYCoord(const Node* rootGet)
{
    clear(treeInfo);
    ///create copy of a tree
    treeInfo = copy(rootGet);
    Info* root = treeInfo;
    if (root == nullptr)
        return;
    ///implement level-order traversal
    std::queue<Info*> que;
    que.push(root);
    Info* cur;
    int count = 0, timesNow = 1, timesNext = 0;
    while (!que.empty()) {
        cur = que.front();
        que.pop();
        cur->y = count * (2 * R + H);
        if (cur->left != nullptr){
            que.push(cur->left);
            ++timesNext;
        }
        if (cur->right != nullptr){
            que.push(cur->right);
            ++timesNext;
        }
        --timesNow;
        if(timesNow == 0)
        {
            ++count;
            timesNow = timesNext;
            timesNext = 0;
        }
    }
}

void View::postOrder(Info* cur)
{
    if (cur == nullptr)
        return;
    postOrder(cur->left);
    postOrder(cur->right);

    if(cur->right == nullptr && cur->left == nullptr)
        cur->width = 2 * R;
    else if(cur->left == nullptr)
        cur->width = cur->right->width + W;
    else if(cur->right == nullptr)
        cur->width = cur->left->width + W;
    else
        cur->width = cur->left->width + cur->right->width + W;
}

void View::calcXCoord(Info* rootGet) {
    Info* coord = rootGet;
    ///post-order tree traversal
    postOrder(coord);
    ///implement level-order traversal
    Info* root = treeInfo;
    if (root == nullptr)
        return;
    std::queue<Info*> que;
    que.push(root);
    Info* cur;
    int count = 0, timesNow = 1, timesNext = 0;
    while (!que.empty()) {
        cur = que.front();
        que.pop();
        if (cur->left != nullptr){
            que.push(cur->left);
            ++timesNext;
            cur->left->x = cur->x - W / 2 - cur->left->width / 2;
        }
        if (cur->right != nullptr){
            que.push(cur->right);
            ++timesNext;
            cur->right->x = cur->x + W / 2 + cur->right->width / 2;
        }
        --timesNow;
        if(timesNow == 0)
        {
            ++count;
            timesNow = timesNext;
            timesNext = 0;
        }
    }
}

void View::drawCircles()
{
    scene->clear();
    scene->setBackgroundBrush(Qt::white);
    Info* root = treeInfo;
    if (root == nullptr)
        return;
    std::queue<Info*> que;
    que.push(root);
    Info* cur;
    while (!que.empty()) {
        cur = que.front();
        que.pop();

        QBrush redbrush(Qt::red);
        QPen blackpen(Qt::black);
        blackpen.setWidth(3);

        QGraphicsEllipseItem* ellipse = scene->addEllipse(cur->x,cur->y,40,40,blackpen, redbrush);

        QGraphicsTextItem *text = scene->addText(QString::number(cur->key));
        text->setPos(cur->x + 10, cur->y + 10);

        if (cur->left != nullptr) {
            que.push(cur->left);
            scene->addLine(cur->x + 10, cur->y + 35, cur->left->x + 20, cur->left->y + 5);
        }
        if (cur->right != nullptr) {
            que.push(cur->right);
            scene->addLine(cur->x + 30, cur->y + 35, cur->right->x + 10, cur->right->y + 5);
        }
    }
}


void View::drawTree(const AVLTree::ModAddData &data) {
    const Node* root = data.Value;
    if(root == nullptr) {
        scene->clear();
        return;
    }

    ///create tree that will help to draw
    calcYCoord(root);
    calcXCoord(treeInfo);

    drawCircles();
}
