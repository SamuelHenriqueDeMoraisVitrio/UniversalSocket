#define  _WIN32
#include "src/imports/imports.def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 8080

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int received_bytes;

    // Limpa o buffer
    memset(buffer, 0, BUFFER_SIZE);

    // Lê a solicitação do cliente
    received_bytes = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (received_bytes <= 0) {
        printf("Erro ao receber dados ou conexão encerrada.\n");
        Universal_close(client_socket);
        return;
    }

    // Exibe os headers recebidos
    printf("Headers recebidos:\n%s\n", buffer);

    // Responde com um arquivo (exemplo: "index.html")
    const char *response_template =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %ld\r\n"
        "\r\n";

    FILE *file = fopen("index.html", "rb");
    if (!file) {
        const char *error_response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "404 Not Found";
        send(client_socket, error_response, strlen(error_response), 0);
        Universal_close(client_socket);
        return;
    }

    // Lê o arquivo e calcula o tamanho
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_content = (char *)malloc(file_size);
    fread(file_content, 1, file_size, file);

    // Envia o cabeçalho HTTP
    char response_header[BUFFER_SIZE];
    int header_length = snprintf(response_header, BUFFER_SIZE, response_template, file_size);
    send(client_socket, response_header, header_length, 0);

    // Envia o conteúdo do arquivo
    send(client_socket, file_content, file_size, 0);

    // Libera recursos
    free(file_content);
    fclose(file);

    Universal_close(client_socket);
}

int main() {
    int server_socket, client_socket;
    Universal_socket_addr server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    // Cria o socket
    if ((server_socket = Universal_socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Erro ao criar o socket");
        return 1;
    }

    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DEFAULT_PORT);

    // Associa o socket ao endereço e porta
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erro ao associar o socket");
        close(server_socket);
        return 1;
    }

    // Coloca o socket no modo de escuta
    if (listen(server_socket, 3) == -1) {
        perror("Erro ao colocar o socket no modo de escuta");
        close(server_socket);
        return 1;
    }

    printf("Servidor rodando na porta %d...\n", DEFAULT_PORT);

    // Aceita conexões e processa clientes
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_size)) != -1) {
        printf("Cliente conectado.\n");
        handle_client(client_socket);
    }

    perror("Erro ao aceitar conexão");
    close(server_socket);

    return 0;
}
