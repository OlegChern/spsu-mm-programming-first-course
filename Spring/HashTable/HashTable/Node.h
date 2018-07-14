#include "stdafx.h"
#pragma once
using namespace std;

/// <summary>
/// ������� ������
/// </summary>
template <typename T1, typename T2>
class Node
{
#pragma region ����

	T1 key;
	T2 value;
	Node* next;
	Node* previous;
#pragma endregion

public:

#pragma region ����
	/// <summary>
	/// ����� �����
	/// </summary>
	size_t lifeTime;
#pragma endregion

#pragma region ������������/�����������
	Node() {
		value = NULL;
		key = NULL;
		next = NULL;
		previous = NULL;
		lifeTime = NULL;
	}
	
	Node(T1 newKey, T2 newValue, size_t _lifeTime)
	{
		value = newValue;
		key = newKey;
		next = NULL;
		previous = NULL;
		lifeTime = _lifeTime;
		thread destTread(&Node::selfDestruct, this);
		destTread.detach();
	}
	
	~Node() {

	};
#pragma endregion

#pragma region ������

	void selfDestruct() {
		size_t curTime = clock();
		while (clock() - curTime < lifeTime)
		{
		}
		value = 0;
	}

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
#pragma endregion

};
