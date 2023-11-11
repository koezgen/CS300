#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <iostream>
#include <string>
#include "mazeBlock.h"
#include "mazeWalls.h"
using namespace std;

template <class Object>
class linkedList
{
    private:
        struct Node
        {
            Object data;
            Node * next;
        };

        Node * head;
        int size = 0;

    public:
        linkedList();
        linkedList(int range);
        ~linkedList();
        void removeElement(Object node);
        int getSize() { return size; };
        Object &operator[](int index);
};

template <class Object>
linkedList<Object>::linkedList()
{
    head = NULL;
}

template <class Object>
linkedList<Object>::linkedList(int range)
{
    head = NULL;
    size = range + 1;

    for (int i = range; i >= 0; i--)
    {
        Node * node = new Node;
        node->data = i;
        node->next = head;
        head = node;
    }
}

template <class Object>
linkedList<Object>::~linkedList()
{
    Node * temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

template <class Object>
void linkedList<Object>::removeElement(Object node)
{
    if (head == nullptr) return;

    if (head->data == node)
    {
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
        size--;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr)
    {
        if (temp->next->data == node)
        {
            Node* nodeToRemove = temp->next;
            temp->next = nodeToRemove->next;
            delete nodeToRemove;
            size--;
            return;
        }
        temp = temp->next;
    }

}

template <class Object>
Object& linkedList<Object>::operator[](int index) {
    Node* current = head;
    for (int i = 0; current != NULL && i < index; i++, current = current->next);
    if (current) {
        return current->data;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

#endif