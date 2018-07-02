import java.security.Key;

public class LinkedList <KeyType, ValueType> {
    private Node<KeyType, ValueType> head;

    LinkedList() {
        head = null;
    }

    public Node<KeyType, ValueType> getHead() {
        return head;
    }

    public void setHead(Node<KeyType, ValueType> head) {
        this.head = head;
    }

    public void addToBegin(KeyType key, ValueType value) {
        Node<KeyType, ValueType> tmp = head;
        boolean flag = false;
        while (tmp != null) {
            if (tmp.getKey() == key) {
                tmp.setValue(value);
                flag = true;
                break;
            } else {
                tmp = tmp.getNext();
            }
        }
        if (!flag) {
            tmp = head;
            head = new Node<>(key, value);
            head.setNext(tmp);
        }
    }

    public boolean deleteByKey(KeyType key) {
        Node<KeyType, ValueType> tmp = head;
        if (tmp != null && tmp.getKey() == key) {
            head = tmp.getNext();
            return true;
        } else {
            while (tmp != null && tmp.getNext() != null) {
                if (tmp.getNext().getKey() == key) {
                    tmp.setNext(tmp.getNext().getNext());
                    return true;
                } else {
                    tmp = tmp.getNext();
                }
            }
            return false;
        }
    }

    public ValueType findByKey(KeyType key) {
        Node<KeyType, ValueType> tmp = head;
        while (tmp != null) {
            if (tmp.getKey() == key) {
                return tmp.getValue();
            } else {
                tmp = tmp.getNext();
            }
        }
        return null;
    }


}