
#include "../../../UniversalSocket.h"



int main() {
  Universal_socket_int sock;
  Universal_sockaddr_in serverAddr;

  if(Universal_start_all() != 0){
    printf("Failed to initialize Winsock. Error: %s\n", Universal_GetLastError());
    return 1;
  }

  sock = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
  if(sock == UNI_INVALID_SOCKET){
    printf("Failed to create of socket. Error: %s\n", Universal_GetLastError());
    Universal_end();
    return 1;
  }

  serverAddr.sin_family = UNI_AF_INET;
  serverAddr.sin_port = Universal_htons(8080);
  serverAddr.sin_addr.s_addr = Universal_inet_addr("127.0.0.1");
  

  printf("addres configured:\n");
  printf("  Family: %d\n", serverAddr.sin_family);
  printf("  Port: %d\n", Universal_ntohs(serverAddr.sin_port));
  printf("  Addres IP: %s\n", Universal_inet_ntoa(serverAddr.sin_addr));

  if (Universal_connect(sock, (Universal_sockaddr*)&serverAddr, sizeof(serverAddr)) == UNI_SOCKET_ERROR) {
      printf("Failed to conect. Error: %s\n", Universal_GetLastError());
  } else {
      printf("Successful connection to the server.\n");
  }

  Universal_close(sock);
  Universal_end();

  return 0;
}

