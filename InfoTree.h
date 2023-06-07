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
        InfoTree(const Node* rootGet)
            :root_(buildInfoTree(rootGet))
        {
            calcYCoord();
            calcXCoord();
        }
        ~InfoTree();
        Info* getRoot() { return root_; }
        std::pair<int, bool> findValue(int x, int y);
        void clear(Info* treeInfo);

    private:
        static constexpr int kRadius_ = 40;
        static constexpr int kHeight_ = 30;
        static constexpr int kWidth_ = 15;
    private:
//        void clear(Info* treeInfo);
        void setWidth(Info* cur);
        void setXCoord(Info* cur, std::queue<Info *>& que, int& count, int& timesNext, int& timesNow);
        void calcXCoord();
        Info* buildInfoTree(const Node* node);
        void setYCoord(Info* cur, std::queue<Info *>& que, int& count, int& timesNext, int& timesNow);
        void calcYCoord();

        Info* root_ = nullptr;
    };

}

#endif//COURSEPROJECT_INFOTREE_H
