package WeekHashMap;

import java.lang.ref.WeakReference;
import java.util.*;

public class WeakHashMap<K, V> implements Map<K, V> {

    private int size;
    private int delay;

    private Timer timer;
    private List<Entry<K, V>>[] elementList;

    @SuppressWarnings("unchecked")
    public WeakHashMap(int delay, int initialSize) {
        this.delay = delay;
        this.size = initialSize;
        this.timer = new Timer(true);

        elementList = (List<Entry<K, V>>[]) new ArrayList<?>[initialSize];
        for (int i = 0; i < initialSize; i++) {
            elementList[i] = new ArrayList<>();
        }
    }

    private static class Element<K, V> implements Map.Entry<K, V> {
        WeakReference<K> key;
        V value;

        Element(K key, V value) {
            this.key = new WeakReference<>(key);
            this.value = value;
        }

        @Override
        public K getKey() {
            return key.get();
        }

        @Override
        public V getValue() {
            return value;
        }

        @Override
        public V setValue(V value) {
            if (key.get() == null) throw new InvalidStateException("The key has expired (it is null)");

            V temp = this.value;
            this.value = value;

            return temp;
        }

        @Override
        public String toString() {
            if (key.get() != null)
                return ("\n" + "Key: " + key.get().toString() + " Value: " + value.toString());
            else
                return ("\n" + "Key: NULL Value: " + value.toString());
        }
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public V get(Object key) {
        for (List<Entry<K, V>> currentList : elementList) {
            for (Entry<K, V> entry : currentList) {
                if (entry.getKey().equals(key)) return entry.getValue();
            }
        }

        return null;
    }

    @Override
    public boolean containsKey(Object key) {
        return get(key) != null;
    }

    @Override
    public boolean containsValue(Object value) {
        for (List<Entry<K, V>> currentList : elementList) {
            for (Entry<K, V> entry : currentList) {
                if (entry.getValue().equals(value)) return true;
            }
        }

        return false;
    }

    private Entry<K, V> getEntry(Object key) {
        for (List<Entry<K, V>> currentList : elementList) {
            for (Entry<K, V> entry : currentList) {
                if (entry.getKey().equals(key)) return entry;
            }
        }

        return null;
    }

    private List<Entry<K, V>> getBin(Object key) {
        if (key == null)
            throw new IllegalArgumentException("The key cannot be null");

        int hash = key.hashCode() >= 0 ? key.hashCode() : -key.hashCode();

        return elementList[hash % size];
    }

    @Override
    public V put(K key, V value) {
        List<Entry<K, V>> wantedBin = getBin(key);

        timer.schedule(new TimerTask() {
            K tempRef = key;

            @Override
            public void run() {
                tempRef = null;
            }
        }, delay);

        if (containsKey(key)) {
            Entry<K, V> wantedEntry = getEntry(key);

            V tempValue = wantedEntry.getValue();
            wantedEntry.setValue(value);

            return tempValue;
        } else {
            wantedBin.add(new Element<>(key, value));
            return null;
        }
    }

    @Override
    public V remove(Object key) {

        Entry<K, V> tempEntry = getEntry(key);

        if (tempEntry == null) return null;

        V tempValue = tempEntry.getValue();
        getBin(key).remove(tempEntry);

        return tempValue;
    }

    @Override
    public void clear() {
        size = 0;
        Arrays.fill(elementList, null);
    }

    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        m.forEach(this::put);
    }

    @Override
    public Set<K> keySet() {
        HashSet<K> result = new HashSet<>();

        for (List<Entry<K, V>> currentList : elementList)
            for (Entry<K, V> entry : currentList) result.add(entry.getKey());

        return result;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        HashSet<Entry<K, V>> result = new HashSet<>();

        for (List<Entry<K, V>> currentList : elementList)
            result.addAll(currentList);

        return result;
    }

    @Override
    public Collection<V> values() {
        List<V> result = new ArrayList<>();

        for (List<Entry<K, V>> currentList : elementList)
            for (Entry<K, V> entry : currentList) result.add(entry.getValue());

        return result;
    }

    private void removeExpiredElements() {
        for (List<Entry<K, V>> currentList : elementList) {
            List<Entry<K, V>> toBeRemoved = new ArrayList<>();
            for (Entry<K, V> entry : currentList) {
                if (entry.getKey() == null)
                    toBeRemoved.add(entry);
            }
            currentList.removeAll(toBeRemoved);
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("WeekHashMap.WeakHashMap{");
        removeExpiredElements();
        for (List<Entry<K, V>> currentList : elementList)
            for (Entry<K, V> entry : currentList) {
                s.append(entry.toString());
            }

        s.append("}");
        return s.toString();
    }
}
