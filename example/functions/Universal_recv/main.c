
#include "../../UniversalSocket.h"
#include <stdio.h>

int main() {
  Universal_socket_int sock;
  Universal_sockaddr_in serverAddr;
  char buffer[512];
  int bytesReceived;

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

  bytesReceived = Universal_recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (bytesReceived == UNI_SOCKET_ERROR) {
    printf("Receive failed\n");
  } else if (bytesReceived > 0) {
    buffer[bytesReceived] = '\0';
    printf("Received data: %s\n", buffer);
  } else {
    printf("No data received\n");
  }

  Universal_close(sock);
  Universal_end();
  return 0;
}
