#include "stdafx.h"
#pragma once
using namespace std;

/// <summary>
/// элемент списка
/// </summary>
template <typename T1, typename T2>
class Node
{
private:
#pragma region Поля
	T1 key;
	T2 value;
	Node* next;
	Node* previous;
#pragma endregion

public:

#pragma region Поля
	/// <summary>
	/// время жизни
	/// </summary>
	size_t lifeTime;
	/// <summary>
	/// дата создания
	/// </summary>
	size_t createTime;
	/// <summary>
	/// слабая ссылка на значение
	/// </summary>
	T2 *valuePtr;
#pragma endregion

#pragma region Конструкторы/Деструкторы

	Node() {
		value = NULL;
		valuePtr = NULL;
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
		valuePtr = &value;
		createTime = clock();
	}

	~Node() {

	};
#pragma endregion

#pragma region Методы

	void selfDestruct() {
		size_t curTime = clock();
		while (clock() - curTime < lifeTime)
		{
		}
		valuePtr = NULL;
	}

	void changeValue(T2 newValue)
	{
		value = newValue;
	}

	string getValue()
	{
		size_t curTime = clock();
		if (curTime - createTime<lifeTime)
			return to_string(*valuePtr);
		else
			return"expired";
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
