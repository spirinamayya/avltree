#include "aboutwindow.h"
#include "ui_AboutWindow.h"

namespace mvc {
    AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AboutWindow) {
        ui->setupUi(this);
        this->setFixedSize(500, 570);
        QTextEdit *text = new QTextEdit(this);
        text->setText("All people, who are trying to study programming languages, sooner or later understand that they need to get familiar with tree data structures. However, it can be a complicated task to capture how complex data structures work, especially when person encounters them for a first time. Visualization is a useful tool, which can make study of data structures more comprehensive.\n"
                      "This application presents the work of AVL Tree - a self-balancing Binary Search Tree, which offers O(log(n)) complexity of search, insertion and deletion operations, where n is the number of nodes. This efficient data structure was proposed in 1968 by two Soviet mathematicians Georgy Maximovich Adelson-Velsky and Evgenii Mikhailovich Landis. Because of self-balancing and almost never degenerative structure, AVL Tree offers effective way to store data. To elaborate on what AVL tree is its features should be mentioned:\n"
                      "1) Key in the node is smaller that any key in the right subtree and greater than any key in the left subtree (feature of a Binary Search Tree).\n"
                      "2) Difference between heights of right and left subtrees(also known as balance factor) is either -1, 0 or 1.");
        QLabel *labelIns = new QLabel("Insertion algorithm", this);
        QTextEdit *textIns = new QTextEdit(this);
        textIns->setText("Insert node A in the manner similar to insertion in BST, that is to the leaf node. \n"
                         "\n"
                         "Go to the parent of A and find first node, which is unbalanced. Balance the tree, performing following operations. (Operation type depends on where child and grandchild of unbalanced node are located).\n"
                         "Important to mention that child and grandchild should be on the way from inserted node. Let's denote x, as inserted node, y as its child, z as grandchild\n"
                         "Let's discuss how nodes can be located with respect to each other. \n"

                         "1. Left Left Case (This operation will be called right rotation)\n"
                         "Initial:\n"
                         "X: y left child; Y: z left child\n"
                         "New:\n"
                         "Y: z left child, x right child\n"
                         "\n"

                         "2. Right Right Case (This operation will be called right rotation)\n"
                         "Initial:\n"
                         "X: y right child; Y: z right child\n"
                         "New:\n"
                         "Y: z right child, x left child\n"
                         "\n"

                         "3. Left Right Case\n"
                         "Initial:\n"
                         "X: y left child; Y: z right child\n"
                         "New:\n"
                         "Z: y left child, x right child (first apply left rotate to y, after that apply right rotate to x)\n"
                         "\n"

                         "4. Right Left Case \n"
                         "Initial:\n"
                         "X: y right child; Y: z left child\n"
                         "New:\n"
                         "Z: y right child, x left child (first apply right rotate to y, after that apply left rotate to x)\n"
                         "\n");

        QLabel *del = new QLabel("Deletion algorithm", this);
        QTextEdit *textDel = new QTextEdit(this);
        textDel->setText("Delete node A in the manner similar to the deletion from BST, in the csse of this application find inorder successor, change it with node and perform standard deletion.\n"
                         "\n"
                         "Go to the parent of A and find first node, which is unbalanced. Balance the tree, performing following operations. (Operation type depends on where child and grandchild of unbalanced node are located).\n"
                         "Difference from insertion operation is that in this case child and grandchild from the subtree with a greatest height should be considered. \n"
                         "1. Left Left Case \n"
                         "Initial:\n"
                         "X: y left child; Y: z left child\n"
                         "New:\n"
                         "Y: z left child, x right child (apply right rotate to x)\n"
                         "\n"

                         "2. Right Right Case \n"
                         "Initial:\n"
                         "X: y right child; Y: z right child\n"
                         "New:\n"
                         "Y: z right child, x left child (apply left rotate to x)\n"
                         "\n"


                         "3. Left Right Case \n"
                         "Initial:\n"
                         "X: y left child; Y: z right child\n"
                         "New:\n"
                         "Z: y left child, x right child (first apply left rotate to y, after that apply right rotate to x)\n"
                         "\n"

                         "4. Right Left Case \n"
                         "Initial:\n"
                         "X: y right child; Y: z left child\n"
                         "New:\n"
                         "Z: y right child, x left child (first apply right rotate to y, after that apply left rotate to x)\n"
                         "Operations should be repeated until root node is reached.\n"
                         "Information is taken from https://www.geeksforgeeks.org/introduction-to-avl-tree/");
        text->setReadOnly(true);
        textDel->setReadOnly(true);
        textIns->setReadOnly(true);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(text);
        layout->addWidget(labelIns);
        layout->addWidget(textIns);
        layout->addWidget(del);
        layout->addWidget(textDel);
    }

    AboutWindow::~AboutWindow() {
        delete ui;
    }
}// namespace mvc
