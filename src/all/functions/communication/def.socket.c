
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags){
    return recv(fd, buf, n,flags);
}
extern ssize_t Universal_send (int fd, const void *buf, size_t n, int flags){
    return send(fd,buf,n,flags);
}

extern const char *Universal_inet_ntop(int af, const void *src, char *dst, Universal_socket_len size){
    return inet_ntop(af, src, dst, size);
}

extern int Universal_inet_pton(int af, const char *src, void *dst){
    return inet_pton(af, src, dst);
}

extern uint32_t Universal_ntohl(uint32_t netlong){
    return ntohl(netlong);
}

