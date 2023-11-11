#include "mazeStack.h"
#pragma once
template <class Object>
mazeStack<Object>::mazeStack()
{
    top = NULL;
}

template <class Object>
mazeStack<Object>::mazeStack(const mazeStack<Object> & rhs)
{
    top = NULL;
    Node* rCur = rhs.top;
    Node** cur = &top;

    while (rCur != NULL) {

        *cur = new Node(rCur->data, NULL);

        rCur = rCur->next;
        cur = &((*cur)->next);
    }
}

template <class Object>
mazeStack<Object>::~mazeStack()
{
    Node * temp;
    temp = top;
    while (temp != NULL)
    {
        top = top->next;
        delete temp;
        temp = top;
    }
}

template <class Object>
void mazeStack<Object>::addTop(Object Obj)
{
    if (top == NULL) 
    {
        Node * node = new Node;
        node->data = Obj;
        node->next = NULL;
        top = node;
    }

    else
    {
        Node * node = new Node;
        node->data = Obj;
        node->next = top;
        top = node;
    }
}

template <class Object>
Object mazeStack<Object>::getTop()
{
    return top->data;
}

template <class Object>
bool mazeStack<Object>::isEmpty()
{
    if (top == NULL)
    {
        return true;
    }

    else return false;
}

template <class Object>
Object mazeStack<Object>::removeTop()
{
    if (top != NULL)
    {
        Node* temp = top;
        Object data = top->data;
        top = top->next;
        delete temp;
        return data;
    }
}