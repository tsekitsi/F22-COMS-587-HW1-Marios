package manager;

public class BeaconListener extends Thread {
    public int LISTENING_PORT;

    public BeaconListener(int port) {
        LISTENING_PORT = port;
    }

    public void run() {
        new ReceiverUDP().listen(LISTENING_PORT);
    }
}
