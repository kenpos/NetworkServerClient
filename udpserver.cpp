#include <iostream>
#include <winsock2.h>

int
main()
{
        WSAData wsaData;

        SOCKET sock;
        struct sockaddr_in addr;

        char buf[2048];
        int numrcv;
        int status;
        WSAStartup(MAKEWORD(2,0), &wsaData);

        sock = socket(AF_INET, SOCK_DGRAM, 0);

        addr.sin_family = AF_INET;
        addr.sin_port = htons(12345);
        addr.sin_addr.S_un.S_addr = INADDR_ANY;

        bind(sock, (struct sockaddr *)&addr, sizeof(addr));

        while(1) {
                memset(buf, 0, sizeof(buf));

                numrcv = recv(sock, buf, sizeof(buf), 0);
                if(numrcv ==0 || numrcv ==-1 ) {
                        status = closesocket(sock); break;
                }
                std::cout <<buf << std::endl;
        }


        WSACleanup();

        return 0;
}
