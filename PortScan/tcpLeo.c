#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma comment(lib, "ws2_32.lib")

// Definição do cabeçalho IP
struct iphdr {
    unsigned int ihl:4;
    unsigned int version:4;
    unsigned char tos;
    unsigned short tot_len;
    unsigned short id;
    unsigned short frag_off;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short check;
    unsigned int saddr;
    unsigned int daddr;
};

// Definição do cabeçalho TCP
struct tcphdr {
    uint16_t source;
    uint16_t dest;
    uint32_t seq;
    uint32_t ack_seq;
    uint16_t doff:4;
    uint16_t res1:4;
    uint16_t flags:8;
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
};

void syn_scan(const char* ip, int ports[], int size) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    printf("Scanning %s with TCP SYN scan...\n", ip);
    
    for (int i = 0; i < size; i++) {
        SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) {
            printf("[-] Error creating raw socket\n");
            continue;
        }

        struct sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_port = htons(ports[i]);
        inet_pton(AF_INET, ip, &target.sin_addr);

        // Criar um pacote TCP SYN
        char packet[40] = {0};
        struct tcphdr* tcp = (struct tcphdr*)(packet + sizeof(struct iphdr));
        tcp->source = htons(12345);
        tcp->dest = htons(ports[i]);
        tcp->seq = htonl(0);
        tcp->ack_seq = 0;
        tcp->doff = 5;
        tcp->flags = 0x02; // SYN flag
        tcp->window = htons(1024);
        tcp->check = 0; // Checksum não calculado
        
        int result = sendto(sock, packet, sizeof(packet), 0, (struct sockaddr*)&target, sizeof(target));
        if (result == SOCKET_ERROR) {
            printf("[-] Error sending SYN packet to port %d\n", ports[i]);
            closesocket(sock);
            continue;
        }

        // Receber resposta
        char buffer[1024];
        struct sockaddr_in from;
        int fromlen = sizeof(from);
        int recv_len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&from, &fromlen);
        
        if (recv_len > 0) {
            struct tcphdr* response_tcp = (struct tcphdr*)(buffer + sizeof(struct iphdr));
            if ((response_tcp->flags & 0x12) == 0x12) { // SYN-ACK
                printf("[+] Port %d is open\n", ports[i]);
            } else if (response_tcp->flags & 0x04) { // RST
                printf("[-] Port %d is closed\n", ports[i]);
            }
        } else {
            printf("[?] Port %d is filtered or unresponsive\n", ports[i]);
        }

        closesocket(sock);
    }
    
    WSACleanup();
}

int main() {
    char ip_address[16];
    printf("Enter the IP address to scan: ");
    scanf("%15s", ip_address);
    
    int port_list[] = {21, 22, 23, 25, 53, 80, 443, 3306, 8080};
    int size = sizeof(port_list) / sizeof(port_list[0]);
    
    syn_scan(ip_address, port_list, size);
    
    return 0;
}
