
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.types.h"
//silver_chain_scope_end

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags);

extern ssize_t Universal_send (int fd, const void *buf, size_t n, int flags);

extern const char *Universal_inet_ntop(int af, const void *src, char *dst, Universal_socket_len size);

extern int Universal_inet_pton(int af, const char *src, void *dst);

uint32_t Universal_ntohl(uint32_t netlong);

uint16_t Universal_htons(uint16_t value);

uint16_t Universal_ntohs(uint16_t value);

extern in_addr_t Universal_inet_addr(const char *ip);


