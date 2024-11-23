#ifndef silverchain_imp
#define silverchain_imp

#if defined(__linux__)

#include <arpa/inet.h>
#include <sys/socket.h>

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

int Universal_socket (int __domain, int __type, int __protocol);

#endif

#ifndef silverchain_def
#define silverchain_def

//silver_chain_scope_start
//mannaged by silver chain

//silver_chain_scope_end

int Universal_socket (int __domain, int __type, int __protocol){
    return socket(__domain,__type,__protocol);
}

#endif
