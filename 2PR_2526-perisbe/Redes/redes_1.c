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
  sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
  ip.sin_family = AF_INET; 
  ip.sin_addr.s_addr = inet_addr("0.0.0.0"); 
  ip.sin_port = htons(9999); 
  bind(sock_server, (SOCKADDR*)&ip, sizeof(ip));
  listen(sock_server, 2);
  printf("esperando conexion");
  sock_cliente = accept(sock_server, NULL, NULL);
  while(1){
    printf("Pendiente de diamante");
    memset(&pkt, 0, sizeof(pkt));
    recv(sock_cliente,(char*)&pkt, sizeof(pkt), 0);
    if(pkt.tipo==1){
      printf("Recibido dato");
    }
    else if(pkt.tipo==2)
    
  
    printf("Recibido usuario");
  }


  return 0;
}