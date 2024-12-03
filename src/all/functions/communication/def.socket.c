
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags){
    return recv(fd, buf, n,flags);
}
extern ssize_t Universal_send (int fd, const void *buf, size_t n, int flags){
    return send(fd,buf,n,flags);
}

#if !defined(_DEFAULT_INET_PTON_AND_INET_NTOP_)

extern const char *Universal_inet_ntop(int af, const void *src, char *dst, Universal_socket_len size){
    if (af == AF_INET) {
        unsigned char *p = (unsigned char *)src;
        snprintf(dst, size, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
        return dst;
    } else if (af == AF_INET6) {
        unsigned char *p = (unsigned char *)src;
        int i;
        int offset = 0;

        for (i = 0; i < 8; i++) {
            if (offset < size) {
                offset += snprintf(dst + offset, size - offset, "%x", (p[i * 2] << 8) | p[i * 2 + 1]);
            }
            if (i < 7 && offset < size) {
                dst[offset++] = ':';
            }
        }
        return dst;
    }

    return NULL;
}

extern int Universal_inet_pton(int af, const char *src, void *dst){
    if (af == AF_INET) {
        unsigned char *p = (unsigned char *)dst;
        int values[4];
        if (sscanf(src, "%d.%d.%d.%d", &values[0], &values[1], &values[2], &values[3]) != 4) {
            return 0;
        }
        
        for (int i = 0; i < 4; i++) {
            if (values[i] < 0 || values[i] > 255) {
                return 0;
            }
            p[i] = (unsigned char)values[i];
        }

        return 1;
    } 
    else if (af == AF_INET6) {
        unsigned char *p = (unsigned char *)dst;
        int values[8];
        int count = 0;
        const char *ptr = src;
        int i;
        
        while (*ptr) {
            if (sscanf(ptr, "%x", &values[count]) != 1) {
                return 0;
            }
            count++;
            while (*ptr && isxdigit(*ptr)) {
                ptr++;
            }
            if (*ptr == ':') {
                ptr++;
            }
            if (count > 8) {
                return 0;
            }
        }

        if (count != 8) {
            return 0;
        }

        for (i = 0; i < 8; i++) {
            p[i * 2] = (unsigned char)(values[i] >> 8);
            p[i * 2 + 1] = (unsigned char)(values[i] & 0xFF);
        }

        return 1;
    }

    return 0;
}

#else

extern const char *Universal_inet_ntop(int af, const void *src, char *dst, Universal_socket_len size){
    return inet_ntop(af, src, dst, size);
}

extern int Universal_inet_pton(int af, const char *src, void *dst){
    return inet_pton(af, src, dst);
}

#endif

extern uint32_t Universal_ntohl(uint32_t netlong){
    return ntohl(netlong);
}

uint16_t Universal_htons(uint16_t value) {
    return htons(value);
}

uint16_t Universal_ntohs(uint16_t value) {
    return ntohs(value);
}

extern in_addr_t Universal_inet_addr(const char *ip) {
  return inet_addr(ip);
}

