#ifndef COURSEPROJECT_INFOTREE_H
#define COURSEPROJECT_INFOTREE_H

#include "Model.h"
#include <queue>

namespace mvc {

    struct Info{
        int x = 0;
        int y = 0;
        int key;
        Info* left;
        Info* right;
        int width;
    };

    class InfoTree {
    public:
        InfoTree(const Node* rootGet){
            calcYCoord(rootGet);
            calcXCoord();
        }
        ~InfoTree();
        Info* getRoot() { return root_; }
        std::pair<int, bool> findValue(int x, int y);

    private:
        void clear(Info* treeInfo);
        void setWidth(Info* cur);
        void calcXCoord();
        Info* copy(const Node* node);
        void calcYCoord(const Node* node);

        static constexpr int RADIUS = 40;
        static constexpr int HEIGHT = 30;
        static constexpr int WIDTH = 15;
        Info* root_ = nullptr;
    };

}

#endif//COURSEPROJECT_INFOTREE_H
