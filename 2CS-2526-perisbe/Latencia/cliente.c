#include <stdio.h>
#include <winsock2.h> //API prog red
#include "estructuras.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;  //winsock api
    SOCKET sock;

    struct sockaddr_in ip;
    struct Paquete pkt;


    WSAStartup(MAKEWORD(2, 0), &wsa);


    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = inet_addr("127.0.0.1");
    ip.sin_port = htons(9999);
    connect(sock, (SOCKADDR)&ip, sizeof(ip)); //conexion

    while (1) {
        memset(&pkt, 0, sizeof(pkt));
        pkt.tipo = 2;
        pkt.usuario.id = 420;
        strcopy(pkt.usuario.nombre, "Bloste");
        pkt.usuario.vida = 99;
        send(sock, (char)&pkt, sizeof(pkt), 0);
        printf("\n enviado paquete usuario");
        pkt.tipo = 1;
        pkt.dato.id_user = 69;
        strcopy(pkt.dato.mapa, "Overpass");
        pkt.dato.posx = 10;
        pkt.dato.posy = 10;
        system("pause");
    }

    return 0;
}