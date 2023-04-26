#ifndef COURSEPROJECT_MODEL_H
#define COURSEPROJECT_MODEL_H

#include <iostream>
#include <vector>
#include "/Users/mayyaspirina/Documents/CourseProject/Observer/Observer.h"

class Node{
public:

    Node(){}
    Node(int key)
            : key(key), height(1), rightCh(nullptr), leftCh(nullptr)
    {}
    int key;
    int height;
    Node* leftCh;
    Node* rightCh;
};

class AVLTree{
public:
    AVLTree()
    : root_(nullptr)
    {}

    void clearHelp(Node*& treeptr);
    ~AVLTree();

    void insert(int key);
    int findMaxHeight(Node* left, Node* right);
    int findBalanceFactor(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    Node* insert(Node* node, int key);

    Node* inorderSuccessor(Node* x);
    void deleteNode(int key);
    Node* deleteNode(Node* node, int key);
    void levelPrint(Node* root);

    Node* search(int key);
    Node* search(Node* node, int key);


    struct ModAddData{
        std::reference_wrapper<Node* const> Value;
    };
    void subscribe(NSLibrary::CObserver<ModAddData>* observer)
    {
        assert(observer);
        insertPort.subscribe(observer);
    }
private:

//    std::vector<Node*> root_;
    Node* root_ = nullptr;
    int Value;
    NSLibrary::CObservableData<ModAddData> insertPort = ModAddData{std::cref(root_)};
};


#endif //COURSEPROJECT_MODEL_H
