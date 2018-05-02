package Host;


/**
 * Stores data about the user constituent.
 * This class is potentially to expand. In the circumstances of this task it stores only
 * {@linkplain #name}.
 * But we can add here, for instance, birth date, avatar, aboutMe info and so on.
 */
public class UserData extends Data {
    private String name;
    
    private static final long serialVersionUID = 100L;
    
    public UserData(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
}
