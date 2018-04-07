package vector;

import com.sun.istack.internal.NotNull;

import java.util.*;

public class Vector<T> implements List<T> {
    private Object[] elements;
    private int size = 0;

    private static final int MINIMUM_CAPACITY = 8;
    private static final int DEFAULT_CAPACITY = 16;

    private class Itr implements Iterator<T> {
        int next = 0;
        int lastReturned = -1;

        @Override
        public boolean hasNext() {
            return next < size;
        }

        @Override
        public T next() {
            if (next >= size) {
                throw new NoSuchElementException();
            }

            lastReturned = next;
            return (T) elements[next++];
        }

        @Override
        public void remove() {
            if (lastReturned == -1) {
                throw new IllegalStateException();
            }

            Vector.this.remove(lastReturned);
            next = lastReturned;
            lastReturned = -1;
        }
    }

    private class ListItr extends Itr implements ListIterator<T> {
        ListItr(int index) {
            super();

            checkIndex(index);
            next = index;
        }

        @Override
        public boolean hasPrevious() {
            return next > 0;
        }

        @Override
        public T previous() {
            if (next == 0) {
                throw new NoSuchElementException();
            }

            lastReturned = next - 1;
            return (T) elements[--next];
        }

        @Override
        public int nextIndex() {
            return next;
        }

        @Override
        public int previousIndex() {
            return next - 1;
        }

        @Override
        public void set(T t) {
            if (lastReturned == -1) {
                throw new IllegalStateException();
            }

            Vector.this.set(lastReturned, t);
        }

        @Override
        public void add(T t) {
            Vector.this.add(next++, t);
            lastReturned = -1;
        }
    }

    public Vector(int capacity) {
        if (capacity < 0) {
            throw new IllegalArgumentException("Capacity must be non-negative");
        }

        elements = new Object[Math.max(capacity, MINIMUM_CAPACITY)];
    }

    public Vector() {
        this(DEFAULT_CAPACITY);
    }

    public Vector(@NotNull T[] a) {
        elements = Arrays.copyOf(a, a.length);
    }

    public Vector(@NotNull Collection<? extends T> collection) {
        elements = collection.toArray();
    }

    public void resize(int capacity) {
        if (capacity < 0) {
            throw new IllegalArgumentException("Capacity must be non-negative");
        }

        elements = Arrays.copyOf(elements, Math.max(capacity, MINIMUM_CAPACITY));
    }

    private void checkIndex(int index) {
        if (!(0 <= index && index < size)) {
            throw new IndexOutOfBoundsException("Index: " + index + ", size: " + size);
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
    public boolean contains(Object o) {
        for (int i = 0; i < size; i++) {
            if (elements[i] == null && o == null || elements[i] != null && elements[i].equals(o)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public Object[] toArray() {
        return Arrays.copyOf(elements, size);
    }

    @Override
    public <E> E[] toArray(@NotNull E[] a) {
        if (a == null) {
            throw new NullPointerException();
        }

        if (size <= a.length) {
            System.arraycopy(elements, 0, a, 0, size);
            if (size < a.length) {
                a[size] = null;
            }
            return a;
        }

        return Arrays.copyOf(elements, size, (Class<? extends E[]>) a.getClass());
    }

    @Override
    public boolean add(T t) {
        if (size >= elements.length) {
            resize(size < Integer.MAX_VALUE / 2 ? size * 2 : Integer.MAX_VALUE);
        }

        elements[size++] = t;
        return true;
    }

    @Override
    public boolean remove(Object o) {
        if (o == null) {
            for (int i = 0; i < size; i++) {
                if (elements[i] == null) {
                    remove(i);
                    return true;
                }
            }
        } else {
            for (int i = 0; i < size; i++) {
                if (elements[i] != null && elements[i].equals(o)) {
                    remove(i);
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public boolean containsAll(@NotNull Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        for (Object o : c) {
            boolean result = false;
            for (int i = 0; i < size; i++) {
                result |= (elements[i] == null && o == null || elements[i] != null && elements[i].equals(o));
            }

            if (!result) {
                return false;
            }
        }

        return true;
    }

    @Override
    public boolean addAll(@NotNull Collection<? extends T> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        for (T t : c) {
            add(t);
        }

        return !c.isEmpty();
    }

    @Override
    public boolean addAll(int index, @NotNull Collection<? extends T> c) {
        checkIndex(index);

        if (c == null) {
            throw new NullPointerException();
        }

        if (c.isEmpty()) {
            return false;
        }

        if (size > Integer.MAX_VALUE - c.size()) {
            throw new IllegalArgumentException("Too much adding values to store in one array");
        }

        if (size + c.size() > elements.length) {
            resize(size + c.size());
        }

        System.arraycopy(elements, index, elements, index + c.size(), size - index);
        for (T t : c) {
            elements[index++] = t;
        }
        size = elements.length;
        return true;
    }

    @Override
    public boolean removeAll(@NotNull Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        boolean wasModified = false;
        for (Object o : c) {
            for (int i = 0; i < size; i++) {
                if (elements[i] == null && o == null || elements[i] != null && elements[i].equals(o)) {
                    wasModified = true;
                    remove(i);
                }
            }
        }

        return wasModified;
    }

    @Override
    public boolean retainAll(@NotNull Collection<?> c) {
        if (c == null) {
            throw new NullPointerException();
        }

        boolean wasModified = false;
        for (Object o : c) {
            for (int i = 0; i < size; i++) {
                if (!(elements[i] == null && o == null || elements[i] != null && elements[i].equals(o))) {
                    wasModified = true;
                    remove(i);
                }
            }
        }

        return wasModified;
    }

    @Override
    public void clear() {
        elements = new Object[DEFAULT_CAPACITY];
        size = 0;
    }

    @Override
    public T get(int index) {
        checkIndex(index);

        return (T) elements[index];
    }

    @Override
    public T set(int index, T element) {
        checkIndex(index);

        T oldValue = (T) elements[index];
        elements[index] = element;
        return oldValue;
    }

    @Override
    public void add(int index, T element) {
        if (size == elements.length) {
            resize(size < Integer.MAX_VALUE / 2 ? size * 2 : Integer.MAX_VALUE);
        }

        System.arraycopy(elements, index, elements, index + 1, size - index);
        size++;
        elements[index] = element;
    }

    @Override
    public T remove(int index) {
        checkIndex(index);

        T result = (T) elements[index];
        System.arraycopy(elements, index + 1, elements, index, size - index - 1);
        elements[--size] = null;

        return result;
    }

    @Override
    public int indexOf(Object o) {
        if (o == null) {
            for (int i = 0; i < size; i++) {
                if (elements[i] == null) {
                    return i;
                }
            }
        } else {
            for (int i = 0; i < size; i++) {
                if (elements[i] != null && elements[i].equals(o)) {
                    return i;
                }
            }
        }
        return -1;
    }

    @Override
    public int lastIndexOf(Object o) {
        if (o == null) {
            for (int i = size - 1; i >= 0; i--) {
                if (elements[i] == null) {
                    return i;
                }
            }
        } else {
            for (int i = size - 1; i >= 0; i--) {
                if (elements[i] != null && elements[i].equals(o)) {
                    return i;
                }
            }
        }
        return -1;
    }

    @Override
    public Iterator<T> iterator() {
        return new Itr();
    }

    @Override
    public ListIterator<T> listIterator() {
        return new ListItr(0);
    }

    @Override
    public ListIterator<T> listIterator(int index) {
        return new ListItr(index);
    }

    @Override
    public List<T> subList(int fromIndex, int toIndex) {
        throw new UnsupportedOperationException();
    }

    @Override
    public String toString() {
        return Arrays.deepToString(Arrays.copyOf(elements, size));
    }
}
