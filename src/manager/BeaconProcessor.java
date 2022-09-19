public class BeaconProcessor extends Thread {
    public byte[] rawData;

    public BeaconProcessor(byte[] data) {
        rawData = data;
    }

    public void reconstructDataFromBytes() {
        // The ID:
        int ID = (rawData[0] & 0xFF) + ((rawData[1] & 0xFF) << 8) + ((rawData[2] & 0xFF) << 16) + ((rawData[3] & 0xFF) << 24);
        // The StartUpTime:
        int StartUpTime = (rawData[4] & 0xFF) + ((rawData[5] & 0xFF) << 8) + ((rawData[6] & 0xFF) << 16) + ((rawData[7] & 0xFF) << 24);
        // The IP:
        char[] IP = {(char)(rawData[8] & 0xFF), (char)(rawData[9] & 0xFF), (char)(rawData[10] & 0xFF), (char)(rawData[11] & 0xFF) };
        // The CmdPort:
        int CmdPort = (rawData[12] & 0xFF) + ((rawData[13] & 0xFF) << 8) + ((rawData[14] & 0xFF) << 16) + ((rawData[15] & 0xFF) << 24);
        System.out.println(ID);
        System.out.println(StartUpTime);
        System.out.printf("%d.%d.%d.%d\n", (byte)IP[0], (byte)IP[1], (byte)IP[2], (byte)IP[3]);
        System.out.println(CmdPort);
    }

    public void run() {
        reconstructDataFromBytes();
    }
}
