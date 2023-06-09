#include "InfoTree.h"

namespace mvc {
    InfoTree::~InfoTree() {
        clear(root_);
    }

    std::pair<int, bool> InfoTree::findValue(int x, int y) {
        if (this == nullptr)
            return {0, false};
        std::queue<Info *> que;
        que.push(root_);
        Info *cur;
        while (!que.empty()) {
            cur = que.front();
            que.pop();
            if ((x > cur->x - kRadius_ && x < cur->x + kRadius_) && (y > cur->y - kRadius_ && y < cur->y + kRadius_))
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
            cur->width = 2 * kRadius_;
        else if (cur->left == nullptr)
            cur->width = 2 * cur->right->width + kWidth_;
        else if (cur->right == nullptr)
            cur->width = 2 * cur->left->width + kWidth_;
        else
            cur->width = 2 * std::max(cur->left->width, cur->right->width) + kWidth_;
    }

    void InfoTree::setXCoord(Info *cur, std::queue<Info *> &que, int &count, int &timesNext, int &timesNow) {
        if (cur->left != nullptr) {
            que.push(cur->left);
            ++timesNext;
            cur->left->x = cur->x - kWidth_ / 2 - cur->left->width / 2;
        }
        if (cur->right != nullptr) {
            que.push(cur->right);
            ++timesNext;
            cur->right->x = cur->x + kWidth_ / 2 + cur->right->width / 2;
        }
        --timesNow;
        if (timesNow == 0) {
            ++count;
            timesNow = timesNext;
            timesNext = 0;
        }
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
            setXCoord(cur, que, count, timesNext, timesNow);
        }
    }

    Info *InfoTree::buildInfoTree(const Node *node) {
        if (node == nullptr)
            return nullptr;
        else {
            Info *temp = new Info;
            temp->key = node->key;
            temp->left = buildInfoTree(node->leftCh);
            temp->right = buildInfoTree(node->rightCh);
            return temp;
        }
    }

    void InfoTree::setYCoord(Info *cur, std::queue<Info *> &que, int &count, int &timesNext, int &timesNow) {
        cur->y = count * (2 * kRadius_ + kHeight_);
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

    void InfoTree::calcYCoord() {
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
            setYCoord(cur, que, count, timesNext, timesNow);
        }
    }
}// namespace mvc
