#ifndef D_SKIP_LIST_HPP
#define D_SKIP_LIST_HPP

#include "DSkipNode.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

/**
 * @brief A Doubly Linked Skip List, which allows for more traversal options and minor 
 * optimization improvements, at the cost of some memory usage.
 * 
 * @author Jonathan Ung
 */
class DSkipList
{
    private:
        int MAX_ALLOWED_LVL;
        int topLevel;
        DSkipNode *head;
        DSkipNode *tail;
        int getRandomLevel();

    public:
        DSkipList();
        DSkipList(int);
        ~DSkipList();
        void insertValue(int);
        void insertValueFront(int);
        void insertValueBack(int);
        friend std::ostream& operator<<(std::ostream&, const DSkipList&);
        void show() const;
        void showBack() const;
        bool search(int) const;
        bool searchFront(int) const;
        bool searchBack(int) const;
        void remove(int);
        void removeHighestFront(int);
        void removeHighestBack(int);
        void removeFirst(int);
        void removeLast(int);
};

int DSkipList::getRandomLevel(){
    bool heads = rand() % 2;
    int nodeLevel = 0;
    while (heads && nodeLevel < MAX_ALLOWED_LVL){
        nodeLevel++;
        heads = rand() % 2;
    }
    return nodeLevel;
}

DSkipList::DSkipList(){
    this->MAX_ALLOWED_LVL = 3;
    this->topLevel = 0;
    this->head = new DSkipNode(nullptr, this->topLevel);
    this->tail = new DSkipNode(nullptr, this->topLevel);
    tail->prev[0] = head;
    head->next[0] = tail;
}

DSkipList::~DSkipList() {
    DSkipNode *curr = head;
    while (curr != nullptr) {
        DSkipNode *next = curr->next[0];
        curr->next.clear();
        curr->prev.clear();
        delete curr;
        curr = next;
    }
    this->MAX_ALLOWED_LVL = -1;
    this->topLevel = -1;
}

DSkipList::DSkipList(int maxLevel){
    this->MAX_ALLOWED_LVL = maxLevel;
    this->topLevel = 0;
    this->head = new DSkipNode(nullptr, this->topLevel);
    this->tail = new DSkipNode(nullptr, this->topLevel);
    tail->prev[0] = head;
    head->next[0] = tail;
}

void DSkipList::insertValue(int value){
    if ((this->head->next[0]->value == nullptr || this->tail->prev[0]->value == nullptr) && this->topLevel == 0){
        insertValueFront(value);
        return;
    }
    double mid = double(*(this->head->next[0]->value)) / double(*(this->tail->prev[0]->value));
    if (value > mid) {
        insertValueBack(value);
        return;
    }
    insertValueFront(value);
}

void DSkipList::insertValueFront(int value){
    int nodeLevel = getRandomLevel();
    if (nodeLevel > this->topLevel){
        this->head->next.resize(nodeLevel + 1, tail);
        this->tail->prev.resize(nodeLevel + 1, head);
        for (int i = this->topLevel + 1; i <= nodeLevel; i++) {
            tail->prev[i] = head;
            head->next[i] = tail;
        }
        this->topLevel = nodeLevel;
    }
    int* persistentVal = new int(value);
    DSkipNode *insertedNode = new DSkipNode(persistentVal, nodeLevel);
    DSkipNode *curr = head;
    while (nodeLevel >= 0) {
        if (curr->next[nodeLevel] != nullptr &&
            curr->next[nodeLevel]->value != nullptr &&
            *(curr->next[nodeLevel]->value) < *(insertedNode->value))
        {
            curr = curr->next[nodeLevel];
        }
        else
        {
            DSkipNode *temp = curr->next[nodeLevel];
            curr->next[nodeLevel] = insertedNode;
            insertedNode->prev[nodeLevel] = curr;
            temp->prev[nodeLevel] = insertedNode;
            insertedNode->next[nodeLevel] = temp;
            nodeLevel--;
        }
    }
}

void DSkipList::insertValueBack(int value){
    int nodeLevel = getRandomLevel();
    if (nodeLevel > this->topLevel){
        this->head->next.resize(nodeLevel + 1, tail);
        this->tail->prev.resize(nodeLevel + 1, head);
        for (int i = this->topLevel + 1; i <= nodeLevel; i++) {
            tail->prev[i] = head;
            head->next[i] = tail;
        }
        this->topLevel = nodeLevel;
    }
    int* persistentVal = new int(value);
    DSkipNode *insertedNode = new DSkipNode(persistentVal, nodeLevel);
    DSkipNode *curr = tail;
    while (nodeLevel >= 0) {
        if (curr->prev[nodeLevel] != nullptr &&
            curr->prev[nodeLevel]->value != nullptr &&
            *(curr->prev[nodeLevel]->value) > *(insertedNode->value))
        {
            curr = curr->prev[nodeLevel];
        }
        else
        {
            DSkipNode *temp = curr->prev[nodeLevel];
            curr->prev[nodeLevel] = insertedNode;
            insertedNode->next[nodeLevel] = curr;
            temp->next[nodeLevel] = insertedNode;
            insertedNode->prev[nodeLevel] = temp;
            nodeLevel--;
        }
    }
}

std::ostream& operator<<(std::ostream& o, const DSkipList& dSL){
    for (int i = dSL.MAX_ALLOWED_LVL; i >= 0; i--) {
        if (i > dSL.topLevel) {
            o << "Level " << i << " has no data." << std::endl;
            continue;
        }
        o << "Level " << i << ": " << "head" << " <-> ";
        DSkipNode *curr = dSL.head->next[i];
        while (curr != nullptr && curr->value != nullptr) {
            o << *(curr->value);
            if (curr->next[i] != nullptr) {
                o << " <-> ";
            }
            curr = curr->next[i];
        }
        o << "tail";
        o << std::endl;
    }
    return o;
}

void DSkipList::show() const{
    for (int i = this->MAX_ALLOWED_LVL; i >= 0; i--) {
        if (i > this->topLevel) {
            std::cout << "Level " << i << "has no data." << std::endl;
            continue;
        }
        std::cout << "Level " << i << ": " << "head" << " <-> ";
        DSkipNode *curr = this->head->next[i];
        while (curr != nullptr && curr->value != nullptr) {
            std::cout << *(curr->value);
            if (curr->next[i] != nullptr) {
                std::cout << " <-> ";
            }
            curr = curr->next[i];
        }
        std::cout << "tail";
        std::cout << std::endl;
    }
}

void DSkipList::showBack() const{
    for (int i = this->MAX_ALLOWED_LVL; i >= 0; i--) {
        if (i > this->topLevel) {
            std::cout << "Level " << i << "has no data." << std::endl;
            continue;
        }
        std::cout << "Level " << i << ": " << "tail" << " <-> ";
        DSkipNode *curr = this->tail->prev[i];
        while (curr != nullptr && curr->value != nullptr) {
            std::cout << *(curr->value);
            if (curr->prev[i] != nullptr) {
                std::cout << " <-> ";
            }
            curr = curr->prev[i];
        }
        std::cout << "head";
        std::cout << std::endl;
    }
}

bool DSkipList::search(int num) const{
    if (this->head->next[0]->value == nullptr || this->tail->prev[0]->value == nullptr){
        return false;
    }
    double mid = (double(*(this->head->next[0]->value)) + double(*(this->tail->prev[0]->value)))/2.0;
    if (num > mid)
    {
        return searchBack(num);
    }
    return searchFront(num);
}

bool DSkipList::searchFront(int num) const{
    int level = this->topLevel;
    DSkipNode *curr = this->head;
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

bool DSkipList::searchBack(int num) const{
    int level = this->topLevel;
    DSkipNode *curr = this->tail;
    while (level >= 0){
        if(curr->prev[level] == nullptr || 
        curr->prev[level]->value == nullptr || 
        *(curr->prev[level]->value) < num){
            level--;
        } else if (*(curr->prev[level]->value) == num) {
            return true;
        } else if (*(curr->prev[level]->value) > num) {
            curr = curr->prev[level];
        }
    }
    return false;
}

void DSkipList::remove(int num){
    if (this->head->next[0]->value == nullptr || this->tail->prev[0]->value == nullptr){
        return;
    }
    double mid = double(*(this->head->next[0]->value)) / double(*(this->tail->prev[0]->value));
    if (num > mid) {
        removeHighestBack(num);
    } else {
        removeHighestFront(num);
    }
}

void DSkipList::removeHighestFront(int num){
    int level = this->topLevel;
    DSkipNode *curr = this->head;
    DSkipNode *temp = nullptr;
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
        for (int i = 0; i < temp->prev.size(); i++){
            temp->prev[i]->next[i] = temp->next[i];
            temp->next[i]->prev[i] = temp->prev[i];
        }
        delete temp;
    }
}

void DSkipList::removeHighestBack(int num){
    int level = this->topLevel;
    DSkipNode *curr = this->tail;
    DSkipNode *temp = nullptr;
    while (level >= 0)
    {
        if(curr->prev[level] == nullptr || 
            curr->prev[level]->value == nullptr || 
            *(curr->prev[level]->value) < num){
            level--;
        } else if (*(curr->prev[level]->value) == num) {
            temp = curr->prev[level];
            break;
        } else if (*(curr->prev[level]->value) > num) {
            curr = curr->prev[level];
        }
    }
    if (temp != nullptr) {
        for (int i = 0; i < temp->prev.size(); i++){
            temp->prev[i]->next[i] = temp->next[i];
            temp->next[i]->prev[i] = temp->prev[i];
        }
        delete temp;
    }
}

void DSkipList::removeFirst(int num){
    int level = this->topLevel;
    DSkipNode *curr = this->head;
    DSkipNode *temp = nullptr;
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
        for (int i = 0; i < temp->prev.size(); i++){
            temp->prev[i]->next[i] = temp->next[i];
            temp->next[i]->prev[i] = temp->prev[i];
        }
        delete temp;
    }
}

void DSkipList::removeLast(int num){
    int level = this->topLevel;
    DSkipNode *curr = this->tail;
    DSkipNode *temp = nullptr;
    while (curr->prev[0] != nullptr)
    {
        if (*(curr->prev[0]->value) == num){
            temp = curr->prev[0];
            break;
        } else if (*(curr->prev[0]->value) > num) {
            curr = curr->prev[0];
        } else {
            break;
        }
    }
    if (temp != nullptr) {
        for (int i = 0; i < temp->prev.size(); i++){
            temp->prev[i]->next[i] = temp->next[i];
            temp->next[i]->prev[i] = temp->prev[i];
        }
        delete temp;
    }
}

#endif