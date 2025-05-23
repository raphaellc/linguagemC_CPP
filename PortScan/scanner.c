#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdint.h>
#include <time.h>

#define PSEUDO_HEADER_SIZE 12
#define PACKET_SIZE 60
#define BUFFER_SIZE 1024
#define TIMEOUT_SEC 2

typedef struct iphdr {
    unsigned int ihl : 4;
    unsigned int version : 4;
    uint8_t tos;
    uint16_t tot_len;
    uint16_t id;
    uint16_t frag_off;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
} IPV4_HDR;

typedef struct tcphdr {
    uint16_t source;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack_seq;
    unsigned int res1 : 4;
    unsigned int doff : 4;
    unsigned int fin : 1;
    unsigned int syn : 1;
    unsigned int rst : 1;
    unsigned int psh : 1;
    unsigned int ack : 1;
    unsigned int urg : 1;
    unsigned int res2 : 2;
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
} TCP_HDR;

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    
    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    
    if (len == 1)
        sum += *(unsigned char *)buf;
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    
    return (unsigned short)~sum;
}

void scan_port(const char *target_ip, int target_port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup falhou: %d\n", WSAGetLastError());
        return;
    }

    // Socket para enviar
    SOCKET send_sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (send_sock == INVALID_SOCKET) {
        printf("Erro ao criar socket de envio: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    // Habilita header IP personalizado
    int enable = 1;
    if (setsockopt(send_sock, IPPROTO_IP, IP_HDRINCL, (char*)&enable, sizeof(enable)) == SOCKET_ERROR) {
        printf("setsockopt falhou: %d\n", WSAGetLastError());
        closesocket(send_sock);
        WSACleanup();
        return;
    }

    // Socket para receber
    SOCKET recv_sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (recv_sock == INVALID_SOCKET) {
        printf("Erro ao criar socket de recebimento: %d\n", WSAGetLastError());
        closesocket(send_sock);
        WSACleanup();
        return;
    }

    // Configura timeout
    DWORD timeout = TIMEOUT_SEC * 1000;
    if (setsockopt(recv_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) {
        printf("Erro ao configurar timeout: %d\n", WSAGetLastError());
        closesocket(send_sock);
        closesocket(recv_sock);
        WSACleanup();
        return;
    }

    // Vincula o socket de recebimento
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(recv_sock, (struct sockaddr *)&local, sizeof(local)) == SOCKET_ERROR) {
        printf("Erro ao vincular socket de recebimento: %d\n", WSAGetLastError());
        closesocket(send_sock);
        closesocket(recv_sock);
        WSACleanup();
        return;
    }

    // Prepara pacote SYN
    char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

    IPV4_HDR *iph = (IPV4_HDR *)packet;
    TCP_HDR *tcph = (TCP_HDR *)(packet + sizeof(IPV4_HDR));

    // Cabeçalho IP
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(PACKET_SIZE);
    iph->id = htons((unsigned short)(rand() % 65535));
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;
    iph->saddr = inet_addr("192.168.15.154"); // Modifique para seu IP
    iph->daddr = inet_addr(target_ip);
    iph->check = 0;

    // Cabeçalho TCP
    uint16_t src_port = htons(12345 + (rand() % 1000));
    tcph->source = src_port;
    tcph->dest = htons(target_port);
    tcph->seq = htonl(rand() % 4294967295);
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->syn = 1;
    tcph->window = htons(5840);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    // Checksum TCP
    struct pseudo_header {
        uint32_t source_address;
        uint32_t dest_address;
        uint8_t placeholder;
        uint8_t protocol;
        uint16_t tcp_length;
    } psh;

    psh.source_address = iph->saddr;
    psh.dest_address = iph->daddr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(TCP_HDR));

    char pseudo_packet[PSEUDO_HEADER_SIZE + sizeof(TCP_HDR)];
    memcpy(pseudo_packet, &psh, PSEUDO_HEADER_SIZE);
    memcpy(pseudo_packet + PSEUDO_HEADER_SIZE, tcph, sizeof(TCP_HDR));
    tcph->check = checksum(pseudo_packet, sizeof(pseudo_packet));

    // Checksum IP
    iph->check = checksum(iph, sizeof(IPV4_HDR));

    // Configura destino para envio
    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(target_port);
    dest.sin_addr.s_addr = inet_addr(target_ip);

    // Envia pacote SYN
    if (sendto(send_sock, packet, PACKET_SIZE, 0, (struct sockaddr *)&dest, sizeof(dest)) == SOCKET_ERROR) {
        printf("Erro ao enviar SYN para %s:%d - %d\n", target_ip, target_port, WSAGetLastError());
        closesocket(send_sock);
        closesocket(recv_sock);
        WSACleanup();
        return;
    }

    printf("Enviado SYN para %s:%d... ", target_ip, target_port);

    // Tenta receber resposta
    char buffer[BUFFER_SIZE];
    struct sockaddr_in from;
    int fromlen = sizeof(from);
    int bytes_received;
    clock_t start_time = clock();
    int timeout_ms = TIMEOUT_SEC * 1000;

    while ((clock() - start_time) * 1000 / CLOCKS_PER_SEC < timeout_ms) {
        bytes_received = recvfrom(recv_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&from, &fromlen);
        
        if (bytes_received == SOCKET_ERROR) {
            int error = WSAGetLastError();
            if (error == WSAETIMEDOUT) {
                break; // Timeout é esperado
            }
            printf("Erro ao receber: %d\n", error);
            continue;
        }
        
        if (bytes_received < sizeof(IPV4_HDR)) continue;
        
        IPV4_HDR *recv_iph = (IPV4_HDR *)buffer;
        if (recv_iph->protocol != IPPROTO_TCP) continue;

        int ip_header_len = recv_iph->ihl * 4;
        if (bytes_received < ip_header_len + sizeof(TCP_HDR)) continue;

        TCP_HDR *recv_tcph = (TCP_HDR *)(buffer + ip_header_len);
        
        // Verifica se é resposta para nossa porta de origem e se é SYN-ACK
        if (ntohs(recv_tcph->dest) == ntohs(src_port) && 
            recv_tcph->syn && recv_tcph->ack) {
            printf("Porta ABERTA\n");
            closesocket(send_sock);
            closesocket(recv_sock);
            WSACleanup();
            return;
        }
    }

    printf("Porta FECHADA ou sem resposta\n");
    closesocket(send_sock);
    closesocket(recv_sock);
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