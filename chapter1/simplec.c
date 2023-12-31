#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in peer;
    int s, rc;
    char buffer[1];

    peer.sin_family         = AF_INET;
    peer.sin_port           = htons(7500);
    peer.sin_addr.s_addr    = inet_addr("127.0.0.1");

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed\n");
        return 1;
    }

    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    if (rc)
    {
        perror("connect call failed\n");
        return 1;
    }

    rc = send(s, "1", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed\n");
        return 1;
    }

    rc = recv(s, buffer, sizeof(buffer), 0);
    if (rc <= 0)
    {
        perror("recv call failed\n");
        return 1;
    }
    printf("%c\n", buffer[0]);
    return 0;
}