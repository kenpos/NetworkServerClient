#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ctype.h>

#define PORT 9876 //クライアントプログラムとポート番号を合わせてください

int main() {
        int i;
        // ポート番号，ソケット
        int srcSocket; // 自分
        int dstSocket; // 相手

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
        memset(&srcAddr, 0, sizeof(srcAddr));
        srcAddr.sin_port = htons(PORT);
        srcAddr.sin_family = AF_INET;
        srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        // ソケットの生成（ストリーム型）
        srcSocket = socket(AF_INET, SOCK_STREAM, 0);
        // ソケットのバインド
        bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));
        // 接続の許可
        listen(srcSocket, 1);

        while(1) { //ループで回すことによって何度でもクライアントからつなぐことができる

                // 接続の受付け
                printf("接続を待っています\nクライアントプログラムを動かしてください\n");
                dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
                printf("%s から接続を受けました\n", inet_ntoa(dstAddr.sin_addr));

                while(1) {
                        //パケットの受信
                        numrcv = recv(dstSocket, buffer, sizeof(char)*1024, 0);
                        if(numrcv ==0 || numrcv ==-1 ) {
                                status = closesocket(dstSocket); break;
                        }
                        printf("変換前 %s",buffer);
                        for (i=0; i< numrcv; i++) { // bufの中の小文字を大文字に変換
                                //if(isalpha(buffer[i]))
                                buffer[i] = toupper(buffer[i]);
                        }
                        // パケットの送信
                        //send(dstSocket, buffer, sizeof(char)*1024, 0);
                        //printf("→ 変換後 %s \n",buffer);
                }
        }
        // Windows での終了設定
        WSACleanup();

        return(0);
}
