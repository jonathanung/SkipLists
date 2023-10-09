#ifndef SKIP_NODE_HPP
#define SKIP_NODE_HPP

#include <vector>

/**
 * @brief Skip List SkipNode
 * 
 * @author Jonathan Ung
 */
class SkipNode {
    public:
        int *value;
        std::vector<SkipNode *> next;
        SkipNode(int* v, int lvl){
            value = v;
            next = std::vector<SkipNode *>(lvl+1, nullptr);
        }
};

#endif