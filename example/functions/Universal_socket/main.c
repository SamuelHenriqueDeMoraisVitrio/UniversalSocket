
#include "../../UniversalSocket.h"
#include <stdio.h>


int main() {
  Universal_socket_int sock;

  Universal_start_all();

  sock = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);

  if (sock == UNI_INVALID_SOCKET) {
    printf("Error creating socket.\n");
  } else {
    printf("Socket created successfully.\n");
  }

  Universal_close(sock);
  Universal_end();
  return 0;
}

