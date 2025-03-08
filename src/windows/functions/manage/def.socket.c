
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end




#if defined(_WIN32)

extern int Universal_start_all (){
    WSADATA wsa;
    int error = WSAStartup(MAKEWORD(2, 2), &wsa);
    return error;
}

extern int Universal_end (){
   return  WSACleanup();
}

extern int Universal_close (int fd){
    return closesocket(fd);
}

//#if defined(_GET_ADDR_INFO_DEFAULT_)
int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res){


    Universal_hostent *he;

    he = Universal_gethostbyname(node);

    if(he == NULL){
        return 1;
    }

    *res = (Universal_addrinfo *)malloc(sizeof(Universal_addrinfo));
    if (*res == NULL) {
        return 1;
    }

    (*res)->ai_flags = 0;
    (*res)->ai_family = UNI_AF_INET;
    (*res)->ai_socktype = UNI_SOCK_STREAM;
    (*res)->ai_protocol = UNI_IPPROTO_TCP;
    (*res)->ai_addrlen = sizeof(Universal_sockaddr_in);


    Universal_sockaddr_in *sa_in = (Universal_sockaddr_in *)malloc(sizeof(Universal_sockaddr_in));
    if (sa_in == NULL) {
        free(*res);
        return 1;
    }

    Universal_in_addr **addr_list;
    sa_in->sin_family = UNI_AF_INET;
    addr_list = (Universal_in_addr **)he->h_addr_list;
    sa_in->sin_addr = *addr_list[0];

    (*res)->ai_addr = (Universal_sockaddr *)sa_in;
    (*res)->ai_canonname = strdup(he->h_name);
    (*res)->ai_next = NULL;

    return 0;
}


void Universal_freeaddrinfo(Universal_addrinfo *addrinfo_ptr){

    free(addrinfo_ptr->ai_addr);
    free(addrinfo_ptr->ai_canonname);
    free(addrinfo_ptr);
}
//#endif

#endif
