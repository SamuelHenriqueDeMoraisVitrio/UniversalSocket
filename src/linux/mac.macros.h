
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.imp.h"
//silver_chain_scope_end


#if defined(__linux__)

#define UNI_SO_REUSEADDR SO_REUSEADDR
#define UNI_SO_RCVBUF SO_RCVBUF
#define UNI_SOL_SOCKET SOL_SOCKET
#define UNI_AF_INET6 AF_INET6
#define UNI_INVALID_SOCKET -1
#define UNI_SOCKET_ERROR -1
#define UNI_EAGAIN EAGAIN
#define UNI_EWOULDBLOCK EWOULDBLOCK

#endif
