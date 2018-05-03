package com.company;

import java.util.ArrayList;

public class CollectionChangerReverse<T> {
    public ArrayList<T> Permute(ArrayList<T> arr) {
        T tmp;
        for (int i = 0; i < arr.size() / 2; i++) {
            tmp = arr.get(i);
            arr.set(i, arr.get(arr.size() - 1 - i));
            arr.set(arr.size() - 1 - i, tmp);
        }
        return arr;
    }
}
