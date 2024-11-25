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


