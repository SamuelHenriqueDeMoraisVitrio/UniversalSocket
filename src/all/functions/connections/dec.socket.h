
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.types.h"
//silver_chain_scope_end

extern int Universal_bind (int fd,Universal_socket_addr_in  *addrin , universal_socket_len len);

extern int Universal_accept (int fd, Universal_socket_addr_in *addrin,
		   universal_socket_len *adrr_len);

extern int Universal_listen (int fd, int n);
