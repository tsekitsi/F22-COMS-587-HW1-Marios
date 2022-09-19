#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct BEACON {
    int  ID;          // randomly generated during startup
    int  StartUpTime; // the time when the client starts
    char IP[4];       // the IP address of this client
    int  CmdPort;     // the client listens to this port for cmd
};

int main(int argc, char *argv[]) {
    int s;
    struct sockaddr_in udpServer;
    int8_t buf[16]; // (8 bytes for the header) 16 bytes for the payload.

    // Convert IP address from string to in_addr_t:
    in_addr_t ipOfUDPServerAsInAddrT;
    int rVal;
    if ( (rVal = inet_pton(AF_INET, argv[1], &ipOfUDPServerAsInAddrT)) == 0) {
        printf("Invalid address: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    } else if (rVal == -1) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    } // http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fi%2Finet_pton.html

    // Create a datagram socket in the internet domain and use the default protocol (UDP):
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }

    // Set up the server name:
    udpServer.sin_family      = AF_INET;
    udpServer.sin_port        = htons(atoi(argv[2]));   // the UDP server port is expected to be the second argument.
    udpServer.sin_addr.s_addr = ipOfUDPServerAsInAddrT;

    // Instantiate beacon:
    struct BEACON beacon;
    beacon.ID          = 7;
    beacon.StartUpTime = 1663432187;
    beacon.CmdPort     = 2336;
    for(int i = 0; i < 4; i++) {
        beacon.IP[i] = i+1;
    }

    // Load buf:
    // The ID:
    buf[0] = beacon.ID & 0xFF;
    buf[1] = (beacon.ID >> 8) & 0xFF;
    buf[2] = (beacon.ID >> 16) & 0xFF;
    buf[3] = (beacon.ID >> 24) & 0xFF;
    // The StartUpTime:
    buf[4] = beacon.StartUpTime & 0xFF;
    buf[5] = (beacon.StartUpTime >> 8) & 0xFF;
    buf[6] = (beacon.StartUpTime >> 16) & 0xFF;
    buf[7] = (beacon.StartUpTime >> 24) & 0xFF;
    // The IP:
    buf[8]  = beacon.IP[0];
    buf[9]  = beacon.IP[1];
    buf[10] = beacon.IP[2];
    buf[11] = beacon.IP[3];
    // The CmdPort:
    buf[12] = beacon.CmdPort & 0xFF;
    buf[13] = (beacon.CmdPort >> 8) & 0xFF;
    buf[14] = (beacon.CmdPort >> 16) & 0xFF;
    buf[15] = (beacon.CmdPort >> 24) & 0xFF;

    // Send the message in buf to the server:
    if (sendto(s, buf, sizeof(buf), 0, (struct sockaddr *)&udpServer, sizeof(udpServer)) < 0) {
        perror("sendto()");
        exit(2);
    }

    // Deallocate the socket:
    close(s);
    return 0;
}
