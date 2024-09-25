#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ERROR 1
#define REQUIRED_ARGC 3
#define HOST_POS 1
#define PORT_POS 2
#define PROTOCOL "tcp"
#define BUFLEN 1024

void usage(const char *progname) {
    std::cerr << "usage: " << progname << " host port" << std::endl;
    exit(ERROR);
}

void errexit(const char *format, const char *arg) {
    std::cerr << format << arg << std::endl;
    exit(ERROR);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in sin;
    struct hostent *hinfo;
    struct protoent *protoinfo;
    char buffer[BUFLEN];
    int sd, ret;

    if (argc != REQUIRED_ARGC) {
        usage(argv[0]);
    }

    /* lookup the hostname */
    hinfo = gethostbyname(argv[HOST_POS]);
    if (hinfo == nullptr) {
        errexit("cannot find name: %s", argv[HOST_POS]);
    }

    /* set endpoint information */
    memset(&sin, 0x0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[PORT_POS]));
    memcpy(&sin.sin_addr, hinfo->h_addr, hinfo->h_length);

    if ((protoinfo = getprotobyname(PROTOCOL)) == nullptr) {
        errexit("cannot find protocol information for %s", PROTOCOL);
    }

    /* allocate a socket */
    sd = socket(PF_INET, SOCK_STREAM, protoinfo->p_proto);
    if (sd < 0) {
        errexit("cannot create socket", nullptr);
    }

    /* connect the socket */
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        errexit("cannot connect", nullptr);
    }

    /* snarf whatever server provides and print it */
    memset(buffer, 0x0, BUFLEN);
    ret = read(sd, buffer, BUFLEN - 1);
    if (ret < 0) {
        errexit("reading error", nullptr);
    }
    std::cout << buffer << std::endl;

    /* close & exit */
    close(sd);
    return 0;
}
