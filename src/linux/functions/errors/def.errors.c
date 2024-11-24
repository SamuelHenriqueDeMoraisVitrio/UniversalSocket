
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


#if defined(__linux__)


extern char *Universal_GetLastError(){
  return strerror(errno);
}



#endif





