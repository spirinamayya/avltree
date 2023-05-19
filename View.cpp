#include "View.h"

namespace mvc {

    View::View() {
        mainWindow = new MainWindow();
        mainWindow->show();
        addButton_ = new QPushButton("Add node", mainWindow);
        deleteButton_ = new QPushButton("Delete node", mainWindow);
        searchButton_ = new QPushButton("Search node", mainWindow);

        inOrderButton_ = new QPushButton("Inorder traversal", mainWindow);
        preOrderButton_ = new QPushButton("Preorder traversal", mainWindow);
        postOrderButton_ = new QPushButton("Postorder traversal", mainWindow);

        QValidator *validator = new QIntValidator(mainWindow);
        editText_ = new QLineEdit(mainWindow);
        editText_->setValidator(validator);

        treeSpot_ = new QGraphicsView(mainWindow);
        scene_ = new CustomScene(this);
        scene_->setBackgroundBrush(Qt::white);
        treeSpot_->setScene(scene_);

        QHBoxLayout* layout = new QHBoxLayout(mainWindow);

        QGroupBox* box = new QGroupBox(mainWindow);
        QVBoxLayout* buttonLayout = new QVBoxLayout(box);
        layout->addWidget(treeSpot_, 75);
        layout->addWidget(box, 25);
        buttonLayout->setSpacing(15);
        buttonLayout->setAlignment(Qt::AlignTop);

        QLabel* header1 = new QLabel(mainWindow);
        header1->setText(tr("Type integer:"));
        buttonLayout->addWidget(header1);
        buttonLayout->addWidget(editText_);
        buttonLayout->addWidget(addButton_);
        buttonLayout->addWidget(deleteButton_);
        buttonLayout->addWidget(searchButton_);

        QSpacerItem* spacer = new QSpacerItem(2, 70);
        buttonLayout->addSpacerItem(spacer);
        QLabel* header2 = new QLabel(mainWindow);
        header2->setText(tr("Tree traversals:"));
        buttonLayout->addWidget(header2);
        buttonLayout->addWidget(inOrderButton_);
        buttonLayout->addWidget(preOrderButton_);
        buttonLayout->addWidget(postOrderButton_);

        buttonLayout->addSpacerItem(spacer);
        QLabel* header3 = new QLabel(mainWindow);
        header3->setText(tr("Node count:"));
        buttonLayout->addWidget(header3);
        count_ = new QLineEdit(mainWindow);
        count_->setReadOnly(true);
        count_->setFixedSize(50, 50);
        count_->setAlignment(Qt::AlignCenter);
        count_->setText("0");
        buttonLayout->addWidget(count_);

        QObject::connect(addButton_, SIGNAL(clicked()), this, SLOT(addNode()));
        QObject::connect(deleteButton_, SIGNAL(clicked(bool)), this, SLOT(deleteNode()));
        QObject::connect(searchButton_, SIGNAL(clicked(bool)), this, SLOT(searchNode()));
        QObject::connect(scene_, SIGNAL(View::CustomScene::trysignal), this, SLOT(deleteClicked()));
        QObject::connect(inOrderButton_, SIGNAL(clicked()), this, SLOT(inOrder()));
        QObject::connect(preOrderButton_, SIGNAL(clicked(bool)), this, SLOT(preOrder()));
        QObject::connect(postOrderButton_, SIGNAL(clicked(bool)), this, SLOT(postOrder()));
    }

    void View::drawTree(Info* treeInfo, AVLTree::Operation& operation, int passing)
    {
        scene_->clear();
        scene_->setBackgroundBrush(Qt::white);
        Info* root = treeInfo;
        if (root == nullptr)
            return;
        std::queue<Info*> que;
        que.push(root);
        Info* cur;
        int count = 1;
        while (!que.empty()) {
            cur = que.front();
            que.pop();

            QBrush redbrush(Qt::red);
            QPen blackpen(Qt::black);
            blackpen.setWidth(3);
            QPen bluepen(Qt::blue);
            bluepen.setWidth(3);

            if(operation == AVLTree::Search && cur->key == passing || operation == AVLTree::Traversal && cur->key == passing)
                QGraphicsEllipseItem* ellipse = scene_->addEllipse(cur->x,cur->y,RADIUS,RADIUS,bluepen, redbrush);
            else
                QGraphicsEllipseItem* ellipse = scene_->addEllipse(cur->x,cur->y,RADIUS,RADIUS,blackpen, redbrush);

            QGraphicsTextItem *text = scene_->addText(QString::number(cur->key));
            text->setPos(cur->x + 10, cur->y + 10);

            if (cur->left != nullptr) {
                que.push(cur->left);
                scene_->addLine(cur->x + 10, cur->y + 35, cur->left->x + 20, cur->left->y + 5);
                ++count;
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
                scene_->addLine(cur->x + 30, cur->y + 35, cur->right->x + 10, cur->right->y + 5);
                ++count;
            }
        }
        count_->setText(QString::number(count));
    }

    void delay(int millisecondsWait)
    {
        QEventLoop loop;
        QTimer t;
        t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
        t.start(millisecondsWait);
        loop.exec();
    }

    void View::drawPrep(const AVLTree::Data &data) {
        if(data.message == 1)
        {
            QMessageBox msgBox;
            msgBox.setText("already present");
            msgBox.exec();
        }
        if(data.message == 2)
        {
            QMessageBox msgBox;
            msgBox.setText("not present");
            msgBox.exec();
        }
        const Node *node = data.value;
        if (node == nullptr) {
            scene_->clear();
            return;
        }
        if(treeInfo_ != nullptr)
            delete treeInfo_;
        treeInfo_ = new InfoTree(node);
        if(treeInfo_) {
            delay(750);
            drawTree(treeInfo_->getRoot(), data.operation, data.passing_);
        }
    }

    void View::deleteClicked(QPointF& point) {
        std::pair<int, bool> temp = treeInfo_->findValue(point.x(), point.y());
        if(!temp.second)
            return;
        editText_->setText(QString::number(temp.first));
    }

    void View::addNode() {
        operation_ = Operation::Add;
        if(editText_->text().size() == 0)
            return;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::deleteNode() {
        operation_ = Operation::Delete;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::searchNode() {
        operation_ = Operation::Search;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::inOrder(){
        operation_ = Operation::Traversal;
        type_ = Type::InOrder;
        commandPort.notify();
    }
    void View::preOrder(){
        operation_ = Operation::Traversal;
        type_ = Type::PreOrder;
        commandPort.notify();
    }
    void View::postOrder(){
        operation_ = Operation::Traversal;
        type_ = Type::PostOrder;
        commandPort.notify();
    }

    void View::CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
        QPointF pos = event->scenePos();
        ptr->deleteClicked(pos);
    }
}

