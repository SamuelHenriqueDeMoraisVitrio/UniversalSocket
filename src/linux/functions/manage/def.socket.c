
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

#if defined(__linux__)

extern int Universal_start_all (){
    return 0;
}

extern int Universal_end (){
    return 0;
}

extern int Universal_close (int fd){
    return close(fd);
}

//#if defined(_GET_ADDR_INFO_DEFAULT_)
int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res){
    return getaddrinfo(node, service, hints, res);
}


void Universal_freeaddrinfo(Universal_addrinfo *addrinfo_ptr){
    freeaddrinfo(addrinfo_ptr);
}
//#endif





#endif


