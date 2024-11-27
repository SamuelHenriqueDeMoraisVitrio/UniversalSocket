
#include "../../../UniversalSocket.h"
#include <stdlib.h>


int main() {

  if(Universal_start_all() != 0){
    fprintf(stderr, "Failed to initialize Winsock.\n");
    return EXIT_FAILURE;
  }

  const char* ipv6_str = "2001:db8::ff00:42:8329";

  Universal_in6_addr ipv6_addr;

  if (Universal_inet_pton(UNI_AF_INET6, ipv6_str, &ipv6_addr) != 1) {
    fprintf(stderr, "Error converting IPv6 address.\n");
    Universal_end();
    return EXIT_FAILURE;
  }

  printf("IPv6 address converted successfully.\n");

  printf("IPv6 address in bytes:\n");
  for(int i = 0; i < 16; i++){
    printf("%02x", ipv6_addr.s6_addr[i]);
    if ((i + 1) % 2 == 0 && i < 15) printf(":");
  }
  printf("\n");

  Universal_end();
  return EXIT_SUCCESS;
}
