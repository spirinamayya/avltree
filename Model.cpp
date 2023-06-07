#include "Model.h"

namespace mvc {

    AVLTree::~AVLTree() {
        clearHelp(root_);
    }

    void AVLTree::insert(int key) {
        operation_ = Add;
        root_ = insert(root_, key);
        if (root_ == nullptr)
            return;
        port_.notify();
    }

    void AVLTree::deleteNode(int key) {
        operation_ = Delete;
        root_ = deleteNode(root_, key);
        port_.notify();
    }

    void AVLTree::search(int key) {
        operation_ = Search;
        message_ = Fine;
        search(root_, key, message_);
        if(message_ == 2)
            operation_ = Add;
        port_.notify();
    }

    void AVLTree::deleteAll(){
        clearHelp(root_);
        operation_ = DeleteAll;
        port_.notify();
    }

    void AVLTree::clearHelp(Node *&node) {
        if (node != nullptr) {
            clearHelp(node->leftCh);
            clearHelp(node->rightCh);
            delete node;
            node = nullptr;
        }
    }

    Node *AVLTree::leftRotate(Node *node) {
        Node *rCh = node->rightCh;
        Node *lGrCh = node->rightCh->leftCh;
        node->rightCh->leftCh = node;
        node->rightCh = lGrCh;
        node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;
        rCh->height = findMaxHeight(rCh->leftCh, rCh->rightCh) + 1;
        return rCh;
    }

    Node *AVLTree::rightRotate(Node *node) {
        Node *lCh = node->leftCh;
        Node *rGrCh = node->leftCh->rightCh;
        node->leftCh->rightCh = node;
        node->leftCh = rGrCh;
        node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;
        lCh->height = findMaxHeight(lCh->leftCh, lCh->rightCh) + 1;
        return lCh;
    }

    int AVLTree::findBalanceFactor(Node *node) {
        int l = 0, r = 0;
        if (node == nullptr)
            return 0;
        if (node->leftCh != nullptr)
            l = node->leftCh->height;
        if (node->rightCh != nullptr)
            r = node->rightCh->height;
        return l - r;
    }

    int AVLTree::getHeight(const Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int AVLTree::findMaxHeight(const Node *left, const Node *right) {
        return std::max(getHeight(left), getHeight(right));
    }

    Node* AVLTree::balanceInsert(Node* node, int key)
    {
        node->height = findMaxHeight(node->leftCh, node->rightCh) + 1;
        int balanceFactor = findBalanceFactor(node);

        if (balanceFactor > 1 && key < node->leftCh->key) {
            //port_.notify();
            return rightRotate(node);
        }
        if (balanceFactor > 1 && key > node->leftCh->key) {
            //port_.notify();
            node->leftCh = leftRotate(node->leftCh);
            //port_.notify();
            return rightRotate(node);
        }
        if (balanceFactor < -1 && key > node->rightCh->key) {
            //port_.notify();
            return leftRotate(node);
        }
        if (balanceFactor < -1 && key < node->rightCh->key) {
            //port_.notify();
            node->rightCh = rightRotate(node->rightCh);
            //port_.notify();
            return leftRotate(node);
        }
        return node;
    }

    Node* AVLTree::insert(Node *node, int key) {
        if (node == nullptr) {
            message_ = Fine;
            return new Node{key};
        }
        if (key < node->key)
            node->leftCh = insert(node->leftCh, key);
        else if (key > node->key)
            node->rightCh = insert(node->rightCh, key);
        else {
            message_ = AlreadyPresent;
            return node;
        }
        return balanceInsert(node, key);
    }

    Node* AVLTree::balanceDelete(Node *node) {
        if (node == nullptr)
            return node;
        node->height = findMaxHeight(node->rightCh, node->leftCh) + 1;
        int balanceFactor = findBalanceFactor(node);
        if (balanceFactor > 1 && findBalanceFactor(node->leftCh) >= 0) {
            port_.notify();
            return rightRotate(node);
        }
        if (balanceFactor > 1 && findBalanceFactor(node->leftCh) < 0) {
            port_.notify();
            node->leftCh = leftRotate(node->leftCh);
            port_.notify();
            return rightRotate(node);
        }
        if (balanceFactor < -1 && findBalanceFactor(node->rightCh) < 0) {
            port_.notify();
            return leftRotate(node);
        }
        if (balanceFactor < -1 && findBalanceFactor(node->rightCh) >= 0) {
            port_.notify();
            node->rightCh = rightRotate(node->rightCh);
            port_.notify();
            return leftRotate(node);
        }
        return node;
    }

    Node *AVLTree::inorderSuccessor(Node *x) {
        Node *cur = x->rightCh;
        while (cur->leftCh != nullptr)
            cur = cur->leftCh;
        return cur;
    }

    void AVLTree::deleteNodeTwoChildren(Node* node)
    {
        Node* cur = AVLTree::inorderSuccessor(node);
        node->key = cur->key;
        port_.notify();
        node->rightCh = deleteNode(node->rightCh, cur->key);
    }

    Node* AVLTree::deleteNodeOneZeroChildren(Node* node)
    {
        Node *cur = nullptr;
        if (node->leftCh)
            cur = node->leftCh;
        if (node->rightCh)
            cur = node->rightCh;
        if (cur == nullptr) {
            cur = node;
            node = nullptr;
        }
        else
            *node = *cur;
        port_.notify();
        delete cur;
        return node;
    }

    Node* AVLTree::deleteNode(Node *node, int key)
    {
        if(node == nullptr) {
            message_ = NotPresent;
            return node;
        }
        if(key < node->key)
            node->leftCh = deleteNode(node->leftCh, key);
        else if(key > node->key)
            node->rightCh = deleteNode(node->rightCh, key);
        else
        {
            message_ = Fine;
            if(node->leftCh == nullptr || node->rightCh == nullptr)
                node = deleteNodeOneZeroChildren(node);
            else
                deleteNodeTwoChildren(node);
        }
        return balanceDelete(node);
    }

    void AVLTree::search(Node *node, int key, Message& message)
    {
        while(node != nullptr)
        {
            if(node->key < key) {
                passing_ = node->key;
                port_.notify();
                node = node->rightCh;
            }
            else if(node->key > key) {
                passing_ = node->key;
                port_.notify();
                node = node->leftCh;
            }
            else{
                passing_ = key;
                port_.notify();
                return;
            }
        }
        message = NotPresent;
    }

}
