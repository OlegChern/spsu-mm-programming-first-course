using namespace std;
#pragma once
#include "LinkedList.h"

template <typename T1, typename T2>
LinkedList<T1, T2>::LinkedList()
{
    nullNode = new Node<T1, T2> ();
    setHead(nullNode);
    setTail(nullNode);
}

template <typename T1, typename T2>
LinkedList<T1, T2>::~LinkedList()
{
    Node<T1, T2>* tmp2 = nullNode;
    Node<T1, T2>* tmp = getHead();
    while (tmp != nullNode)
    {
        tmp2 = tmp->getNext();
        delete tmp;
        tmp = tmp2;
    }
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::setHead(Node<T1, T2>* ptr)
{
    head = ptr;
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::setTail(Node<T1, T2>* ptr)
{
    tail = ptr;
}

template <typename T1, typename T2>
Node<T1, T2>* LinkedList<T1, T2>::getHead()
{
    return head;
}

template <typename T1, typename T2>
Node<T1, T2>* LinkedList<T1, T2>::getTail()
{
    return head;
}


template <typename T1, typename T2>
void LinkedList<T1, T2>::addToBegin(T1 newKey, T2 newValue)
{
    Node<T1, T2>* tmp = getHead();
    setHead(new Node<T1, T2>(newKey, newValue));
    getHead()->setNext(tmp);
    getHead()->setPrevious((nullNode));
    tmp->setPrevious(getHead());
}


template <typename T1, typename T2>
void LinkedList<T1, T2>::addToEnd(T1 newKey, T2 newValue)
{
    Node<T1, T2>* tmp = getTail();
    setTail(new Node<T1, T2>(newKey, newValue));
    getTail()->setPrevious(tmp);
    getTail()->setNext(nullNode);
    tmp->setNext(getTail());
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::deleteByKey(T1 keyToDelete)
{
    Node<T1, T2>* tmp = getHead();
    while (tmp != nullNode)
    {
        if (tmp->getKey() == keyToDelete)
        {
            if (tmp->getPrevious() != nullNode)
            {
                tmp->getPrevious()->setNext(tmp->getNext());
            }
            else
            {
                setHead(tmp->getNext());
            }
            if (tmp->getNext() != nullNode)
            {
                tmp->getNext()->setPrevious(tmp->getPrevious());
            }
            else
            {
                setTail(tmp->getPrevious());
            }
            delete tmp;
            break;
        }
        tmp = tmp->getNext();
        if (tmp == nullNode)
        {
            cout << "Key not found";
        }
    }
}

template <typename T1, typename T2>
T2 LinkedList<T1, T2>::findByKey(T1 keyToFind)
{
    Node<T1, T2>* tmp = getHead();
    while (tmp != nullNode)
    {
        if (tmp->getKey() == keyToFind)
        {
            return tmp->getValue();
        }
        tmp = tmp->getNext();
    }
    if (tmp == nullNode)
    {
        cout << "Key not found";
    }
    return 0;
}
