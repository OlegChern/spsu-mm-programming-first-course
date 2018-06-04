public class ListElement<T> {

    private T value;
    private ListElement<T> next;
    private ListElement<T> prev;


    ListElement(T obj) {

        this.value = obj;
        this.next = null;
        this.prev = null;

    }

    public T getValue() {

        return value;
    }

    public ListElement<T> getNext() {

        return next;
    }

    public ListElement<T> getPrev() {

        return prev;
    }

    public void setNext(ListElement<T> next) {

        this.next = next;
    }

    public void setPrev(ListElement<T> prev) {

        this.prev = prev;
    }

}
