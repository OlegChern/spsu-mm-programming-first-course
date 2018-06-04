package Chat;

import java.util.EventListener;

public interface MessageListener extends EventListener {

    void messageProcessing(MessageEvent event);
}
