#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client!";
    char buffer[1024] = {0};

    // Membuat socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Konversi alamat IP ke binary
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported\n");
        return -1;
    }

    // Terhubung ke server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // Mengirim pesan ke server
    send(sock, message, strlen(message), 0);
    printf("Pesan terkirim ke server.\n");

    // Membaca balasan dari server
    read(sock, buffer, 1024);
    printf("Balasan dari server: %s\n", buffer);

    close(sock);

    return 0;
}
