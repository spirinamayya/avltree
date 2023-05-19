#ifndef COURSEPROJECT_MODEL_H
#define COURSEPROJECT_MODEL_H

#include "/Users/mayyaspirina/Documents/CourseProject/Observer/Observer.h"
#include <iostream>
#include <vector>

namespace mvc {
    struct Node {
        int key;
        int height = 1;
        Node *leftCh = nullptr;
        Node *rightCh = nullptr;
    };

    class AVLTree {
    public:
        AVLTree()
            : root_(nullptr){}
        ~AVLTree();

        AVLTree(const AVLTree&) = delete;
        AVLTree(AVLTree&&) noexcept = delete;
        AVLTree& operator=(const AVLTree&) = delete;
        AVLTree& operator=(AVLTree&&) noexcept = delete;

        void insert(int key);
        void deleteNode(int key);
        void search(int key);
        void inOrder();
        void preOrder();
        void postOrder();

    private:
        void clearHelp(Node *&treeptr);

        Node *leftRotate(Node *node);
        Node *rightRotate(Node *node);
        int findBalanceFactor(Node *node);
        static int getHeight(const Node* node);
        int findMaxHeight(const Node *left, const Node *right);
        Node* balanceInsert(Node* node, int key);
        Node* insert(Node *node, int key);

        Node* balanceDelete(Node* node);
        Node *inorderSuccessor(Node *x);
        void twoChildren(Node* node);
        Node* oneZeroChildren(Node* node);
        Node *deleteNode(Node *node, int key);

        void search(Node* node, int key, int& repeat);

        void inOrderTraversal(Node* node);
        void preOrderTraversal(Node* node);
        void postOrderTraversal(Node* node);
    public:
        enum Operation{
            Add, Delete, Search, Traversal
        };
        struct Data {
            Node*& value;
            int& message;
            Operation& operation;
            int& passing_;
        };
    private:
        using Observer = NSLibrary::CObserver<Data>;
        using Observable = NSLibrary::CObservableData<Data>;

    public:
        void subscribe(Observer *observer) {
            assert(observer);
            port_.subscribe(observer);
        }

    private:
        Node *root_ = nullptr;
        int message_ = 0;
        Operation operation_;
        int passing_;
        Observable port_ = Data{root_, message_, operation_, passing_};
    };
}

#endif//COURSEPROJECT_MODEL_H
