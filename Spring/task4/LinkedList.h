#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#pragma once
#include <bits/stdc++.h>
#include "Node.h"


template <typename T1, typename T2>
class LinkedList
{
    Node<T1, T2>* head;
    Node<T1, T2>* tail;
    Node<T1, T2>* nullNode;
public:
    LinkedList();
    ~LinkedList();
    Node<T1, T2>* getHead();
    void setHead(Node<T1, T2>* ptr);
    Node<T1, T2>* getTail();
    void setTail(Node<T1, T2>* ptr);
    void addToBegin(T1 newKey, T2 newValue);
    void addToEnd(T1 newKey, T2 newValue);
    void deleteByKey(T1 keyToDelete);
    T2 findByKey(T1 keyToFind);
};

#include "LinkedList.cpp"

#endif // LINKEDLIST_H_INCLUDED
