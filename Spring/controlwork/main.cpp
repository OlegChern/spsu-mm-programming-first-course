#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CollectionReverse
{
public:
    vector <T> Permute(vector <T> collection)
    {
        int size = collection.size();
        int i;
        for (i = 0; i < size / 2; i++)
        {
            swap(collection[i], collection[size - i - 1]);
        }
        return collection;
    }

};

template <typename T>
class CollectionShift
{
    public:
    vector <T> Permute(vector <T> collection)
    {
        int size = collection.size();
        int i;
        T tmp = collection[size - 1];
        for (i = size - 1; i > 0; i--)
        {
            collection[i] = collection[i - 1];
        }
        collection[0] = tmp;
        return collection;
    }
};

main()
{
    vector <int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    CollectionShift<int> changer;
    a = changer.Permute(a);
    cout << a[0] << ' ' << a[1] << ' ' << a[2];
    return 0;
}

