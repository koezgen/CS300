#ifndef _MAZESTACK_H
#define _MAZESTACK_H

#include <string>
#include <iostream>
#include "mazeBlock.h"
#include "mazeWalls.h"
using namespace std;

template <class Object>
class mazeStack
{
    private:
        struct Node
        {
            Object data;
            Node * next;
            Node() : data(Object()), next(nullptr) { }
            Node(Object data, Node * next) : data(data), next(next) { }
        };

        Node * top;

    public:
        mazeStack();
        mazeStack(const mazeStack<Object>& rhs);
        ~mazeStack();
        void addTop(Object node);
        Object getTop();
        bool isEmpty();
        Object removeTop();
    
    friend class mazeBlock;
    friend class mazeWalls;
};

#include "mazeStack.hpp"

#endif