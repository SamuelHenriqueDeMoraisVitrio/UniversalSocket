
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.types.h"
//silver_chain_scope_end

int Universal_socket (int domain, int type, int protocol);

int Universal_ZeroMemory(void *ptr, size_t num);

int Universal_setsockopt(
    Universal_socket_int sockfd,
    int level,
    int optname,
    const void *optval,
    Universal_socket_len optlen
);

int Universal_getsockopt(
    Universal_socket_int sockfd,
    int level,
    int optname,
    void *optval,
    Universal_socket_len *optlen
);

Universal_hostent *Universal_gethostbyname(const char *hostname);




