#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    "38.109.180.24"
#define PORT    80

int main()
{
    int                 server;
    struct sockaddr_in  sv_addr = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    char                mesg[800];
    char                data[800] = "GET / HTTP/1.0\r\nHost: defmacro.com\r\n\r\n"; 

    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);

    
    write(server, data, sizeof data);
    read(server, mesg, sizeof mesg);
    printf("%s", mesg);

    close(server);
    return 0;
}
