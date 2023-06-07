#include "aboutwindow.h"
#include "ui_AboutWindow.h"

namespace mvc {
    AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AboutWindow) {
        ui->setupUi(this);
        QTextEdit* text = new QTextEdit(this);
        text->setText("All people, who are trying to study programming languages, sooner or later understand that they need to get familiar with tree data structures. However, it can be a complicated task to capture how complex data structures work, especially when person encounters them for a first time. Visualization is a useful tool, which can make study of data structures more comprehensive.\n"
                      "This application presents the work of AVL Tree - a self-balancing Binary Search Tree, which offers O(log(n)) complexity of search, insertion and deletion operations, where n is the number of nodes. This efficient data structure was proposed in 1968 by two Soviet mathematicians Georgy Maximovich Adelson-Velsky and Evgenii Mikhailovich Landis. Because of self-balancing and almost never degenerative structure, AVL Tree offers effective way to store data. To elaborate on what AVL tree is its features should be mentioned:\n"
                      "1) Key in the node is smaller that any key in the right subtree and greater than any key in the left subtree (feature of a Binary Search Tree).\n"
                      "2) Difference between heights of right and left subtrees(also known as balance factor) is either -1, 0 or 1.");
        QLabel* labelIns = new QLabel("Insertion algorithm", this);
        QTextEdit* textIns = new QTextEdit(this);
        textIns->setText("Let the newly inserted node be w \n"
                         "\n"
                         "Perform standard BST insert for w. \n"
                         "Starting from w, travel up and find the first unbalanced node. Let z be the first unbalanced node, y be the child of z that comes on the path from w to z and x be the grandchild of z that comes on the path from w to z. \n"
                         "Re-balance the tree by performing appropriate rotations on the subtree rooted with z. There can be 4 possible cases that need to be handled as x, y and z can be arranged in 4 ways.\n"
                         "Following are the possible 4 arrangements: \n"
                         "y is the left child of z and x is the left child of y (Left Left Case) \n"
                         "y is the left child of z and x is the right child of y (Left Right Case) \n"
                         "y is the right child of z and x is the right child of y (Right Right Case) \n"
                         "y is the right child of z and x is the left child of y (Right Left Case)\n"
                         "1. Left Left Case \n"
                         "\n"
                         "T1, T2, T3 and T4 are subtrees.\n"
                         "         z                                      y \n"
                         "        / \\                                   /   \\\n"
                         "       y   T4      Right Rotate (z)          x      z\n"
                         "      / \\          - - - - - - - - ->      /  \\    /  \\ \n"
                         "     x   T3                               T1  T2  T3  T4\n"
                         "    / \\\n"
                         "  T1   T2\n"
                         "2. Left Right Case \n"
                         "\n"
                         "     z                               z                           x\n"
                         "    / \\                            /   \\                        /  \\ \n"
                         "   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z\n"
                         "  / \\      - - - - - - - - ->    /  \\      - - - - - - - ->  / \\    / \\\n"
                         "T1   x                          y    T3                    T1  T2 T3  T4\n"
                         "    / \\                        / \\\n"
                         "  T2   T3                    T1   T2\n"
                         "3. Right Right Case \n"
                         "\n"
                         "  z                                y\n"
                         " /  \\                            /   \\ \n"
                         "T1   y     Left Rotate(z)       z      x\n"
                         "    /  \\   - - - - - - - ->    / \\    / \\\n"
                         "   T2   x                     T1  T2 T3  T4\n"
                         "       / \\\n"
                         "     T3  T4\n"
                         "4. Right Left Case \n"
                         "\n"
                         "   z                            z                            x\n"
                         "  / \\                          / \\                          /  \\ \n"
                         "T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y\n"
                         "    / \\  - - - - - - - - ->     /  \\   - - - - - - - ->  / \\    / \\\n"
                         "   x   T4                      T2   y                  T1  T2  T3  T4\n"
                         "  / \\                              /  \\\n"
                         "T2   T3                           T3   T4");
        QLabel* del = new QLabel("Deletion algorithm", this);
        QTextEdit* textDel = new QTextEdit(this);
        textDel->setText("Let w be the node to be deleted \n"
                         "\n"
                         "Perform standard BST delete for w. \n"
                         "Starting from w, travel up and find the first unbalanced node. Let z be the first unbalanced node, y be the larger height child of z, and x be the larger height child of y. Note that the definitions of x and y are different from insertion here. \n"
                         "Re-balance the tree by performing appropriate rotations on the subtree rooted with z. There can be 4 possible cases that needs to be handled as x, y and z can be arranged in 4 ways. Following are the possible 4 arrangements: \n"
                         "y is left child of z and x is left child of y (Left Left Case) \n"
                         "y is left child of z and x is right child of y (Left Right Case) \n"
                         "y is right child of z and x is right child of y (Right Right Case) \n"
                         "y is right child of z and x is left child of y (Right Left Case)\n"
                         "a) Left Left Case \n"
                         "\n"
                         "T1, T2, T3 and T4 are subtrees.\n"
                         "         z                                      y \n"
                         "        / \\                                   /   \\\n"
                         "       y   T4      Right Rotate (z)          x      z\n"
                         "      / \\          - - - - - - - - ->      /  \\    /  \\ \n"
                         "     x   T3                               T1  T2  T3  T4\n"
                         "    / \\\n"
                         "  T1   T2\n"
                         "b) Left Right Case \n"
                         "\n"
                         "     z                               z                           x\n"
                         "    / \\                            /   \\                        /  \\ \n"
                         "   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z\n"
                         "  / \\      - - - - - - - - ->    /  \\      - - - - - - - ->  / \\    / \\\n"
                         "T1   x                          y    T3                    T1  T2 T3  T4\n"
                         "    / \\                        / \\\n"
                         "  T2   T3                    T1   T2\n"
                         "c) Right Right Case \n"
                         "\n"
                         "  z                                y\n"
                         " /  \\                            /   \\ \n"
                         "T1   y     Left Rotate(z)       z      x\n"
                         "    /  \\   - - - - - - - ->    / \\    / \\\n"
                         "   T2   x                     T1  T2 T3  T4\n"
                         "       / \\\n"
                         "     T3  T4\n"
                         "d) Right Left Case \n"
                         "\n"
                         "   z                            z                            x\n"
                         "  / \\                          / \\                          /  \\ \n"
                         "T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y\n"
                         "    / \\  - - - - - - - - ->     /  \\   - - - - - - - ->  / \\    / \\\n"
                         "   x   T4                      T2   y                  T1  T2  T3  T4\n"
                         "  / \\                              /  \\\n"
                         "T2   T3                           T3   T4\n"
                         "Unlike insertion, in deletion, after we perform a rotation at z, we may have to perform a rotation at ancestors of z. Thus, we must continue to trace the path until we reach the root.");
        text->setReadOnly(true);
        textDel->setReadOnly(true);
        textIns->setReadOnly(true);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(text);
        layout->addWidget(labelIns);
        layout->addWidget(textIns);
        layout->addWidget(del);
        layout->addWidget(textDel);
    }

    AboutWindow::~AboutWindow() {
        delete ui;
    }
}
