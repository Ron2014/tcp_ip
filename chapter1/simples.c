#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in local, target;
    int s, s1, rc;
    char buffer[1];

    local.sin_family         = AF_INET;
    local.sin_port           = htons(7500);
    local.sin_addr.s_addr    = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed\n");
        return 1;
    }

    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    if (rc < 0)
    {
        perror("bind call failed\n");
        return 1;
    }

    rc = listen(s, 5);
    if (rc)
    {
        perror("listen call failed\n");
        return 1;
    }

    int targetlen = sizeof(target);
    s1 = accept(s, (struct sockaddr *)&target, &targetlen);
    if (s1 < 0)
    {
        perror("accept call failed\n");
        return 1;
    }

    if (targetlen > 0)
    {
        printf("accept from %s\n", inet_ntoa(target.sin_addr));
    }

    rc = recv(s1, buffer, sizeof(buffer), 0);
    if (rc <= 0)
    {
        perror("recv call failed\n");
        return 1;
    }
    printf("%c\n", buffer[0]);

    rc = send(s1, "2", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed\n");
        return 1;
    }

    return 0;
}