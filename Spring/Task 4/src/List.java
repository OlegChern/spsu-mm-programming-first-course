public class List<T> {

    private ListElement<T> head;
    private ListElement<T> last;

    List(T obj) {
        head = new ListElement<T>(obj);
        last = head;
    }

    List() {
        head = null;
        last = null;
    }

    public void addToEnd(T obj) {

        ListElement<T> newElem = new ListElement<>(obj);
        ListElement<T> temp = last;

        last.setNext(newElem);
        last = last.getNext();
        last.setPrev(temp);

    }

    public void addToHead(T obj) {

        ListElement<T> newElem = new ListElement<>(obj);
        ListElement<T> temp = head;

        head.setPrev(newElem);
        head = head.getPrev();
        head.setNext(temp);

    }

    public boolean deleteElement(T obj) {

        if (head == null) return false;

        if (last.getValue().equals(obj)) {
            last = last.getPrev();
            last.setNext(null);
            return true;
        }

        ListElement<T> temp = head;

        while (temp != last) {

            if (temp.getValue().equals(obj)) {

                if (temp.getPrev() != null) {

                    ListElement<T> tempPrev = temp.getPrev();
                    ListElement<T> tempNext = temp.getNext();

                    tempPrev.setNext(tempNext);
                    tempNext.setPrev(tempPrev);

                    return true;
                }

                ListElement<T> tempHead = temp.getNext();

                head = tempHead;
                tempHead.setPrev(null);

                return true;
            }

            temp = temp.getNext();
        }

        return false;
    }

    public boolean searchElement(T obj) {

        if (head == null) return false;

        if (last.getValue().equals(obj)) {
            return true;
        }

        ListElement<T> temp = head;

        while (temp != last) {

            if (temp.getValue().equals(obj)) {
                return true;
            }

            temp = temp.getNext();
        }

        return false;
    }

    public void listPrint() {

        ListElement<T> temp = head;

        if (temp == null) return;

        while (temp != null) {

            System.out.println(temp.getValue().toString());
            temp = temp.getNext();

        }
    }
}
