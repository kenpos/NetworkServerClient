#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctype.h>

#include <iostream>

#define PORT 8765 //クライアントプログラムとポート番号を合わせてください

int main(int argc, char const *argv[]) {
        int i;
// ポート番号，ソケット
        int srcSocket; // 自分のソケット
        int dstSocket; // 相手のソケット

// sockaddr_in 構造体
        struct sockaddr_in srcAddr;
        struct sockaddr_in dstAddr;
        int dstAddrSize = sizeof(dstAddr);
        int status;
// 各種パラメータ
        int numrcv;
        char buffer[1024];

// Windows の場合
        WSADATA data;
        WSAStartup(MAKEWORD(2,0), &data);
// sockaddr_in 構造体のセット
        memset(&srcAddr, 0, sizeof(srcAddr));//0で埋めるらしい
        srcAddr.sin_port = htons(PORT);
        srcAddr.sin_family = AF_INET;
        srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

// ソケットの生成（ストリーム型）
        srcSocket = socket(AF_INET, SOCK_STREAM, 0);
// ソケットのバインド
        bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));
// 接続の許可
        listen(srcSocket, 1);

        while(1) {
                // 接続の受付け
                std::cout <<"wait connecting" << std::endl;
                //ソケットに関する新規接続の受け入れ
                dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
                //ネットワークバイトオーダで渡されたインターネットホストアドレスをIPv4 のドット区切りの 10 進数表記の文字列に変換
                std::cout << inet_ntoa(dstAddr.sin_addr)<< std::endl;

                while(1) {
                        //パケットの受信
                        numrcv = recv(dstSocket, buffer, sizeof(char)*1024, 0);
                        if(numrcv ==0 || numrcv ==-1 ) {
                                status = closesocket(dstSocket); break;
                        }
                        std::cout << buffer << std::endl;
                }
        }
// Windows での終了設定
        WSACleanup();

        return(0);
}
