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

// Estrutura do pseudo-header para checksum
struct pseudo_header {
    uint32_t source_address;
    uint32_t dest_address;
    uint8_t placeholder;
    uint8_t protocol;
    uint16_t tcp_length;
};

// Definição manual da estrutura iphdr para Windows
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

// Definição manual da estrutura tcphdr para Windows
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

// Função para calcular checksum
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;
    
    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    
    if (len == 1)
        sum += *(unsigned char *)buf;
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    
    return result;
}

// Função para criar e enviar um pacote SYN
void send_syn_packet(const char *target_ip, int target_port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup falhou: %d\n", WSAGetLastError());
        exit(1);
    }
    
    // Cria socket RAW com privilégios para cabeçalho IP personalizado
    SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sock == INVALID_SOCKET) {
        printf("Erro ao criar socket: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    // Habilita a inclusão do cabeçalho IP pelo usuário
    int enable = 1;
    if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char*)&enable, sizeof(enable)) == SOCKET_ERROR) {
        printf("setsockopt falhou: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(target_port);
    if (inet_pton(AF_INET, target_ip, &dest.sin_addr) != 1) {
        printf("Endereço IP inválido\n");
        closesocket(sock);
        WSACleanup();
        exit(1);
    }

    char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

    IPV4_HDR *iph = (IPV4_HDR *)packet;
    TCP_HDR *tcph = (TCP_HDR *)(packet + sizeof(IPV4_HDR));

    // Preenche cabeçalho IP
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(PACKET_SIZE);
    iph->id = htons((unsigned short)(rand() % 65535));
    iph->frag_off = 0;
    iph->ttl = 64;
    iph->protocol = IPPROTO_TCP;
    iph->saddr = inet_addr("192.168.1.154"); // Modifique para seu IP
    iph->daddr = dest.sin_addr.s_addr;
    iph->check = 0; // Zero inicialmente para cálculo do checksum

    // Preenche cabeçalho TCP
    tcph->source = htons(12345);
    tcph->dest = htons(target_port);
    tcph->seq = htonl(rand() % 4294967295);
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->syn = 1;
    tcph->window = htons(5840);
    tcph->check = 0;
    tcph->urg_ptr = 0;

    // Calcula checksum TCP usando pseudo-header
    struct pseudo_header psh;
    psh.source_address = iph->saddr;
    psh.dest_address = iph->daddr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_TCP;
    psh.tcp_length = htons(sizeof(TCP_HDR));

    char pseudo_packet[PSEUDO_HEADER_SIZE + sizeof(TCP_HDR)];
    memcpy(pseudo_packet, &psh, PSEUDO_HEADER_SIZE);
    memcpy(pseudo_packet + PSEUDO_HEADER_SIZE, tcph, sizeof(TCP_HDR));
    tcph->check = checksum(pseudo_packet, sizeof(pseudo_packet));

    // Calcula checksum IP
    iph->check = checksum(iph, sizeof(IPV4_HDR));

    // Envia o pacote
    if (sendto(sock, packet, PACKET_SIZE, 0, (struct sockaddr *)&dest, sizeof(dest)) == SOCKET_ERROR) {
        printf("Erro ao enviar pacote: %d\n", WSAGetLastError());
    } else {
        printf("Pacote SYN enviado para %s:%d\n", target_ip, target_port);
    }
    
    closesocket(sock);
    WSACleanup();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <IP> <Porta>\n", argv[0]);
        return 1;
    }
    
    // Inicializa gerador de números aleatórios
    srand((unsigned int)time(NULL));
    
    send_syn_packet(argv[1], atoi(argv[2]));
    return 0;
}