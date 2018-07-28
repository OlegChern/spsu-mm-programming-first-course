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
#pragma region ѕол€
	T1 key;
	T2 value;
	Node* next;
	Node* previous;
#pragma endregion

public:

#pragma region ѕол€
	/// <summary>
	/// врем€ жизни
	/// </summary>
	size_t lifeTime;
	/// <summary>
	/// врем€ создани€
	/// </summary>
	size_t createTime;
	/// <summary>
	/// общий указатель на значение
	/// </summary>
	shared_ptr<int> sharedPointer;
	/// <summary>
	/// слаба€ ссылка на значение
	/// </summary>
	weak_ptr<T2>valuePtr;
#pragma endregion

#pragma region  онструкторы/ƒеструкторы
	Node() {
		value = NULL;
		//valuePtr = NULL;
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
		sharedPointer = make_shared<int>(value);
		valuePtr = sharedPointer;
	}

	~Node() {

	};
#pragma endregion

#pragma region ћетоды

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
		if (curTime - createTime > lifeTime)
			valuePtr.reset();
		int i = valuePtr.use_count();
		if (auto spt = valuePtr.lock())
			return to_string(*spt);
		return "ptr expired\n";
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
	/// <summary>
	/// преобразует элемент в строку
	/// </summary>
	/// <returns>выходна€ строка "(ключ, значение, врем€ жизни(мс) , времени осталось(мс))"</returns>
	string toStr() {
		string str = "";
		/// <summary>
		/// сколько времени прошло после создани€
		/// </summary>
		int timePassed = clock() - createTime;
		/// <summary>
		/// сколько времени осталось - отрицательное число - врем€ вышло,
		/// указатель уничтожен
		/// </summary>
		int timeLeft = lifeTime - timePassed;
		/// <summary>
		/// выходна€ строка:
		/// (ключ, значение, врем€ жизни(мс) , времени осталось(мс))
		/// </summary>
		str += "(" +
			to_string(getKey()) + ";" +
			getValue() + ";" +
			to_string(lifeTime) + ";" +
			to_string(timeLeft) + ")->";
		return str;
	}
#pragma endregion

};
