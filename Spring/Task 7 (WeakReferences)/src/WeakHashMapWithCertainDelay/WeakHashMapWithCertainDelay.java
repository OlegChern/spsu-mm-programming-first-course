package WeakHashMapWithCertainDelay;

import java.lang.ref.WeakReference;
import java.util.*;
import java.util.function.Consumer;


public class WeakHashMapWithCertainDelay<K, V> implements Map<K, V> {
    
    private static final int DEFAULT_INITIAL_CAPACITY = 8;
    
    private int size = 0;
    
    private int delay = 0;
    
    private List<Entry<K, V>>[] map;
    
    private Timer timer = new Timer(true);
    
    @SuppressWarnings("unchecked")
    public WeakHashMapWithCertainDelay(int delay, int initialCapacity) {
        if (delay < 0) {
            throw new IllegalArgumentException("Delay must not be negative, given delay: " + delay);
        }
        if (initialCapacity < 0) {
            throw new IllegalArgumentException("InitialCapacity must not be negative, given initialCapacity: " + initialCapacity);
        }
        
        this.delay = delay;
        this.map = (List<Entry<K, V>>[]) new LinkedList<?>[initialCapacity];
        for (int i = 0; i < initialCapacity; i++) {
            this.map[i] = new LinkedList<>();
        }
    }
    
    public WeakHashMapWithCertainDelay(int delay) {
        this(delay, DEFAULT_INITIAL_CAPACITY);
    }
    
    private static class Node<K, V> implements Map.Entry<K, V> {
        WeakReference<K> key;
        V value;
    
        public Node(K key, V value) {
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
            if (key == null) {
                throw new NotActualStateException("Entry is not actual anymore: the key is null");
            }
            
            V old = this.value;
            this.value = value;
            
            return old;
        }
        
        public boolean isActual() {
            return key != null;
        }
    
        @Override
        public String toString() {
            return "{key=" + key.get() + ",value=" + value + "}";
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
    public boolean containsKey(Object key) {
        return get(key) != null;
    }
    
    private List<Entry<K, V>> getBin(Object key) {
        if (key == null) {
            throw new IllegalArgumentException("Null keys are prohibited");
        }
    
        int hash = key.hashCode() % map.length;
        return map[hash];
    }
    
    private Iterator<Entry<K, V>> getNodeIteratorInBin(List<Entry<K, V>> bin, Object key) {
        for (ListIterator<Entry<K, V>> iterator = bin.listIterator(); iterator.hasNext(); ) {
            Entry<K, V> entry = iterator.next();
            
            
            if (entry.getKey() == null) { // it has been already discarded by GC
                iterator.remove();
            } else if (entry.getKey().equals(key)) {
                iterator.previous();
                return iterator;
            }
        }
        
        return null;
    }
    
    @Override
    public boolean containsValue(Object value) {
        for (List<Entry<K, V>> list : map) {
            for (Entry<K, V> entry : list) {
                if (entry.getValue() == null) {
                    if (value == null) {
                        return true;
                    }
                } else if (entry.getValue().equals(value)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    @Override
    public V get(Object key) {
        Iterator<Entry<K, V>> nodeIterator = getNodeIteratorInBin(getBin(key), key);
        return nodeIterator == null ? null : nodeIterator.next().getValue();
    }
    
    @Override
    public V put(K key, V value) {
        List<Entry<K, V>> bin = getBin(key);
        Iterator<Entry<K, V>> nodeIterator = getNodeIteratorInBin(bin, key);
        
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                // this simple line will store strong link until the task execution
                K temp = key;
            }
        }, delay);
        
        if (nodeIterator == null) {
            bin.add(new Node<>(key, value));
            return null;
        }
        
        Entry<K, V> node = nodeIterator.next();
        V oldValue = node.getValue();
        node.setValue(value);
        
        return oldValue;
    }
    
    @Override
    public V remove(Object key) {
        Iterator<Entry<K, V>> nodeIterator = getNodeIteratorInBin(getBin(key), key);
    
        if (nodeIterator == null) {
            return null;
        }
    
        V oldValue = nodeIterator.next().getValue();
        nodeIterator.remove();
    
        return oldValue;
    }
    
    @Override
    public void putAll(Map<? extends K, ? extends V> m) {
        m.forEach(this::put);
    }
    
    @Override
    public void clear() {
        size = 0;
        Arrays.fill(map, null);
    }
    
    private void iterateAllEntries(Consumer<Entry<K, V>> consumer) {
        for (List<Entry<K, V>> bin : map) {
            for (Iterator<Entry<K, V>> iterator = bin.iterator(); iterator.hasNext(); ) {
                Entry<K, V> entry = iterator.next();
            
                if (entry.getKey() == null) {
                    iterator.remove();
                } else {
                    consumer.accept(entry);
                }
            }
        }
    }
    
    @Override
    public Set<K> keySet() {
        HashSet<K> result = new HashSet<>();
        iterateAllEntries(e -> result.add(e.getKey()));
        return result;
    }
    
    @Override
    public Collection<V> values() {
        List<V> result = new ArrayList<>();
        iterateAllEntries(e -> result.add(e.getValue()));
        return result;
    }
    
    @Override
    public Set<Entry<K, V>> entrySet() {
        HashSet<Entry<K, V>> result = new HashSet<>();
        iterateAllEntries(result::add);
        return result;
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("WeakMap{");
        iterateAllEntries(sb::append);
        sb.append("}");
        return sb.toString();
    }
}