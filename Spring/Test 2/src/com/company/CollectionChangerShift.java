package com.company;

import java.util.ArrayList;

public class CollectionChangerShift<T> {
    public ArrayList<T> Permute(ArrayList<T> arr) {
        T tmp;
        tmp = arr.get(arr.size() - 1);
        for (int i = arr.size() - 1; i > 0; i--) {
            arr.set(i, arr.get(i - 1));
        }
        arr.set(0, tmp);
        return arr;
    }
}