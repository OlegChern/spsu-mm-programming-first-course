#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#pragma once
#include "LinkedList.h"
using namespace std;

template <typename T1, typename T2>
class Node
{
    T1 key;
    T2 value;
    Node* next;
    Node* previous;
public:
    Node(T1 newKey = 0, T2 newValue = 0)
    {
        value = newValue;
        key = newKey;
        next = 0;
        previous = 0;
    }
    ~Node(){};
    void changeValue(T2 newValue)
    {
        value = newValue;
    }
    T2 getValue()
    {
        return value;
    }
    T1 getKey()
    {
        return key;
    }
    void setNext(Node* ptr)
    {
        next = ptr;
    }
    void setPrevious(Node* ptr)
    {
        previous = ptr;
    }
    Node* getNext()
    {
        return next;
    }
    Node* getPrevious()
    {
        return previous;
    }
};

#endif // NODE_H_INCLUDED
