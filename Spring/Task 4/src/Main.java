public class Main {

    public static void main(String[] argv) {

        String test = "Test string!";
        String testEnd = "Testing addition to the end ";
        String testHead = "Testing addition to the head ";

        List<String> testList = new List<>(test);

        for (int i = 1; i < 6; i++) {
            String addTest = testEnd.concat(Integer.toString(i));
            testList.addToEnd(addTest);
        }

        for (int i = 1; i < 6; i++) {
            String addTest = testHead.concat(Integer.toString(i));
            testList.addToHead(addTest);
        }

        System.out.println("Initial state of the list:\n");
        testList.listPrint();

        String deleteTest1 = testHead.concat(Integer.toString(2));
        String deleteTest2 = testEnd.concat(Integer.toString(3));

        testList.deleteElement(deleteTest1);
        testList.deleteElement(deleteTest2);

        System.out.println("\nAfter some elements were deleted:\n");
        testList.listPrint();


        System.out.println("\nNow Searching for the test string\n");
        if (testList.searchElement(test)) {
            System.out.println("Element found!");
        }
    }
}
