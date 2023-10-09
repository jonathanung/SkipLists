#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include "SkipNode.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

/**
 * @brief A Skip List class.
 * 
 * @author Jonathan Ung
 */
class SkipList
{
    private:
        int MAX_ALLOWED_LVL;
        int topLevel;
        SkipNode *head;
        int getRandomLevel();

    public:
        SkipList();
        SkipList(int);
        ~SkipList();
        void insertValue(int);
        friend std::ostream& operator<<(std::ostream&, const SkipList &);
        void show() const;
        bool search(int) const;
        void remove(int);
        void removeHighest(int);
        void removeFirst(int);
};

int SkipList::getRandomLevel(){
    bool heads = rand() % 2;
    int nodeLevel = 0;
    while (heads && nodeLevel < MAX_ALLOWED_LVL){
        nodeLevel++;
        heads = rand() % 2;
    }
    return nodeLevel;
}

SkipList::SkipList(){
    this->MAX_ALLOWED_LVL = 3;
    this->topLevel = 0;
    this->head = new SkipNode(nullptr, this->topLevel);
}

SkipList::SkipList(int maxLevel){
    this->MAX_ALLOWED_LVL = maxLevel;
    this->topLevel = 0;
    this->head = new SkipNode(nullptr, this->topLevel);
}

SkipList::~SkipList() {
    SkipNode *curr = head;
    while (curr != nullptr) {
        SkipNode *next = curr->next[0];
        curr->next.clear();
        delete curr;
        curr = next;
    }
    this->MAX_ALLOWED_LVL = -1;
    this->topLevel = -1;
}

void SkipList::insertValue(int value){
    int nodeLevel = getRandomLevel();
    if (nodeLevel > this->topLevel){
        this->head->next.resize(nodeLevel + 1, nullptr);
        this->topLevel = nodeLevel;
    }
    int* persistentVal = new int(value);
    SkipNode *insertedNode = new SkipNode(persistentVal, nodeLevel);
    SkipNode *curr = head;
    while (nodeLevel >= 0) {
        if (curr->next[nodeLevel] != nullptr &&
            curr->next[nodeLevel]->value != nullptr &&
            *(curr->next[nodeLevel]->value) < *(insertedNode->value))
        {
            curr = curr->next[nodeLevel];
        }
        else
        {
            SkipNode *temp = curr->next[nodeLevel];
            curr->next[nodeLevel] = insertedNode;
            insertedNode->next[nodeLevel] = temp;
            nodeLevel--;
        }
    }
}

std::ostream& operator<<(std::ostream& o, const SkipList& sL){
    for (int i = sL.MAX_ALLOWED_LVL; i >= 0; i--) {
        if (i > sL.topLevel) {
            o << "Level " << i << " has no data." << std::endl;
            continue;
        }
        o << "Level " << i << ": ";
        SkipNode *curr = sL.head->next[i];
        while (curr != nullptr && curr->value != nullptr) {
            o << *(curr->value);
            if (curr->next[i] != nullptr) {
                o << " -> ";
            }
            curr = curr->next[i];
        }
        o << std::endl;
    }
    return o;
}

void SkipList::show() const{
    for (int i = this->MAX_ALLOWED_LVL; i >= 0; i--) {
        if (i > this->topLevel) {
            std::cout << "Level " << i << "has no data." << std::endl;
            continue;
        }
        std::cout << "Level " << i << ": ";
        SkipNode *curr = this->head->next[i];
        while (curr != nullptr && curr->value != nullptr) {
            std::cout << *(curr->value);
            if (curr->next[i] != nullptr) {
                std::cout << " -> ";
            }
            curr = curr->next[i];
        }
        std::cout << std::endl;
    }
}

bool SkipList::search(int num) const{
    if (this->head->next[0] == nullptr) {
        return false;
    }
    int level = this->topLevel;
    SkipNode *curr = this->head;
    while (level >= 0){
        if(curr->next[level] == nullptr || 
        curr->next[level]->value == nullptr || 
        *(curr->next[level]->value) > num){
            level--;
        } else if (*(curr->next[level]->value) == num) {
            return true;
        } else if (*(curr->next[level]->value) < num) {
            curr = curr->next[level];
        }
    }
    return false;
}

void SkipList::remove(int num){
    return removeHighest(num);
}

void SkipList::removeHighest(int num){
    if (this->head->next[0] == nullptr) {
        return;
    }
    int level = this->topLevel;
    SkipNode *curr = this->head;
    SkipNode *temp = nullptr;
    while (level >= 0)
    {
        if(curr->next[level] == nullptr || 
            curr->next[level]->value == nullptr || 
            *(curr->next[level]->value) > num){
            level--;
        } else if (*(curr->next[level]->value) == num) {
            temp = curr->next[level];
            break;
        } else if (*(curr->next[level]->value) < num) {
            curr = curr->next[level];
        }
    }
    if (temp != nullptr) {
        while (level >= 0) {
            if(curr->next[level] == nullptr || 
                curr->next[level]->value == nullptr || 
                *(curr->next[level]->value) > num){
                level--;
            } else if (curr->next[level] == temp) {
                if (curr->next[level] != nullptr){
                    curr->next[level] =  temp->next[level];
                } else {
                    curr->next[level] = nullptr;
                }
                if (level == 0){
                    delete temp;
                }
                level--;
            }
            else if (*(curr->next[level]->value) <= num)
            {
                curr = curr->next[level];
            }
        }
        for (int i = topLevel; i >= 0; i--){
            if (this->head->next[i] == nullptr){
                topLevel--;
            } else {
                break;
            }
        }
    }
}

void SkipList::removeFirst(int num){
    if (this->head->next[0] == nullptr) {
        return;
    }
    int level = this->topLevel;
    SkipNode *curr = this->head;
    SkipNode *temp = nullptr;
    while (curr->next[0] != nullptr)
    {
        if (*(curr->next[0]->value) == num){
            temp = curr->next[0];
            break;
        } else if (*(curr->next[0]->value) < num) {
            curr = curr->next[0];
        } else {
            break;
        }
    }
    if (temp != nullptr) {
        curr = this->head;
        while (level >= 0) {
            if(curr->next[level] == nullptr || 
                curr->next[level]->value == nullptr || 
                *(curr->next[level]->value) > num){
                level--;
                curr=this->head;
            } else if (curr->next[level] == temp) {
                if (curr->next[level] != nullptr){
                    curr->next[level] =  temp->next[level];
                } else {
                    curr->next[level] = nullptr;
                }
                if (level == 0){
                    delete temp;
                }
                level--;
            }
            else if (*(curr->next[level]->value) <= num)
            {
                curr = curr->next[level];
            }
        }
        for (int i = topLevel; i >= 0; i--){
            if (this->head->next[i] == nullptr){
                topLevel--;
            } else {
                break;
            }
        }
    }
}

#endif