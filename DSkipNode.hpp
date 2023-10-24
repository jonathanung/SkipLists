#ifndef D_SKIP_NODE_HPP
#define D_SKIP_NODE_HPP

#include <vector>

/**
 * @brief Doubly Linked Skip List DSkipNode
 * 
 * @author Jonathan Ung
 */
class DSkipNode {
    public:
        int *value;
        std::vector<DSkipNode *> prev;
        std::vector<DSkipNode *> next;
        DSkipNode(int* v, int lvl){
            value = v;
            prev = std::vector<DSkipNode *>(lvl+1, nullptr);
            next = std::vector<DSkipNode *>(lvl+1, nullptr);
        }
        ~DSkipNode() {
            delete value;
        }
};

#endif