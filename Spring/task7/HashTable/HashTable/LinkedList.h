#pragma once
#include "Node.h"

/// <summary>
/// двусвязный список
/// </summary>
template <typename T1, typename T2>
class LinkedList
{

#pragma region Поля
	Node<T1, T2>* head;
	Node<T1, T2>* tail;
	Node<T1, T2>* nullNode;
#pragma endregion

public:

#pragma region Конструкторы/Деструкторы
	LinkedList()
	{
		nullNode = new Node<T1, T2>();
		setHead(nullNode);
		setTail(nullNode);
	}

	~LinkedList()
	{
	}
#pragma endregion

#pragma region Методы
	void setHead(Node<T1, T2>* ptr)
	{
		head = ptr;
	}

	void setTail(Node<T1, T2>* ptr)
	{
		tail = ptr;
	}

	Node<T1, T2>* getHead()
	{
		return head;
	}

	Node<T1, T2>* getTail()
	{
		return head;
	}
	
	void addToBegin(T1 newKey, T2 newValue)
	{
		Node<T1, T2>* tmp = getHead();
		setHead(new Node<T1, T2>(0, newKey, newValue));
		getHead()->setNext(tmp);
		getHead()->setPrevious((nullNode));
		tmp->setPrevious(getHead());
	}

	void addToBegin(T1 newKey, T2 newValue, size_t _lifeTime)
	{
		addToBegin(newKey, newValue);
		head->lifeTime = _lifeTime;
	}

	void addToEnd(T1 newKey, T2 newValue)
	{
		Node<T1, T2>* tmp = getTail();
		setTail(new Node<T1, T2>(newKey, newValue));
		getTail()->setPrevious(tmp);
		getTail()->setNext(nullNode);
		tmp->setNext(getTail());
	}
	
	void deleteByKey(T1 keyToDelete)
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

	T2 findByKey(T1 keyToFind)
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

	string toStr() {
		string str = "";
		Node<T1, T2>* tmp = getHead();
		while (tmp != nullNode) {
			str += tmp->toStr();
			tmp = tmp->getNext();
		}
		return str;
	}
#pragma endregion
};