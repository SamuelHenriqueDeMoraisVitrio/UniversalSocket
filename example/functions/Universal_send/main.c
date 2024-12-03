
#include "../../UniversalSocket.h"
#include <stdio.h>
#include <string.h>

int main() {
  Universal_socket_int sock;
  Universal_sockaddr_in serverAddr;
  char *data = "Hello, Server!";

  if (Universal_start_all() != 0) {
    printf("WSAStartup failed\n");
    return 1;
  }

  sock = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
  if (sock == UNI_INVALID_SOCKET) {
    printf("Socket creation failed\n");
    Universal_end();
    return 1;
  }

  Universal_ZeroMemory(&serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = UNI_AF_INET;
  serverAddr.sin_port = Universal_htons(8080);
  serverAddr.sin_addr.s_addr = Universal_inet_addr("127.0.0.1");

  if (Universal_connect(sock, (Universal_sockaddr*)&serverAddr, sizeof(serverAddr)) == UNI_SOCKET_ERROR) {
    printf("Connection failed\n");
    Universal_close(sock);
    Universal_end();
    return 1;
  }

  if (Universal_send(sock, data, strlen(data), 0) == UNI_SOCKET_ERROR) {
    printf("Send failed\n");
    Universal_close(sock);
    Universal_end();
    return 1;
  }

  printf("Data sent successfully\n");

  Universal_close(sock);
  Universal_end();
  return 0;
}

