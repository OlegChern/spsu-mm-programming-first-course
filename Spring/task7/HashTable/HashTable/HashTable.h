#pragma once
#include "LinkedList.h"
/// <summary>
/// хэш таблица
/// </summary>
template <typename T>
class HashTable
{
private:

#pragma region Поля
	/// <summary>
	/// было ли первое добавление в таблицу
	/// </summary>
	bool firstAdd = true;
	/// <summary>
	/// уникальный id
	/// </summary>
	int id;
	/// <summary>
	/// хэш функция
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	int hashFunction(T value) {
		return value % lists.size();
	}

	vector<LinkedList<T, T>> lists;
#pragma endregion

public:

#pragma region Конструкторы/Деструкторы

	HashTable(int count) {
		id = 0;
		lists = vector<LinkedList<T, T>>(count);
	}

	~HashTable() {

	}
#pragma endregion

#pragma region Методы

	void add(T value) {
		int hash = hashFunction(value);
		lists[hash].addToBegin(id++, value);
	}

	void add(T value, int lifeTime) {
		int hash = hashFunction(value);
		lists[hash].addToBegin(id++, value, lifeTime);
	}

	string toStr() {
		string str = "";
		for (LinkedList<T, T> list : lists)
			str += list.toStr() + "\n";
		return str;
	}
#pragma endregion
};

