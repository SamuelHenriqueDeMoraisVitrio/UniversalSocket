#ifndef silverchain_imp
#define silverchain_imp

#if defined(__linux__)

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>


#endif

#endif

#ifndef silverchain_types
#define silverchain_types

//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end

#if defined(__linux__)
typedef   struct sockaddr_in Universal_socket_addr;
#endif


//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end
#if defined(_WIN32)

typedef SOCKET Universal_socket_addr
#endif

#endif

#ifndef silverchain_dec
#define silverchain_dec

//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end

int Universal_socket (int domain, int ttype, int protocol);

extern int Universal_close (int fd);

#endif

#ifndef silverchain_def
#define silverchain_def

//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end

int Universal_socket (int domain, int type, int protocol){
    return socket(domain,type,protocol);
}


//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end

#if defined(__linux__)

extern int Universal_close (int fd){
    return close(fd);
}
#endif


//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end
#if defined(_WIN32)

extern int Universal_close (int fd){
    return closesocket(fd);
}
#endif

#endif
