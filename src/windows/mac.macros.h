
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.imp.h"
//silver_chain_scope_end



#if defined(_WIN32)

#define UNI_SO_REUSEADDR SO_REUSEADDR
#define UNI_SO_RCVBUF SO_RCVBUF
#define UNI_SOL_SOCKET SOL_SOCKET
#define UNI_AF_INET6 AF_INET6
#define UNI_INVALID_SOCKET INVALID_SOCKET
#define UNI_SOCKET_ERROR SOCKET_ERROR
#define UNI_EAGAIN WSAEWOULDBLOCK
#define UNI_EWOULDBLOCK WSAEWOULDBLOCK

#endif







