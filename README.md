
# UniversalSocket

## Overview

`UniversalSocket` is a cross-platform C socket library designed to simplify socket programming on both Linux and Windows platforms. This library abstracts the platform-specific details and provides a unified API for socket creation, communication, and error handling.

It supports both IPv4 and IPv6 addresses, as well as TCP, UDP, and raw sockets. The library also allows for socket configuration using common socket options and handles typical socket operations like binding, listening, connecting, and accepting connections.

## Supported Platforms

- Linux
- Windows

## Features

- **Cross-Platform**: Works on both Linux and Windows.
- **Socket Abstraction**: Simplifies socket creation and management.
- **IPv4 and IPv6 Support**: Supports both IPv4 and IPv6 socket types.
- **TCP/UDP/Raw Socket Support**: Can create sockets for TCP, UDP, and raw communication.
- **Socket Options**: Provides functions for setting and getting socket options.
- **Error Handling**: Unified error handling with platform-specific messages.

## Installation

Simply include the `UniversalSocket.h` file in your C project.

## Functions

### Universal Functions

- `Universal_socket(domain, type, protocol)`:
  - Creates a socket with the specified domain, type, and protocol.
  
- `Universal_bind(fd, addr, len)`:
  - Binds a socket to a local address.

- `Universal_accept(fd, addr, addr_len)`:
  - Accepts an incoming connection on a socket.

- `Universal_listen(fd, n)`:
  - Prepares the socket to accept incoming connections.

- `Universal_connect(sockfd, addr, addrlen)`:
  - Connects to a remote address.

- `Universal_recv(fd, buf, n, flags)`:
  - Receives data from a socket.

- `Universal_send(fd, buf, n, flags)`:
  - Sends data through a socket.

- `Universal_setsockopt(sockfd, level, optname, optval, optlen)`:
  - Sets a socket option.

- `Universal_getsockopt(sockfd, level, optname, optval, optlen)`:
  - Gets a socket option.

- `Universal_start_all()`:
  - Initializes platform-specific networking features (Windows only).

- `Universal_end()`:
  - Cleans up platform-specific networking features (Windows only).

- `Universal_close(fd)`:
  - Closes a socket.

- `Universal_getaddrinfo(node, service, hints, res)`:
  - Resolves a domain name or service into an address structure.

- `Universal_freeaddrinfo(addrinfo_ptr)`:
  - Frees the memory used by address information.

- `Universal_GetLastError()`:
  - Returns the last error message related to socket operations.

### Constants

The library defines constants that map to their respective platform's socket API constants:

- `UNI_AF_INET`: IPv4 address family.
- `UNI_AF_INET6`: IPv6 address family.
- `UNI_SOCK_STREAM`: Stream socket (TCP).
- `UNI_SOCK_DGRAM`: Datagram socket (UDP).
- `UNI_SOCK_RAW`: Raw socket.
- `UNI_IPPROTO_TCP`: TCP protocol.
- `UNI_IPPROTO_UDP`: UDP protocol.
- `UNI_SO_RCVBUF`: Receive buffer size option.
- `UNI_SO_SNDTIMEO`: Send timeout option.
- `UNI_SHUT_RDWR`: Shut down both reading and writing on a socket.

## Error Handling

### Linux

- Errors are reported using `errno`. You can retrieve the last error using `Universal_GetLastError()`, which will return a string representation of the error.

### Windows

- Windows errors are reported through the `WSAGetLastError()` function. The `Universal_GetLastError()` function returns a string description of the last error.

## Example Usage

### Server Example (TCP)

```c
#include "UniversalSocket.h"

int main() {
    Universal_socket_int server_fd;
    struct sockaddr_in server_addr;

    // Initialize socket
    server_fd = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
    if (server_fd == UNI_INVALID_SOCKET) {
        printf("Socket creation failed: %s
", Universal_GetLastError());
        return -1;
    }

    // Set server address
    server_addr.sin_family = UNI_AF_INET;
    server_addr.sin_addr.s_addr = UNI_INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket
    if (Universal_bind(server_fd, &server_addr, sizeof(server_addr)) == UNI_SOCKET_ERROR) {
        printf("Bind failed: %s
", Universal_GetLastError());
        return -1;
    }

    // Listen for incoming connections
    if (Universal_listen(server_fd, 5) == UNI_SOCKET_ERROR) {
        printf("Listen failed: %s
", Universal_GetLastError());
        return -1;
    }

    printf("Server is listening on port 8080...
");

    // Accept client connection
    struct sockaddr_in client_addr;
    Universal_socket_len client_len = sizeof(client_addr);
    Universal_socket_int client_fd = Universal_accept(server_fd, &client_addr, &client_len);
    if (client_fd == UNI_INVALID_SOCKET) {
        printf("Accept failed: %s
", Universal_GetLastError());
        return -1;
    }

    printf("Client connected!
");

    // Close server socket
    Universal_close(server_fd);

    return 0;
}
```

### Client Example (TCP)

```c
#include "UniversalSocket.h"

int main() {
    Universal_socket_int client_fd;
    struct sockaddr_in server_addr;

    // Initialize socket
    client_fd = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
    if (client_fd == UNI_INVALID_SOCKET) {
        printf("Socket creation failed: %s
", Universal_GetLastError());
        return -1;
    }

    // Set server address
    server_addr.sin_family = UNI_AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (Universal_connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == UNI_SOCKET_ERROR) {
        printf("Connection failed: %s
", Universal_GetLastError());
        return -1;
    }

    printf("Connected to server!
");

    // Close client socket
    Universal_close(client_fd);

    return 0;
}
```

---

## Example structs

### Universal_addrinfo
```c

#include "../../../UniversalSocket.h"


int main() {
  int iResult;

  iResult = Universal_start_all();
  if (iResult != 0) {
    printf("WSAStartup falhou: %d\n", iResult);
    return 1;
  }

  Universal_addrinfo hints;
  Universal_addrinfo *result = NULL;

  Universal_ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = UNI_AF_UNSPEC;
  hints.ai_socktype = UNI_SOCK_STREAM;
  hints.ai_protocol = UNI_IPPROTO_TCP;

  const char *hostname = "www.google.com";
  const char *port = "80";

  iResult = Universal_getaddrinfo(hostname, port, &hints, &result);
  if (iResult != 0) {
    printf("getaddrinfo falhou: %d\n", iResult);
    Universal_end();
    return 1;
  }

  printf("Endereços IP para %s:\n", hostname);

  Universal_addrinfo *ptr = result;
  char ipstr[UNI_INET6_ADDRSTRLEN];

  while (ptr != NULL) {
    void *addr;
    const char *ipver;

    if (ptr->ai_family == UNI_AF_INET) {
      Universal_sockaddr_in *ipv4 = (Universal_sockaddr_in *)ptr->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "IPv4";
    } else if (ptr->ai_family == UNI_AF_INET6) {
      Universal_sockaddr_in6 *ipv6 = (Universal_sockaddr_in6 *)ptr->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "IPv6";
    } else {
      ptr = ptr->ai_next;
      continue;
    }

    const char *result_inet_ntop = Universal_inet_ntop(ptr->ai_family, addr, ipstr, sizeof(ipstr));

    if(result_inet_ntop == NULL){
      printf("Error in inet_ntop: %s\n", Universal_GetLastError());
      Universal_freeaddrinfo(result);
      Universal_end();
      return 1;
    }

    ptr = ptr->ai_next;


  }

  printf("suscefuly");

  Universal_freeaddrinfo(result);

  Universal_end();

  return 0;
}

```

### Universal_in6_addr

```c


#include "../../../UniversalSocket.h"
#include <stdlib.h>


int main() {

  if(Universal_start_all() != 0){
    fprintf(stderr, "Failed to initialize Winsock.\n");
    return EXIT_FAILURE;
  }

  const char* ipv6_str = "2001:db8::ff00:42:8329";

  Universal_in6_addr ipv6_addr;

  if (Universal_inet_pton(UNI_AF_INET6, ipv6_str, &ipv6_addr) != 1) {
    fprintf(stderr, "Error converting IPv6 address.\n");
    Universal_end();
    return EXIT_FAILURE;
  }

  printf("IPv6 address converted successfully.\n");

  printf("IPv6 address in bytes:\n");
  for(int i = 0; i < 16; i++){
    printf("%02x", ipv6_addr.s6_addr[i]);
    if ((i + 1) % 2 == 0 && i < 15) printf(":");
  }
  printf("\n");

  Universal_end();
  return EXIT_SUCCESS;
}
```

### Universal_in_addr
```c


#include "../../../UniversalSocket.h"


int main() {

  if(Universal_start_all() != 0){
    fprintf(stderr, "Failed to initialize Winsock.\n");
    return 1;
  }

  const char *ip_address = "192.168.1.1";

  Universal_in_addr addr;

  if (Universal_inet_pton(UNI_AF_INET, ip_address, &addr) != 1) {
    printf("Error converting IPv4 address.\n");
    Universal_end();
    return 1;
  }

  printf("Endereço IP: %s\n", ip_address);
  printf("Valor em formato binário: 0x%x\n", Universal_ntohl(addr.s_addr));

  Universal_end();
  return 0;
}
```

### Universal_sockaddr
```c


#include "../../../UniversalSocket.h"



int main() {
  Universal_socket_int sock;
  Universal_sockaddr_in serverAddr;

  if(Universal_start_all() != 0){
    printf("Failed to initialize Winsock. Error: %s\n", Universal_GetLastError());
    return 1;
  }

  sock = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
  if(sock == UNI_INVALID_SOCKET){
    printf("Failed to create of socket. Error: %s\n", Universal_GetLastError());
    Universal_end();
    return 1;
  }

  serverAddr.sin_family = UNI_AF_INET;
  serverAddr.sin_port = Universal_htons(8080);
  serverAddr.sin_addr.s_addr = Universal_inet_addr("127.0.0.1");
  

  printf("addres configured:\n");
  printf("  Family: %d\n", serverAddr.sin_family);
  printf("  Port: %d\n", Universal_ntohs(serverAddr.sin_port));
  printf("  Addres IP: %s\n", Universal_inet_ntoa(serverAddr.sin_addr));

  if (Universal_connect(sock, (Universal_sockaddr*)&serverAddr, sizeof(serverAddr)) == UNI_SOCKET_ERROR) {
      printf("Failed to conect. Error: %s\n", Universal_GetLastError());
  } else {
      printf("Successful connection to the server.\n");
  }

  Universal_close(sock);
  Universal_end();

  return 0;
}

```

### Universal_sockaddr_in
```c

#include "../../../UniversalSocket.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int result = Universal_start_all();
    if (result != 0) {
        printf("Falha ao iniciar a biblioteca de sockets. Erro: %s\n", Universal_GetLastError());
        return 1;
    }

    int server_fd = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
    if (server_fd == UNI_INVALID_SOCKET) {
        printf("Falha ao criar o socket. Erro: %s\n", Universal_GetLastError());
        Universal_end();
        return 1;
    }

    Universal_sockaddr_in server_addr;
    Universal_ZeroMemory(&server_addr, sizeof(server_addr));
    server_addr.sin_family = UNI_AF_INET;
    server_addr.sin_port = Universal_htons(PORT); // Convertendo a porta para a ordem de bytes de rede.
    server_addr.sin_addr.s_addr = UNI_INADDR_ANY; // Aceita conexões de qualquer IP.

    result = Universal_bind(server_fd, &server_addr, sizeof(server_addr));
    if (result == UNI_SOCKET_ERROR) {
        printf("Falha ao fazer o bind. Erro: %s\n", Universal_GetLastError());
        Universal_close(server_fd);
        Universal_end();
        return 1;
    }

    result = Universal_listen(server_fd, 5);
    if (result == UNI_SOCKET_ERROR) {
        printf("Falha ao escutar na porta. Erro: %s\n", Universal_GetLastError());
        Universal_close(server_fd);
        Universal_end();
        return 1;
    }

    printf("Servidor ouvindo na porta %d...\n", PORT);

    /*
    Universal_sockaddr_in client_addr;
    Universal_socket_len addr_len = sizeof(client_addr);
    int client_fd = Universal_accept(server_fd, &client_addr, &addr_len);
    if (client_fd == UNI_SOCKET_ERROR) {
        printf("Falha ao aceitar a conexão. Erro: %s\n", Universal_GetLastError());
        Universal_close(server_fd);
        Universal_end();
        return 1;
    }

    char client_ip[INET_ADDRSTRLEN];
    Universal_inet_ntop(UNI_AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("Conexão estabelecida com o cliente: %s\n", client_ip);

    const char *message = "Bem-vindo ao servidor!\n";
    Universal_send(client_fd, message, strlen(message), 0);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = Universal_recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0'; // Null-terminando a string recebida.
        printf("Mensagem recebida do cliente: %s\n", buffer);
    }

    Universal_close(client_fd);
    */
    Universal_close(server_fd);
    Universal_end();

    return 0;
}


```



## License

