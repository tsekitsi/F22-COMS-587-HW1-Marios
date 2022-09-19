import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class ReceiverUDP {
    public static void listen(int LISTENING_PORT) {
        byte[] buffer = new byte[16];
        // Construct empty DatagramPacket object:
        DatagramPacket incoming = new DatagramPacket(buffer, buffer.length);

        try (DatagramSocket dgSocket = new DatagramSocket(LISTENING_PORT)) {
            while (true) {
                // Call DatagramSocket's receive() method:
                dgSocket.receive(incoming);
                // Block thread until a datagram is received:
                byte[] data = incoming.getData();
                // Make a copy of the data array to pass to processor:
                System.arraycopy(incoming.getData(), 0, data, 0, data.length);
                // Pass the data to processor:
                new BeaconProcessor(data).start();
            }
        } catch (SocketException e) {
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        }
    }

    public static void main(String [] args) {
        listen(4444);
    }
}

