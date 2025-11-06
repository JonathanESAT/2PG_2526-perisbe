#include <stdio.h>
#include <winsock2.h> 
#include "structs.h"
#pragma comment(lib, "ws2_32.lib")

int main(){
  WSADATA wsa; 
  SOCKET sock_cliente;  
  SOCKET sock_server; 
  struct sockaddr_in ip;
  struct Paquete pkt;
  WSAStartup(MAKEWORD(2,0), &wsa);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
  ip.sin_family = AF_INET; 
  ip.sin_addr.s_addr = inet_addr("127.17.2.21"); 
  ip.sin_port = htons(9999); 
  connect(sock, SOCKADDR*(&ip, sizeof(ip)));
  while(1)
  {
    memset(&pkt, 0, sizeof(pkt));
    pkt.tipo=2;
    pkt.usuario.id = 55;
    strcpy(pkt.usuario.nombre, "Bloster");
    pkt.usuario.vida=99;
    send(sock, (char*)&pkt, sizeof(pkt), 0);
    printf("Que es Bloster");
    memset(&pkt, 0, sizeof(pkt), 0);
    pkt.tipo = 2;
    pkt.dato.id_user=55;
    strcpy(pkt.dato.mapa, "Mapa Bloster");
    pkt.dato.posx = 10;
    pkt.dato.posy = 67;
    system("pause");
  }
  return 0;
}