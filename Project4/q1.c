#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define HOST "140.113.207.245"
#define PORT 30170
#define PASSWORD "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    // 建立 Socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(HOST);

    // 連線到伺服器
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // 讀取伺服器回應
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("%s", buffer);

    // 傳送密碼
    send(sock, PASSWORD "\n", strlen(PASSWORD) + 1, 0);

    // 讀取伺服器回應
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("%s", buffer);

    // 關閉 Socket
    close(sock);

    return 0;
}
