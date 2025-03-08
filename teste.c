#include "UniversalSocket.c"
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

    int sended =  Universal_send(client_fd,response, sizeof(response)-1,UNI_MSG_WAITALL);
    // Close server socket
    Universal_close(server_fd);
    Universal_end();

    return 0;
}
