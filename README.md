
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

## License

This library is provided under the MIT License.
