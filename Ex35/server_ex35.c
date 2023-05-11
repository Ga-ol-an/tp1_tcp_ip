#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

#define SERVER_PORT 54321
#define MAX_PENDING 5
#define MAX_LINE 256

/* Rode esse em um terminal e o client em outro.

para rodar esse, é só digitar:

    ./server_ex35


p/ compliar e rodar:

    gcc server_ex35.c -o server_ex35 && ./server_ex35

 */

int main() {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int buf_len, addr_len;
    int s, new_s;

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /* setup passive open */
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }
    /* receive and print text */
    addr_len = sizeof(sin);

    while (buf_len = recv(s, buf, sizeof(buf), 0)) { 
        fputs(buf, stdout);
    }
    close(s);
}