
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.imp.h"
//silver_chain_scope_end



#if defined(_WIN32)

#define UNI_INVALID_SOCKET INVALID_SOCKET
#define UNI_SOCKET_ERROR SOCKET_ERROR
#define UNI_EAGAIN WSAEWOULDBLOCK
#define UNI_EWOULDBLOCK WSAEWOULDBLOCK

#define UNI_ECONNREFUSED WSAECONNREFUSED
#define UNI_ETIMEDOUT WSAETIMEDOUT
#define UNI_EINPROGRESS WSAEINPROGRESS
#define UNI_EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define UNI_ENETUNREACH WSAENETUNREACH

#endif







