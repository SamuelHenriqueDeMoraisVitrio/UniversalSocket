
//silver_chain_scope_start
//mannaged by silver chain
#include "../imports/imports.imp.h"
//silver_chain_scope_end


#if defined(__linux__)

#define UNI_INVALID_SOCKET -1
#define UNI_SOCKET_ERROR -1
#define UNI_EAGAIN EAGAIN
#define UNI_EWOULDBLOCK EWOULDBLOCK

#define UNI_ECONNREFUSED ECONNREFUSED
#define UNI_ETIMEDOUT ETIMEDOUT
#define UNI_EINPROGRESS EINPROGRESS
#define UNI_EADDRNOTAVAIL EADDRNOTAVAIL
#define UNI_ENETUNREACH ENETUNREACH

#define UNI_EAI_NONAME EAI_NONAME 
#define UNI_EAI_AGAIN EAI_AGAIN
#define UNI_EAI_FAIL EAI_FAIL
#define UNI_EAI_NODATA EAI_NONAME

#endif
