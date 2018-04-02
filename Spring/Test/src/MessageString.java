public class MessageString extends Message {

    private String mess;
    private String formatMess;

    public void format() {

        if (mess.length() % 2 == 0) {
            formatMess = ("++" + mess + "++");
        } else {
            formatMess = ("--" + mess + "--");
        }
    }

    public void printMess() {

        if (formatMess != null)
            System.out.println("Formatted string: " + formatMess);
    }

    public MessageString(String mess) {
        this.mess = mess;
        formatMess = null;
    }


}
