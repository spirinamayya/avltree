#include "View.h"

#include <chrono>

namespace mvc {

    View::View()
    {
        mainWindow_ = new MainWindow();
        addMenu();
        addControlPannel();
        adjustMainWindow();
        connectObjects();
        mainWindow_->setWindowTitle("AVL tree");

        QFile file("/Users/mayyaspirina/Downloads/pumpum-addTree/stylesheet.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());
        mainWindow_->setStyleSheet(styleSheet);

        mainWindow_->show();
    }

    void View::addMenu(){
        QMenuBar* menu = new QMenuBar(mainWindow_);
        QMenu* about = new QMenu("About", mainWindow_);
        QMenu* load = new QMenu("Load", mainWindow_);
        QAction* act = new QAction(about);
        QAction* actLoad = new QAction(load);
        act->setText("Info");
        actLoad->setText("Load");
        about->addAction(act);
        about->addAction(actLoad);
        menu->addMenu(about);
        QObject::connect(act, &QAction::triggered, this, &View::aboutMenu);
        QObject::connect(actLoad, &QAction::triggered, this, &View::loadMenu);
    }

    void View::addControlPannel() {
        addButton_ = new QPushButton("Add node", mainWindow_);
        deleteButton_ = new QPushButton("Delete node", mainWindow_);
        searchButton_ = new QPushButton("Search node", mainWindow_);

        inOrderButton_ = new QPushButton("Inorder traversal", mainWindow_);
        preOrderButton_ = new QPushButton("Preorder traversal", mainWindow_);
        postOrderButton_ = new QPushButton("Postorder traversal", mainWindow_);

        stepBackButton_ = new QPushButton("Step back", mainWindow_);

        QValidator *validator = new QIntValidator(mainWindow_);
        editText_ = new QLineEdit(mainWindow_);
        editText_->setValidator(validator);

        treeSpot_ = new QGraphicsView(mainWindow_);
        scene_ = new CustomScene(this);
        scene_->setBackgroundBrush(Qt::white);
        treeSpot_->setScene(scene_);

        slider_ = new QSlider(Qt::Horizontal, mainWindow_);
        slider_->setTickInterval(50);
        slider_->setMinimum(250);
        slider_->setMaximum(1250);
    }

    void View::adjustMainWindow() {
        QHBoxLayout* layout = new QHBoxLayout(mainWindow_);

        QGroupBox* box = new QGroupBox(mainWindow_);
        QVBoxLayout* buttonLayout = new QVBoxLayout(box);
        layout->addWidget(treeSpot_, 75);
        layout->addWidget(box, 25);
        buttonLayout->setSpacing(15);
        buttonLayout->setAlignment(Qt::AlignTop);

        QLabel* header1 = new QLabel(mainWindow_);
        header1->setText(tr("Type integer:"));
        buttonLayout->addWidget(header1);
        buttonLayout->addWidget(editText_);
        buttonLayout->addWidget(addButton_);
        buttonLayout->addWidget(deleteButton_);
        buttonLayout->addWidget(searchButton_);

        QSpacerItem* spacer = new QSpacerItem(2, 70);
        buttonLayout->addSpacerItem(spacer);
        QLabel* header2 = new QLabel(mainWindow_);
        header2->setText(tr("Tree traversals:"));
        buttonLayout->addWidget(header2);
        buttonLayout->addWidget(inOrderButton_);
        buttonLayout->addWidget(preOrderButton_);
        buttonLayout->addWidget(postOrderButton_);

        buttonLayout->addSpacerItem(spacer);
        QLabel* header4= new QLabel(mainWindow_);
        header4->setText(tr("Speed:"));
        buttonLayout->addWidget(header4);
        buttonLayout->addWidget(slider_);
        buttonLayout->addWidget(stepBackButton_);

        buttonLayout->addSpacerItem(spacer);
        QLabel* header3 = new QLabel(mainWindow_);
        header3->setText(tr("Node count:"));
        buttonLayout->addWidget(header3);
        count_ = new QLineEdit(mainWindow_);
        count_->setReadOnly(true);
        count_->setFixedSize(50, 50);
        count_->setAlignment(Qt::AlignCenter);
        count_->setText("0");
        buttonLayout->addWidget(count_);
    }

    void View::connectObjects() {
        QObject::connect(addButton_, SIGNAL(clicked()), this, SLOT(addNode()));
        QObject::connect(deleteButton_, SIGNAL(clicked(bool)), this, SLOT(deleteNode()));
        QObject::connect(searchButton_, SIGNAL(clicked(bool)), this, SLOT(searchNode()));
        QObject::connect(inOrderButton_, SIGNAL(clicked()), this, SLOT(inOrder()));
        QObject::connect(preOrderButton_, SIGNAL(clicked(bool)), this, SLOT(preOrder()));
        QObject::connect(postOrderButton_, SIGNAL(clicked(bool)), this, SLOT(postOrder()));
        QObject::connect(stepBackButton_, SIGNAL(clicked(bool)), this, SLOT(stepBack()));
    }

    void View::drawNode(Info *cur, std::queue<Info *>& que, int &count, AVLTree::Operation& operation, int passing) {
        QBrush cyanbrush(Qt::darkCyan);
        QPen blackpen(Qt::black);
        blackpen.setWidth(1);
        QPen redpen(Qt::red);
        redpen.setWidth(3);

        if(operation == AVLTree::Search && cur->key == passing || operation == AVLTree::Traversal && cur->key == passing)
            scene_->addEllipse(cur->x,cur->y,kRadius_,kRadius_,redpen, cyanbrush);
        else
            scene_->addEllipse(cur->x,cur->y,kRadius_,kRadius_,blackpen, cyanbrush);

        QGraphicsTextItem *text = scene_->addText(QString::number(cur->key));
        text->setPos(cur->x + 10, cur->y + 10);

        if (cur->left != nullptr) {
            que.push(cur->left);
            scene_->addLine(cur->x + 10, cur->y + 37, cur->left->x + 29, cur->left->y + 3);
            ++count;
        }
        if (cur->right != nullptr) {
            que.push(cur->right);
            scene_->addLine(cur->x + 31, cur->y + 37, cur->right->x + 13, cur->right->y + 3);
            ++count;
        }
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
            drawNode(cur, que, count, operation, passing);
        }
        count_->setText(QString::number(count));
    }

    void delay(int millisecondsWait)
    {
        QTimer t;
        QEventLoop loop;
        t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
        t.start(millisecondsWait);
        loop.exec();
    }

    void View::draw(const AVLTree::Data &data) {
        if(data.operation == AVLTree::DeleteAll)
        {
            scene_->clear();
            treeInfo_.release();
            count_->setText("0");
        }
        if(!hist_){
            switch(data.message){
                case AVLTree::AlreadyPresent:
                {
                    if(load_)
                        return;
                    QMessageBox msgBox;
                    msgBox.setText("already present");
                    msgBox.exec();
                    return;
                }
                case AVLTree::NotPresent:
                {
                    if(load_)
                        return;
                    QMessageBox msgBox;
                    msgBox.setText("not present");
                    msgBox.exec();
                    return;
                }
                default:
                    break;
            }
        }
        if(history_.size() == 0)
            history_.push_back({value_, Operation::Add});
        else if(!hist_ && history_[history_.size() - 1] != std::make_pair(value_, operation_)) {
            if (data.operation == AVLTree::Operation::Add)
                history_.push_back({value_, Operation::Add});
            else if (data.operation == AVLTree::Operation::Delete)
                history_.push_back({value_, Operation::Delete});
        }
        const Node *node = data.value;
        if (node == nullptr) {
            scene_->clear();
            treeInfo_.release();
            count_->setText("0");
            return;
        }
        if(treeInfo_ != nullptr) {
            treeInfo_.release();
        }
        treeInfo_ = std::make_unique<InfoTree>(node);
        if(treeInfo_) {
            if(!load_ && !hist_)
                delay(speed_);
            drawTree(treeInfo_->getRoot(), data.operation, data.passing_);
        }
    }

    void View::deleteClicked(QPointF& point) {
        speed_ = slider_->value();
        std::pair<int, bool> temp = treeInfo_->findValue(point.x(), point.y());
        if(!temp.second)
            return;
        editText_->setText(QString::number(temp.first));
    }

    void View::inOrderTraversal(Info *node) {
        if(node == nullptr)
            return;
        inOrderTraversal(node->left);
        delay(slider_->value());
        AVLTree::Operation op = AVLTree::Operation::Traversal;
        drawTree(treeInfo_->getRoot(), op, node->key);
        inOrderTraversal(node->right);
    }

    void View::preOrderTraversal(Info *node) {
        if(node == nullptr)
            return;
        delay(slider_->value());
        AVLTree::Operation op = AVLTree::Operation::Traversal;
        drawTree(treeInfo_->getRoot(), op, node->key);
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }

    void View::postOrderTraversal(Info *node) {
        if(node == nullptr)
            return;
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        delay(slider_->value());
        AVLTree::Operation op = AVLTree::Operation::Traversal;
        drawTree(treeInfo_->getRoot(), op, node->key);
    }

    void View::getDataFromFile(QString& fileName) {
        QFile inputFile(fileName);
        inputFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream inputStream(&inputFile);
        QString key;
        operation_ = Operation::Add;
        while(!inputStream.atEnd())
        {

            QString line = inputStream.readLine();
            QList<QString> temp = line.split(" ");
            for (QString& item : temp) {
                bool convert;
                value_ = item.toInt(&convert);
                if(!convert)
                    continue;
                commandPort.notify();
            }
        }
        inputFile.close();
    }

    void View::addNode() {
        speed_ = slider_->value();
        operation_ = Operation::Add;
        if(editText_->text().size() == 0)
            return;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::deleteNode() {
        speed_ = slider_->value();
        operation_ = Operation::Delete;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::searchNode() {
        speed_ = slider_->value();
        operation_ = Operation::Search;
        value_ = editText_->text().toInt();
        editText_->clear();
        commandPort.notify();
    }

    void View::inOrder(){
        speed_ = slider_->value();
        if(treeInfo_ == nullptr)
            return;
        inOrderTraversal(treeInfo_->getRoot());
    }

    void View::preOrder(){
        speed_ = slider_->value();
        if(treeInfo_ == nullptr)
            return;
        preOrderTraversal(treeInfo_->getRoot());
    }

    void View::postOrder(){
        speed_ = slider_->value();
        if(treeInfo_ == nullptr)
            return;
        postOrderTraversal(treeInfo_->getRoot());
    }

    void View::aboutMenu() {
        secondWindow_ = std::make_unique<AboutWindow>();
        secondWindow_->setWindowTitle("Additional information");
        secondWindow_->show();
    }

    void View::loadMenu() {
        QString fileName = QFileDialog::getOpenFileName(mainWindow_, "Open File",
                                                        "../",
                                                        "Data (*.txt)");
        if(fileName.isEmpty())
            return;
        operation_ = Operation::DeleteAll;
        commandPort.notify();
        history_.clear();
        history_.push_back({0, Operation::Add});
        load_ = true;
        getDataFromFile(fileName);
        load_ = false;
    }

    void View::stepBack() {
        if(history_.size() == 1)
            return;
        hist_ = true;
        operation_ = Operation::DeleteAll;
        commandPort.notify();
        operation_ = Operation::Add;
        history_.pop_back();
        for(size_t i = 1; i < history_.size(); ++i)
        {
            value_ = history_[i].first;
            operation_ = history_[i].second;
            commandPort.notify();
        }
        if(history_.size() == 1) {
            scene_->clear();
            count_->setText("0");
        }
        hist_ = false;
    }

    void View::CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
        QPointF pos = event->scenePos();
        ptr->deleteClicked(pos);
    }
}

