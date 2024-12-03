
#include "../../UniversalSocket.h"
#include <stdio.h>

int main() {
  Universal_socket_int sock;
  int timeout = 5000;

  Universal_start_all();

  sock = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);

  Universal_setsockopt(sock, UNI_SOL_SOCKET, UNI_SO_RCVBUF, (char *)&timeout, sizeof(timeout));

  Universal_close(sock);
  Universal_end();
  return 0;
}
