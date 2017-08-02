#include <winsock2.h>
#include <iostream>

int
main()
{
        WSAData wsaData;

        SOCKET sock;
        struct sockaddr_in addr;
        char buffer[1024];
        const int MAX_WORD = 1024;

        WSAStartup(MAKEWORD(2,0), &wsaData);

        sock = socket(AF_INET, SOCK_DGRAM, 0);

        addr.sin_family = AF_INET;
        addr.sin_port = htons(12345);
        addr.sin_addr.S_un.S_addr = inet_addr("192.168.11.3");

        while(1) {
                std::cin >>buffer;
                sendto(sock, buffer, MAX_WORD, 0, (struct sockaddr *)&addr, sizeof(addr));
        }
        closesocket(sock);

        WSACleanup();

        return 0;
}
