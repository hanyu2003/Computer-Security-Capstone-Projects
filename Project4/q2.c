#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define HOST "140.113.207.245"
#define PORT 30171

unsigned int long_secure_random() {
    srand(time(NULL));
    unsigned int r[100];

    for (int i = 0; i < 100; i++) {
        r[i] = rand() % 32323;
    }

    for (int i = 1; i < 100; i++) {
        r[i] = r[i] * r[i - 1] * r[i - 1] * r[i - 1] + 
               r[i] * r[i - 1] * r[i - 1] * 3 + 
               r[i] * r[i - 1] * 2 + r[i];
    }


    return r[99];
}

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    unsigned int random_value = long_secure_random();
    printf("Generated Random Value: %u\n", random_value);

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
    buffer[strcspn(buffer, "\n")] = '\0'; // 確保字串結尾正確

    printf("%s", buffer);

    // 傳送計算出的隨機數
    char send_buffer[20];
    snprintf(send_buffer, sizeof(send_buffer), "%u\n", random_value);
    send(sock, send_buffer, strlen(send_buffer), 0);

    // 讀取伺服器回應
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer) - 1, 0);
    printf("%s", buffer);

    // 關閉 Socket
    close(sock);

    return 0;
}
