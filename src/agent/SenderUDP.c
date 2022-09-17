// https://www.ibm.com/docs/en/zos/2.3.0?topic=programs-c-socket-udp-client
// https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm
// https://www.studytonight.com/c/compile-and-run-c-program.php

#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
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

/**
 * Converts a string of an IP address to a char[4] array.
 * Source: https://stackoverflow.com/a/9212551.
 * @param String IpAddress The string representation of the IP address we want parsed (e.g. "38.89.40.1").
 * @return The IP address as a char[4] array.
 */
char *parseIpAddress(char *IpAddress) {
    static char result[4] = {0}; // https://stackoverflow.com/a/18041130
    size_t index = 0;

    while (*IpAddress) {
        if (isdigit((unsigned char)*IpAddress)) {
            result[index] *= 10;
            result[index] += *IpAddress - '0';
        } else {
            index++;
        }
        IpAddress++;
    }

    return result;
}

int main(int argc, char *argv[]) {
    int s;
    struct sockaddr_in udpServer;
    char buf[32];

    // Read args:
    char *ipOfUDPServer  = parseIpAddress(argv[1]); // https://www.educative.io/answers/splitting-a-string-using-strtok-in-c
    int  portOfUDPServer = atoi(argv[2]);           // https://www.tutorialspoint.com/cprogramming/c_type_casting.htm

    // Instantiate beacon:
    struct BEACON beacon;              // https://www.programiz.com/c-programming/c-structures
    beacon.ID          = 7;
    beacon.StartUpTime = 1663432187;   // "unix time"
    beacon.CmdPort     = 2336;
    for(int i = 0; i < 4; i++) {
        beacon.IP[i] = 1;
    }

    // Create a datagram socket in the internet domain and use the default protocol (UDP):
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket()");
        exit(1);
    }

    // Set up the server name:
    udpServer.sin_family      = AF_INET;
    udpServer.sin_port        = htons(portOfUDPServer);
    udpServer.sin_addr.s_addr = inet_addr(ipOfUDPServer);

    strcpy(buf, "Hello");

    // Send the message in buf to the server:
    if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&udpServer, sizeof(udpServer)) < 0) {
        perror("sendto()");
        exit(2);
    }

    /* Deallocate the socket */
    close(s);

    /*
    // Print for proof:
    printf("%d\n", beacon.ID);
    printf("%d\n", beacon.StartUpTime);
    for( int i = 0; i < 3; i++ ){
        printf("%d.", beacon.IP[i]);
    }
    printf("%d\n", beacon.IP[3]);
    printf("%d\n", beacon.CmdPort);

    return 0;
    */
}
