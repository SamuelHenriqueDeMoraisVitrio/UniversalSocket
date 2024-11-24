
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.types.h"
//silver_chain_scope_end

int Universal_socket (int domain, int type, int protocol);

int Universal_ZeroMemory(void *ptr, size_t num);

void Universal_freeaddrinfo(Universal_addrinfo *addrinfo_ptr);

int Universal_setsockopt(
    Universal_socket_int sockfd,
    int level,
    int optname,
    const void *optval,
    Universal_socket_len optlen
);





