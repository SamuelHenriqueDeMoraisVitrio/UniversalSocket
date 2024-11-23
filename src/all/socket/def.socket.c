
//silver_chain_scope_start
//mannaged by silver chain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end

int Universal_socket (int __domain, int __type, int __protocol){
    return socket(__domain,__type,__protocol);
}
