
# UniversalSocket

## Overview

`UniversalSocket` is a cross-platform C socket library designed to simplify socket programming on both Linux and Windows platforms. This library abstracts the platform-specific details and provides a unified API for socket creation, communication, and error handling.

It supports both IPv4 and IPv6 addresses, as well as TCP, UDP, and raw sockets. The library also allows for socket configuration using common socket options and handles typical socket operations like binding, listening, connecting, and accepting connections.

## Supported Platforms

- Linux
- Windows

## Releases
| item          | What its |
|-------        |-----------|
| [UniversalSocketOne.h](https://github.com/SamuelHenriqueDeMoraisVitrio/UniversalSocket/releases/download/0.2.4/UniversalSocketOne.h)| A single file release, with declarations and definitions all in one (usefull for single uniy compilations)  |
| [UniversalSocket.c](https://github.com/SamuelHenriqueDeMoraisVitrio/UniversalSocket/releases/download/0.2.4/UniversalSocket.c)|Definitions |
| [UniversalSocket.h](https://github.com/SamuelHenriqueDeMoraisVitrio/UniversalSocket/releases/download/0.2.4/UniversalSocket.h)|Declarations |


## Build from scracth

Install [darwin]("https://github.com/OUIsolutions/Darwin")

```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.020/darwin.out -o darwin && chmod +x darwin
```

Generate build
```bash
./darwin run_blueprint -mode folder build
```

## Features

- **Cross-Platform**: Works on both Linux and Windows.
- **Socket Abstraction**: Simplifies socket creation and management.
- **IPv4 and IPv6 Support**: Supports both IPv4 and IPv6 socket types.
- **TCP/UDP/Raw Socket Support**: Can create sockets for TCP, UDP, and raw communication.
- **Socket Options**: Provides functions for setting and getting socket options.
- **Error Handling**: Unified error handling with platform-specific messages.


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
#include "UniversalSocketOne.h"
#define PORT 3000
int main() {


   int iResult = Universal_start_all();
      if (iResult != 0) {
        printf("WSAStartup falhou: %d\n", iResult);
        return 1;
      }
    Universal_socket_int server_fd;
    struct sockaddr_in server_addr;

    // Initialize socket
    server_fd = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
    if (server_fd == UNI_INVALID_SOCKET) {
        printf("Socket creation failed: %s", Universal_GetLastError());
        return -1;
    }

    // Set server address
    server_addr.sin_family = UNI_AF_INET;
    server_addr.sin_addr.s_addr = UNI_INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (Universal_bind(server_fd, &server_addr, sizeof(server_addr)) == UNI_SOCKET_ERROR) {
        printf("Bind failed: %s", Universal_GetLastError());
        return -1;
    }

    // Listen for incoming connections
    if (Universal_listen(server_fd, 5) == UNI_SOCKET_ERROR) {
        printf("Listen failed: %s", Universal_GetLastError());
        return -1;
    }

    printf("Server is listening on port %d...\n",PORT);

    // Accept client connection
    struct sockaddr_in client_addr;
    Universal_socket_len client_len = sizeof(client_addr);
    Universal_socket_int client_fd = Universal_accept(server_fd, &client_addr, &client_len);
    if (client_fd == UNI_INVALID_SOCKET) {
        printf("Accept failed: %s", Universal_GetLastError());
        return -1;
    }
    printf("Client connected!\n");

    const char response[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "Hello, World!";

   Universal_send(client_fd,response, sizeof(response),MSG_WAITALL);

    // Close server socket
    Universal_close(server_fd);
    Universal_end();

    return 0;
}

```

### Client Example (TCP)

```c

#include "UniversalSocketOne.h"
#define PORT 3000
#define IP "127.0.0.1"
int main() {
    Universal_socket_int client_fd;
    struct sockaddr_in server_addr;

    // Initialize socket
    client_fd = Universal_socket(UNI_AF_INET, UNI_SOCK_STREAM, UNI_IPPROTO_TCP);
    if (client_fd == UNI_INVALID_SOCKET) {
        printf("Socket creation failed: %s", Universal_GetLastError());
        return -1;
    }

    // Set server address
    server_addr.sin_family = UNI_AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    // Connect to server
    if (Universal_connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == UNI_SOCKET_ERROR) {
        printf("Connection failed: %s", Universal_GetLastError());
        return -1;
    }
    char buff[9] ={0};
    while (1) {
        int size_read = Universal_recv(client_fd, buff,sizeof(buff), MSG_WAITALL);
        if(size_read <=0){
            break;
        }
        printf("%s",buff);
    }


    // Close client socket
    Universal_close(client_fd);

    return 0;
}

```

---

## Example structs

### Universal_addrinfo
```c
#include "UniversalSocketOne.h"

#define PORT 3000
#define URL  "www.google.com"

int main() {
    int iResult;

    iResult = Universal_start_all();
    if (iResult != 0) {
        printf("Universal_start_all falhou: %d\n", iResult);
        return 1;
    }

    Universal_addrinfo hints;
    Universal_addrinfo *result = NULL;
    Universal_addrinfo *ptr = NULL;

    Universal_ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = UNI_AF_UNSPEC;   // Permite IPv4 e IPv6
    hints.ai_socktype = UNI_SOCK_STREAM;
    hints.ai_protocol = UNI_IPPROTO_TCP;

    char port[10] = {0};
    sprintf(port, "%d", PORT);

    iResult = Universal_getaddrinfo(URL, port, &hints, &result);
    if (iResult != 0) {
        printf("Universal_getaddrinfo falhou: %d\n", iResult);
        Universal_end();
        return 1;
    }

    printf("IP for %s:\n", URL);

    char ipStr[INET6_ADDRSTRLEN];
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        void *addr;
        if (ptr->ai_family == UNI_AF_INET) {
            addr = &((Universal_sockaddr_in *)ptr->ai_addr)->sin_addr;
        } else if (ptr->ai_family == UNI_AF_INET6) {
            addr = &((Universal_sockaddr_in6 *)ptr->ai_addr)->sin6_addr;
        } else {
            continue;
        }
        Universal_inet_ntop(ptr->ai_family, addr, ipStr, sizeof(ipStr));

        if(ptr->ai_family == UNI_AF_INET6){
            printf("IPV6:%s\n",ipStr);
        }
        if(ptr->ai_family == UNI_AF_INET){
            printf("IPV4:%s\n",ipStr);
        }
    }

    Universal_freeaddrinfo(result);
    Universal_end();

    return 0;
}

```
