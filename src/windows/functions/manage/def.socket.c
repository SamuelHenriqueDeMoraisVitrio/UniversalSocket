
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
#include <netdb.h>
//silver_chain_scope_end


#define _WIN32


#if defined(_WIN32)

extern int Universal_start_all (){
    WSADATA wsa;
    int error = WSAStartup(MAKEWORD(2, 2), &wsa);
    return error;
}

extern int Universal_end (){
    WSACleanup();
}

extern int Universal_close (int fd){
    return closesocket(fd);
}

//#if defined(_GET_ADDR_INFO_DEFAULT_)
int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res){


    if (getaddrinfo) {
        return getaddrinfo(node, service, hints, res);
    }

    Universal_hostent *he = Universal_gethostbyname(node);
    if (he == NULL) {
        return UNI_EAI_NONAME;
    }

    Universal_sockaddr_in *addr = (Universal_sockaddr_in *)malloc(sizeof(Universal_sockaddr_in));
    if (addr == NULL) {
        return UNI_EAI_MEMORY;
    }

    addr->sin_family = UNI_AF_INET;
    addr->sin_port = (service != NULL) ? Universal_htons(atoi(service)) : 0;
    memcpy(&addr->sin_addr, he->h_addr, he->h_length);

    *res = (Universal_addrinfo *)malloc(sizeof(Universal_addrinfo));
    if (*res == NULL) {
        free(addr);
        return UNI_EAI_MEMORY;
    }

    (*res)->ai_family = UNI_AF_INET;
    (*res)->ai_socktype = (hints != NULL) ? hints->ai_socktype : UNI_SOCK_STREAM;
    (*res)->ai_protocol = (hints != NULL) ? hints->ai_protocol : UNI_IPPROTO_TCP;
    (*res)->ai_addrlen = sizeof(Universal_sockaddr_in);
    (*res)->ai_addr = (Universal_sockaddr *)addr;
    (*res)->ai_canonname = NULL;
    (*res)->ai_next = NULL;

    return 0;

}


void Universal_freeaddrinfo(Universal_addrinfo *addrinfo_ptr){
    if(getaddrinfo){
        freeaddrinfo(addrinfo_ptr);
    }
}
//#endif

#endif
