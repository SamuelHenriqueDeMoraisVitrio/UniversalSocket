
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end



#if defined(_WIN32)

extern const char* Universal_inet_ntoa(Universal_in_addr addr) {
  return inet_ntoa(addr);
}

ssize_t private_Universal_recv_all(int fd, void *buf, size_t n){
  int max = 0;
  int received;

  while (max < n) {
    unsigned char *ptr = (unsigned char*)buf + max;
    received = recv(fd,(char*)ptr, n - max, 0);
  
    if (received <= 0) { 
      return max;
    }

    max += received;
  }

  return max;
}

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags){

  if(flags == UNI_MSG_WAITALL){
    return private_Universal_recv_all(fd, buf, n);
  }

  return recv(fd, (char*)buf, n, flags);
}

#endif


