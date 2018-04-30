package com.company;

import java.util.ArrayList;

public class CollectionChangerShiftBack<T> {
    public ArrayList<T> Permute(ArrayList<T> arr) {
        T tmp;
        tmp = arr.get(0);
        for (int i = 0; i < arr.size() - 1; i++) {
            arr.set(i, arr.get(i + 1));
        }
        arr.set(arr.size() - 1, tmp);
        return arr;
    }
}