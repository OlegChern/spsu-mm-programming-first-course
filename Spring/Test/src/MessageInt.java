public class MessageInt extends Message {

    private Integer mess;
    private String formatMess;

    public void format() {

        if (mess % 2 == 0) {
            mess++;
            formatMess = mess.toString();
        } else {
            mess += 2;
            formatMess = mess.toString();
        }
    }

    public void printMess() {

        System.out.println("Formated integer: " + formatMess);
    }

    public MessageInt(Integer mess) {
        this.mess = mess;
        formatMess = null;
    }

}
