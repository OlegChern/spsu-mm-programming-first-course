package com.company;


import static java.lang.Math.abs;

public class HashTable <KeyType, ValueType> {
    private final int SIZE_OF_TABLE;
    private LinkedList<KeyType, ValueType>[] table;

    HashTable(int SIZE_OF_TABLE) {
        this.SIZE_OF_TABLE = SIZE_OF_TABLE;
        table = new LinkedList[SIZE_OF_TABLE];
        for (int i = 0; i < SIZE_OF_TABLE; i++) {
            table[i] = new LinkedList<KeyType, ValueType>();
        }
    }

    public void DeleteElementByKey(KeyType key) {
        if (!table[abs(key.hashCode()) % SIZE_OF_TABLE].deleteByKey(key)) {
            System.out.println("Key not found");
        }
    }

    public void AddElement(KeyType key, ValueType value) {
        table[abs(key.hashCode()) % SIZE_OF_TABLE].addToBegin(key, value);
    }

    public ValueType findByKey(KeyType key) {
        ValueType tmp = table[abs(key.hashCode()) % SIZE_OF_TABLE].findByKey(key);
        if (tmp == null) {
            System.out.println("Key not found");
            return null;
        } else {
            return tmp;
        }
    }
}
