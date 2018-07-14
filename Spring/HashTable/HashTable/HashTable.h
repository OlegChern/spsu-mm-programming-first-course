#pragma once
#include "LinkedList.h"
/// <summary>
/// ��� �������
/// </summary>
template <typename T>
class HashTable
{
private:

#pragma region ����
	/// <summary>
	/// ���������� id
	/// </summary>
	int id;
	/// <summary>
	/// ��� �������
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	int HashFunction(T value) {
		return value % lists.size();
	}

	vector<LinkedList<T, T>> lists;
#pragma endregion

public:

#pragma region ������������/�����������

	HashTable(int count) {
		id = 0;
		lists = vector<LinkedList<T, T>>(count);
	}

	~HashTable() {

	}
#pragma endregion

#pragma region ������

	void Add(T value) {
		int hash = HashFunction(value);
		lists[hash].addToBegin(id++, value);
	}

	void Add(T value, int lifeTime) {
		int hash = HashFunction(value);
		lists[hash].addToBegin(id++, value, lifeTime);
	}

	void Delete(T value) {

	}

	string ToStr() {
		string str = "";
		for (LinkedList<T, T> list : lists)
			str += list.ToStr() + "\n";
		return str;
	}
#pragma endregion
};

