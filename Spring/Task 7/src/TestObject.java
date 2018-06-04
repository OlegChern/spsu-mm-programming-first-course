public class TestObject {

    private String testString;

    TestObject(String str) {
        testString = str;
    }

    @Override
    public String toString() {
        return testString;
    }
}
