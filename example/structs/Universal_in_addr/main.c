
#include "../../../UniversalSocket.h"


int main() {

  if(Universal_start_all() != 0){
    fprintf(stderr, "Failed to initialize Winsock.\n");
    return 1;
  }

  const char *ip_address = "192.168.1.1";

  Universal_in_addr addr;

  if (Universal_inet_pton(UNI_AF_INET, ip_address, &addr) != 1) {
    printf("Error converting IPv4 address.\n");
    Universal_end();
    return 1;
  }

  printf("Endereço IP: %s\n", ip_address);
  printf("Valor em formato binário: 0x%x\n", Universal_ntohl(addr.s_addr));

  Universal_end();
  return 0;
}
