
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

extern int Universal_bind (int fd, Universal_sockaddr_in  *addrin , Universal_socket_len len){
    return bind(fd,(const struct sockaddr *)addrin,len);
}
extern int Universal_accept (int fd, Universal_sockaddr_in *addrin, Universal_socket_len *adrr_len){
    return accept(fd,( struct sockaddr *)addrin,adrr_len);
}
extern int Universal_listen (int fd, int n){
   return  listen(fd,n);
}

extern int Universal_connect(int sockfd, const Universal_sockaddr *addr, socklen_t addrlen){
    return connect(sockfd, addr, addrlen);
}
