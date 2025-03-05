
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


#if defined(__linux__)

extern const char* Universal_inet_ntoa(Universal_in_addr addr) {
  static char buffer[INET_ADDRSTRLEN];
  return inet_ntop(UNI_AF_INET, &addr, buffer, INET_ADDRSTRLEN);
}

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags){
    return recv(fd, buf, n,flags);
}

#endif


