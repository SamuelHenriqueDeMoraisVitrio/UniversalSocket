
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define DEFAULT_PORT "8080" // Porta do servidor
#define BUFFER_SIZE 512     // Tamanho do buffer para mensagens

int main() {
    WSADATA wsaData;
    int iResult;

    // Inicializa o Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup falhou: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;        // IPv4
    hints.ai_socktype = SOCK_STREAM; // Socket TCP
    hints.ai_protocol = IPPROTO_TCP; // Protocolo TCP
    hints.ai_flags = AI_PASSIVE;     // Para escutar conexões

    // Resolve o endereço e a porta do servidor
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo falhou: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Cria um socket para aceitar conexões
    SOCKET ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("Erro ao criar socket: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Associa o socket ao endereço e porta
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind falhou: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // Coloca o socket em modo de escuta
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen falhou: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Servidor em execução na porta %s...\n", DEFAULT_PORT);

    // Aceita conexões de clientes
    SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept falhou: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado.\n");

    // Envia uma mensagem para o cliente
    const char *welcomeMsg = "Bem-vindo ao servidor!\n";
    send(ClientSocket, welcomeMsg, (int)strlen(welcomeMsg), 0);

    // Recebe dados do cliente (opcional)
    char recvBuffer[BUFFER_SIZE];
    ZeroMemory(recvBuffer, BUFFER_SIZE);
    int bytesReceived = recv(ClientSocket, recvBuffer, BUFFER_SIZE, 0);
    if (bytesReceived > 0) {
        printf("Mensagem recebida: %.*s\n", bytesReceived, recvBuffer);
    }

    // Fecha o socket do cliente
    closesocket(ClientSocket);
    closesocket(ListenSocket);

    // Limpa o Winsock
    WSACleanup();

    return 0;
}
