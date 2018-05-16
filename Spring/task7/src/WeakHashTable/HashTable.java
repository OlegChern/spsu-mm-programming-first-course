package WeakHashTable;

import java.lang.ref.*;
import java.util.*;

public class HashTable<K, V> extends AbstractMap<K, V> implements Map<K, V> {

    private Entry<K, V>[] table;

    private int size;

    private int loadFactor;

    private final static int capacity = 16;

    private Timer timer = new Timer(true);

    private int limit;

    //Reference queue for cleared WeakEntries
    private final ReferenceQueue<Object> queue = new ReferenceQueue<>();

    @SuppressWarnings("unchecked")
    private Entry<K, V>[] newTable(int n) {
        return (Entry<K, V>[]) new Entry[n];
    }

    private boolean powerOfTwo(int value) {
        while (value > 0) {

            if (value % 2 == 0)
            {
                value /= 2;
            }
            else return false;
        }
        return true;

    }

    public HashTable(int capacity, int loadFactor) {
        if (capacity < 0 && (powerOfTwo(capacity) == false))
            throw new IllegalArgumentException("Illegal Initial Capacity: " + capacity +" should be the power of 2 and positive value");
        if (loadFactor <= 0)
            throw new IllegalArgumentException("Illegal Load factor: " + loadFactor);
        table = newTable(capacity);
        this.loadFactor = loadFactor;
        limit = loadFactor * capacity;
    }

    public HashTable(int loadFactor)
    {
        this(capacity, loadFactor);
    }

    private Entry<K, V>[] getTable() {
        return table;
    }

    public int size() {
        if (size == 0)
            return 0;
        return size;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public V get(Object key) {
        Object k = (key == null) ? new Object() : key;
        int h = key.hashCode() % table.length;
        Entry<K, V>[] tab = getTable();
        int index = h & (tab.length - 1);
        Entry<K, V> e = tab[index];
        while (e != null) {
            if (e.hash == h && ((k == e.get()) || k.equals(e.get())))
                return e.value;
            e = e.next;
        }
        return null;
    }

    public boolean containsKey(Object key) {
        return getEntry(key) != null;
    }

    private Entry<K, V> getEntry(Object key) {
        Object k = (key == null) ? new Object() : key;
        int h = key.hashCode() % table.length;
        Entry<K, V>[] tab = getTable();
        int index = h & (tab.length - 1);
        Entry<K, V> e = tab[index];
        while (e != null && !(e.hash == h && ((k == e.get()) || k.equals(e.get()))))
            e = e.next;
        return e;
    }

    public V put(K key, V value) {
        Object k = ((key == null) ? new Object() : key);
        int h = k.hashCode() % table.length;
        Entry<K, V>[] tab = getTable();
        int i = h & (tab.length - 1);
        timer.schedule(new TimerTask() {K tmp = key; @Override public void run() { tmp = null; }}, loadFactor);
        for (Entry<K, V> e = tab[i]; e != null; e = e.next) {
            if (h == e.hash && ((k == e.get()) || k.equals(e.get()))) {
                V oldValue = e.value;
                if (value != oldValue)
                    e.value = value;
                return oldValue;
            }
        }
        Entry<K, V> e = tab[i];
        tab[i] = new Entry<>(k, value, queue, h, e);
        if (++size >= (limit))
            resize(tab.length *2);
        return null;
    }

    private void resize(int newCapacity) {
        Entry<K, V>[] oldTable = getTable();
        Entry<K, V>[] newTable = newTable(newCapacity);
        transfer(oldTable, newTable);
        table = newTable;
        if (size >= limit / 2) {
            limit = newCapacity * loadFactor;
        } else {
            transfer(newTable, oldTable);
            table = oldTable;
        }
    }

//Transfers all entries from src to final table


    private void transfer(Entry<K, V>[] src, Entry<K, V>[] dest) {
        for (int j = 0; j < src.length; ++j) {
            Entry<K, V> e = src[j];
            src[j] = null;
            while (e != null) {
                Entry<K, V> next = e.next;
                Object key = e.get();
                if (key == null) {
                    e.next = null;
                    e.value = null;
                    size--;
                } else {
                    int i = e.hash & (dest.length - 1);
                    e.next = dest[i];
                    dest[i] = e;
                }
                e = next;
            }
        }
    }

    public void putAll(Map<? extends K, ? extends V> m) {
        int putKeys = m.size();
        if (putKeys == 0)
            return;
        if (putKeys > limit) {
            int newLimit = putKeys / loadFactor + 1;
            int newSize = table.length;
            while (newSize < newLimit)
                newSize <<= 1;
            if (newSize > table.length)
                resize(newSize);
        }

        for (Map.Entry<? extends K, ? extends V> e : m.entrySet())
            put(e.getKey(), e.getValue());
    }

    public V remove(Object key) {
        Object k = (key == null) ? new Object() : key;
        int h = key.hashCode() % table.length;
        Entry<K, V>[] tab = getTable();
        int i = h & (tab.length - 1);
        Entry<K, V> prev = tab[i];
        Entry<K, V> e = prev;

        while (e != null) {
            Entry<K, V> next = e.next;
            if (h == e.hash && ((k == e.get()) || k.equals(e.get()))) {
                size--;
                if (prev == e)
                    tab[i] = next;
                else
                    prev.next = next;
                return e.value;
            }
            prev = e;
            e = next;
        }

        return null;
    }

    public void clear() {

        Arrays.fill(table, null);
        size = 0;
    }

    public boolean containsValue(Object value) {
        if (value == null)
            return true;

        Entry<K, V>[] tab = getTable();
        for (int i = tab.length; i-- > 0; )
            for (Entry<K, V> e = tab[i]; e != null; e = e.next)
                if (value.equals(e.value))
                    return true;
        return false;
    }


    private static class Entry<K, V> extends WeakReference<Object> implements Map.Entry<K, V> {
        V value;
        final int hash;
        Entry<K, V> next;

        //Creates new entry
        Entry(Object key, V value, ReferenceQueue<Object> queue, int hash, Entry<K, V> next) {
            super(key, queue);
            this.value = value;
            this.hash = hash;
            this.next = next;
        }

        @SuppressWarnings("unchecked")
        public K getKey() {
            return (K) ((get() == new Object()) ? null : get());
        }

        public V getValue() {
            return value;
        }

        public V setValue(V newValue) {
            V oldValue = value;
            value = newValue;
            return oldValue;
        }

        public boolean equals(Object o) {
            if (!(o instanceof Map.Entry))
                return false;
            Map.Entry<?, ?> e = (Map.Entry<?, ?>) o;
            K k1 = getKey();
            Object k2 = e.getKey();
            if (k1 == k2 || (k1 != null && k1.equals(k2))) {
                V v1 = getValue();
                Object v2 = e.getValue();
                if (v1 == v2 || (v1 != null && v1.equals(v2)))
                    return true;
            }
            return false;
        }

        public int hashCode() {
            K k = getKey();
            V v = getValue();
            return ((k == null ? 0 : k.hashCode()) ^ (v == null ? 0 : v.hashCode()));
        }

        public String toString() {
            return getKey() + "=" + getValue();
        }
    }


    private abstract class HashIterator<T> implements Iterator<T> {
        private int index;
        private Entry<K, V> entry = null;
        private Entry<K, V> lastReturned = null;

        private Object nextKey = null;

        private Object currentKey = null;

        HashIterator() {
            index = isEmpty() ? 0 : table.length;
        }

        public boolean hasNext() {
            Entry<K, V>[] t = table;

            while (nextKey == null) {
                Entry<K, V> e = entry;
                int i = index;
                while (e == null && i > 0)
                    e = t[--i];
                entry = e;
                index = i;
                if (e == null) {
                    currentKey = null;
                    return false;
                }
                nextKey = e.get();
                if (nextKey == null)
                    entry = entry.next;
            }
            return true;
        }

        protected Entry<K, V> nextEntry() {
            if (nextKey == null && !hasNext())
                throw new NoSuchElementException();

            lastReturned = entry;
            entry = entry.next;
            currentKey = nextKey;
            nextKey = null;
            return lastReturned;
        }

        public void remove() {
            if (lastReturned == null)
                throw new IllegalStateException();
            HashTable.this.remove(currentKey);
            lastReturned = null;
            currentKey = null;
        }

    }

    private class EntryIterator extends HashIterator<Map.Entry<K, V>> {
        public Map.Entry<K, V> next() {
            return nextEntry();
        }
    }

    private transient Set<Map.Entry<K, V>> entrySet = null;

    public Set<Map.Entry<K, V>> entrySet() {
        Set<Map.Entry<K, V>> es = entrySet;
        return es != null ? es : (entrySet = new EntrySet());
    }

    private class EntrySet extends AbstractSet<Map.Entry<K, V>> {
        public Iterator<Map.Entry<K, V>> iterator() {
            return new EntryIterator();
        }

        public int size() {
            return HashTable.this.size();
        }

        public void clear() {
            HashTable.this.clear();
        }
    }
}