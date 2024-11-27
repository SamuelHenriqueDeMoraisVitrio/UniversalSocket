#include "../../../UniversalSocket.h"


int main() {
  int iResult;

  iResult = Universal_start_all();
  if (iResult != 0) {
    printf("WSAStartup falhou: %d\n", iResult);
    return 1;
  }

  Universal_addrinfo hints;
  Universal_addrinfo *result = NULL;

  Universal_ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = UNI_AF_UNSPEC;
  hints.ai_socktype = UNI_SOCK_STREAM;
  hints.ai_protocol = UNI_IPPROTO_TCP;

  const char *hostname = "www.google.com";
  const char *port = "80";

  iResult = Universal_getaddrinfo(hostname, port, &hints, &result);
  if (iResult != 0) {
    printf("getaddrinfo falhou: %d\n", iResult);
    Universal_end();
    return 1;
  }

  printf("Endereços IP para %s:\n", hostname);

  Universal_addrinfo *ptr = result;
  char ipstr[UNI_INET6_ADDRSTRLEN];

  while (ptr != NULL) {
    void *addr;
    const char *ipver;

    if (ptr->ai_family == UNI_AF_INET) {
      Universal_sockaddr_in *ipv4 = (Universal_sockaddr_in *)ptr->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else if (ptr->ai_family == UNI_AF_INET6) {
      Universal_sockaddr_in6 *ipv6 = (Universal_sockaddr_in6 *)ptr->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    } else {
      ptr = ptr->ai_next;
      continue;
    }

    const char *result_inet_ntop = Universal_inet_ntop(ptr->ai_family, addr, ipstr, sizeof(ipstr));

    if(result_inet_ntop == NULL){
      printf("Error in inet_ntop: %s\n", Universal_GetLastError());
      Universal_freeaddrinfo(result);
      Universal_end();
      return 1;
    }

    ptr = ptr->ai_next;


  }

  printf("suscefuly");

  Universal_freeaddrinfo(result);

  Universal_end();

  return 0;
}

