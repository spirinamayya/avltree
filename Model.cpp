#include "Model.h"

int AVLTree::findMaxHeight(Node* left, Node* right)
{
    int l = 0, r = 0;
    if(left != nullptr)
        l = left->height;
    if(right != nullptr)
        r = right->height;
    return std::max(l, r);
}

int AVLTree::findBalanceFactor(Node* node)
{
    int l = 0, r = 0;
    if(node == nullptr)
        return 0;
    if(node->leftCh != nullptr)
        l = node->leftCh->height;
    if(node->rightCh != nullptr)
        r = node->rightCh->height;
    return l - r;
}

Node* AVLTree::rightRotate(Node* node)
{
    Node* lCh = node->leftCh;
    Node* rGrCh = node->leftCh->rightCh;
    node->leftCh->rightCh = node;
    node->leftCh = rGrCh;
    node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;
    lCh->height = findMaxHeight(lCh->leftCh, lCh->rightCh) + 1;
    return lCh;
}
Node* AVLTree::leftRotate(Node *node)
{
    Node* rCh = node->rightCh;
    Node* lGrCh = node->rightCh->leftCh;
    node->rightCh->leftCh = node;
    node->rightCh = lGrCh;
    node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;
    rCh->height = findMaxHeight(rCh->leftCh, rCh->rightCh) + 1;
    return rCh;
}


Node* AVLTree::insert(Node* node, int key)
{
    ///find leaf node, where to insert newNode
    if(node == nullptr)
        return new Node(key);
    if(key < node->key)
        node->leftCh = insert(node->leftCh, key);
    else if(key > node->key)
        node->rightCh = insert(node->rightCh, key);
    else
        return node;

    ///update height of ancestor
    node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;

    ///find balance factor
    int balanceFactor = findBalanceFactor(node);

    ///check whether tree is unbalanced and balance it
    if(balanceFactor > 1 && key < node->leftCh->key)
        return rightRotate(node);
    if(balanceFactor > 1 && key > node->leftCh->key)
    {
        node->leftCh = leftRotate(node->leftCh);
        return rightRotate(node);
    }
    if(balanceFactor < -1 && key > node->rightCh->key)
        return leftRotate(node);
    if(balanceFactor < -1 && key < node->rightCh->key)
    {
        node->rightCh = rightRotate(node->rightCh);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::insert(int key)
{
    int t = 1;
    root_ = insert(root_, key);

    if(root_== nullptr)
        return;
    insertPort.notify();
}

Node* AVLTree::inorderSuccessor(Node* x)
{
    Node* cur = x->rightCh;
    while(cur->leftCh != nullptr)
        cur = cur->leftCh;
    return cur;
}

Node* AVLTree::deleteNode(Node *node, int key)
{
    ///findNode, which should be deleted, and delete it
    if(node == nullptr)
        return node;
    if(key < node->key)
        node->leftCh = deleteNode(node->leftCh, key);
    else if(key > node->key)
        node->rightCh = deleteNode(node->rightCh, key);
    else
    {
        ///one or zero children
        if(node->leftCh == nullptr || node->rightCh == nullptr)
        {
            Node* cur = nullptr;
            if(node->leftCh)
                cur = node->leftCh;
            if(node->rightCh)
                cur = node->rightCh;
            if(cur == nullptr)
            {
                cur = node;
                node = nullptr;
            }
            else
                *node = *cur;
            delete cur;
        }
            ///two children
        else
        {
            Node* cur = AVLTree::inorderSuccessor(node);
            node->key = cur->key;
            node->rightCh = deleteNode(node->rightCh, cur->key);
        }
    }

    if(node == nullptr)
        return node;
    ///update height of the node
    node->height = findMaxHeight(node->rightCh, node->leftCh) + 1;

    ///find balance factor
    int balanceFactor = findBalanceFactor(node);
    ///check whether tree is unbalanced and balance it
    if(balanceFactor > 1 && findBalanceFactor(node->leftCh) >= 0)
        return rightRotate(node);
    if(balanceFactor > 1 && findBalanceFactor(node->leftCh) < 0)
    {
        node->leftCh = leftRotate(node->leftCh);
        return rightRotate(node);
    }
    if(balanceFactor < -1 && findBalanceFactor(node->rightCh) < 0)
        return leftRotate(node);
    if(balanceFactor < -1 && findBalanceFactor(node->rightCh) >= 0)
    {
        node->rightCh = rightRotate(node->rightCh);
        return leftRotate(node);
    }
    return node;
}

void AVLTree::deleteNode(int key)
{
    root_ = deleteNode(root_, key);
    insertPort.notify();
}

void AVLTree::clearHelp(Node*& node)
{
    if (node != nullptr)
    {
        clearHelp(node->leftCh);
        clearHelp(node->rightCh);
        delete node;
        node = nullptr;
    }
}
AVLTree::~AVLTree()
{
    clearHelp(root_);
}

//Node* AVLTree::search(Node *node, int key)
//{
//    if(node == nullptr)
//        return node;
//    if(key < node->key)
//        node->leftCh = search(node->leftCh, key);
//    else if(key > node->key)
//        node->rightCh = search(node->rightCh, key);
//    else
//        return node;
//}

//Node* AVLTree::search(int key)
//{
//    return search(_root, key);
//}

//void AVLTree::levelPrint(Node* root)
//{
//    if (!root)
//        return;
//    std::queue<Node*> q;
//    q.push(root);

//    while (!q.empty())
//    {
//        Node* cur = q.front();
//        q.pop();
//            std::cout << cur->key <<"\n";
//        if (cur->leftCh)
//            q.push(cur->leftCh);
//        if (cur->rightCh)
//            q.push(cur->rightCh);
//    }
//}