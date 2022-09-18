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
    char buf[1000];

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
        beacon.IP[i] = 1;
    }

    strcpy(buf, "Hello");

    // Send the message in buf to the server:
    if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&udpServer, sizeof(udpServer)) < 0) {
        perror("sendto()");
        exit(2);
    }

    // Deallocate the socket:
    close(s);
    return 0;
}
