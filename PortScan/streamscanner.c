#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdint.h>
#include <time.h>

#define TIMEOUT_SEC 2

void scan_port(const char *target_ip, int target_port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup falhou: %d\n", WSAGetLastError());
        return;
    }

    // Criação do socket TCP
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Erro ao criar socket: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Configuração do timeout para evitar bloqueios longos
    DWORD timeout = TIMEOUT_SEC * 1000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(target_port);
    inet_pton(AF_INET, target_ip, &dest.sin_addr);

    printf("Tentando conectar a %s:%d... ", target_ip, target_port);
    
    // Tenta conectar ao alvo
    if (connect(sock, (struct sockaddr *)&dest, sizeof(dest)) == 0) {
        printf("Porta ABERTA\n");
    } else {
        printf("Porta FECHADA ou FILTRADA\n");
    }
    
    closesocket(sock);
    WSACleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <IP> <Porta>\n", argv[0]);
        return 1;
    }

    srand((unsigned int)time(NULL));
    scan_port(argv[1], atoi(argv[2]));
    return 0;
}
