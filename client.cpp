
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8765 //サーバープログラムとポート番号を合わせてください

int main() {
        // IP アドレス，ポート番号，ソケット構造体
        char destination[32];
        int dstSocket;
        struct sockaddr_in dstAddr;

        // 各種パラメータ
        char buffer[1024];

        // Windows の場合
        WSADATA data;
        WSAStartup(MAKEWORD(2,0), &data);

        // 相手先アドレスの入力と送る文字の入力
        std::cout << "input IP Adress:"<< std::endl;
        scanf("%s", destination);

        // sockaddr_in 構造体のセット
        memset(&dstAddr, 0, sizeof(dstAddr));
        dstAddr.sin_port = htons(PORT);
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_addr.s_addr = inet_addr(destination);

        // ソケットの生成
        dstSocket = socket(AF_INET, SOCK_STREAM, 0);

        //接続
        if(connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr))) {
                std::cout << "Conection Failed" <<destination <<std::endl;
                return(-1);
        }
        std::cout << destination << " to connected\n" << std::endl;
        std::cout << "input Character\n" << std::endl;

        //データ送信ループ
        while (1) {
                std::cin >>buffer;
                //パケットの送信
                send(dstSocket, buffer, 1024, 0);
                std::cout << buffer <<std::endl;
        }

        // Windows でのソケットの終了
        closesocket(dstSocket);
        WSACleanup();
        return(0);
}
