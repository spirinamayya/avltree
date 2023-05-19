#include "InfoTree.h"

namespace mvc {
    InfoTree::~InfoTree() {
        clear(root_);
    }

    std::pair<int, bool> InfoTree::findValue(int x, int y) {
        if(this == nullptr)
            return {0, false};
        std::queue<Info *> que;
        que.push(root_);
        Info *cur;
        while (!que.empty()) {
            cur = que.front();
            que.pop();
            if((x > cur->x - RADIUS && x < cur->x + RADIUS) && (y > cur->y - RADIUS && y < cur->y + RADIUS))
                return {cur->key, true};
            if (cur->left != nullptr)
                que.push(cur->left);
            if (cur->right != nullptr)
                que.push(cur->right);
        }
        return {0, false};
    }

    void InfoTree::clear(Info *treeInfo) {
        if (treeInfo != nullptr) {
            clear(treeInfo->left);
            clear(treeInfo->right);
            delete treeInfo;
        }
    }

    void InfoTree::setWidth(Info *cur) {
        if (cur == nullptr)
            return;
        setWidth(cur->left);
        setWidth(cur->right);

        if (cur->right == nullptr && cur->left == nullptr)
            cur->width = 2 * RADIUS;
        else if (cur->left == nullptr)
            cur->width = 2 * cur->right->width + WIDTH;
        else if (cur->right == nullptr)
            cur->width = 2 * cur->left->width + WIDTH;
        else
            cur->width = cur->left->width + cur->right->width + WIDTH;
    }

    void InfoTree::calcXCoord() {
        Info *coord = root_;
        setWidth(coord);
        Info *root = root_;
        if (root == nullptr)
            return;
        std::queue<Info *> que;
        que.push(root);
        Info *cur;
        int count = 0, timesNow = 1, timesNext = 0;
        while (!que.empty()) {
            cur = que.front();
            que.pop();
            if (cur->left != nullptr) {
                que.push(cur->left);
                ++timesNext;
                cur->left->x = cur->x - WIDTH / 2 - cur->left->width / 2;
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
                ++timesNext;
                cur->right->x = cur->x + WIDTH / 2 + cur->right->width / 2;
            }
            --timesNow;
            if (timesNow == 0) {
                ++count;
                timesNow = timesNext;
                timesNext = 0;
            }
        }
    }

    Info *InfoTree::copy(const Node *node) {
        if (node == nullptr)
            return nullptr;
        else {
            Info *temp = new Info;
            temp->key = node->key;
            temp->left = copy(node->leftCh);
            temp->right = copy(node->rightCh);
            return temp;
        }
    }

    void InfoTree::calcYCoord(const Node *rootGet) {
        root_ = copy(rootGet);
        Info *root = root_;
        if (root == nullptr)
            return;
        std::queue<Info *> que;
        que.push(root);
        Info *cur;
        int count = 0, timesNow = 1, timesNext = 0;
        while (!que.empty()) {
            cur = que.front();
            que.pop();
            cur->y = count * (2 * RADIUS + HEIGHT);
            if (cur->left != nullptr) {
                que.push(cur->left);
                ++timesNext;
            }
            if (cur->right != nullptr) {
                que.push(cur->right);
                ++timesNext;
            }
            --timesNow;
            if (timesNow == 0) {
                ++count;
                timesNow = timesNext;
                timesNext = 0;
            }
        }
    }
}
