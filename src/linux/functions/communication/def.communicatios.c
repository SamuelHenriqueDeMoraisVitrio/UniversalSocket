
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


#if defined(__linux__)

extern const char* Universal_inet_ntoa(Universal_in_addr addr) {
  static char buffer[INET_ADDRSTRLEN];
  return inet_ntop(UNI_AF_INET, &addr, buffer, INET_ADDRSTRLEN);
}

#endif


