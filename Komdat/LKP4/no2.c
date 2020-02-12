#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define HOST    "192.30.252.153"
#define PORT    80

int main()
{
    int                 server;
    struct sockaddr_in  sv_addr = {AF_INET, htons(PORT), {inet_addr(HOST)}};
    char                mesg[2];
    char                data[800] = "GET /tutorial-basics.html HTTP/1.0\r\nHost: libdill.org\r\n\r\n"; 

    server = socket(AF_INET, SOCK_STREAM, 0);
    connect(server, (struct sockaddr*)&sv_addr, sizeof sv_addr);

    write(server, data, sizeof data);
	while(read(server, mesg, 1) > 0){
		printf("%s", mesg);
	}
    close(server);
    return 0;
}
