
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


#if defined(_WIN32)

extern const char* Universal_inet_ntoa(Universal_in_addr addr) {
  return inet_ntoa(addr);
}

#endif


