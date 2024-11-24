
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

int Universal_socket (int domain, int type, int protocol){
    return socket(domain,type,protocol);
}

int Universal_ZeroMemory(void *ptr, size_t num){

    if (ptr == NULL || num <= 0) {
        return -1;
    }

    memset(ptr, 0, (unsigned long long)num);
    return 0;
}

int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res){
    return getaddrinfo(node, service, hints, res);
}



