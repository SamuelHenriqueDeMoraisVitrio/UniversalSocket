#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/imports/imports.def.h"
#pragma comment(lib, "ws2_32.lib")

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 8080

void handle_client(Universal_socket_int client_socket) {
    char buffer[BUFFER_SIZE];
    int received_bytes;

    // Limpa o buffer
    memset(buffer, 0, BUFFER_SIZE);

    // Lê a solicitação do cliente
    received_bytes = Universal_recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
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
    Universal_send(client_socket, response_header, header_length, 0);

    // Envia o conteúdo do arquivo
    Universal_send(client_socket, file_content, file_size, 0);

    // Libera recursos
    free(file_content);
    fclose(file);

    Universal_close(client_socket);
}




int main() {

    // Inicializa o Winsock
    if (Universal_start_all()) {
        printf("erro ao inicializar o socket");
        return 1;
    }


    Universal_socket_int server_socket;


    // Cria o socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("erroao criar socket\n");
        Universal_end();
        return 1;
    }


    Universal_socket_addr_in server_addr;
    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(DEFAULT_PORT);

    // Associa o socket ao endereço e porta
    if (Universal_bind(server_socket,&server_addr, sizeof(server_addr)) == -1) {
        printf("erroao criar socket\n");
        Universal_close(server_socket);
        Universal_end();

        return 1;
    }

    // Coloca o socket no modo de escuta
    if (Universal_listen(server_socket, 3) == -1) {
        printf("erroao criar socket\n");
        Universal_close(server_socket);
        Universal_end();
        return 1;
    }

    printf("Servidor rodando na porta %d...\n", DEFAULT_PORT);
    Universal_socket_int  client_socket;
    struct sockaddr_in  client_addr;
    universal_socket_len client_addr_size = sizeof(client_addr);

    // Aceita conexões e processa clientes
    while (
        client_socket = Universal_accept(server_socket, &client_addr, &client_addr_size) != -1) {
        printf("Cliente conectado.\n");
        handle_client(client_socket);
    }

    // Fecha o socket do servidor
    Universal_close(server_socket);
    Universal_end();

    return 0;
}
