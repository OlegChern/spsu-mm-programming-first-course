import java.util.Objects;

class TestObject {
    private int i;
    
    public TestObject(int i) {
        this.i = i;
    }
    
    @Override
    public String toString() {
        return "TestObject{" + i + "}";
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        TestObject that = (TestObject) o;
        return i == that.i;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(i);
    }
}
