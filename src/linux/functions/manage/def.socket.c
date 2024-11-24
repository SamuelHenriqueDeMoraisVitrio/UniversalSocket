
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

#if defined(__linux__)

extern int Universal_start_all (){
    return 0;
}

extern int Universal_end (){
    return 0;
}

extern int Universal_close (int fd){
    return close(fd);
}

#endif
