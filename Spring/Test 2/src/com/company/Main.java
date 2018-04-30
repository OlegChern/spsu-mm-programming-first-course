package com.company;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        ArrayList<Integer> list = new ArrayList<>();
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);
        CollectionChangerReverse <Integer> rev = new CollectionChangerReverse<>();
        CollectionChangerShift <Integer> shft = new CollectionChangerShift<>();
        CollectionChangerShiftBack <Integer> shftb = new CollectionChangerShiftBack<>();
        rev.Permute(list);
        System.out.println("Here is a reverted sequence:");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i)+" ");
        }
        rev.Permute(list);
        System.out.println();
        System.out.println("Here is a shifted original sequence:");
        shft.Permute(list);
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i)+" ");
        }
        System.out.println();
        System.out.println("And shifted back:");
        shftb.Permute(list);
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i)+" ");
        }
    }
}

