#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include <stdbool.h>

int main() {
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == SOCKET_ERROR) {
        panic(sprintf("Unable to startup (wsa::%d)", WSAGetLastError()));
    }

    struct addrinfo *ai_result = NULL, *ptr = NULL, hints;
    // Fill in the address structure, AF_INET = IPv4
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    int r = getaddrinfo(NULL, DEFAULT_PORT, &hints, &ai_result);
    if (r != 0) {
        panic(sprintf("Invalid socket (%d)", r));
    }

    SOCKET listen_socket = socket(
        ai_result->ai_family,
        ai_result->ai_socktype,
        ai_result->ai_protocol
    );
    if (listen_socket == INVALID_SOCKET) {
        freeaddrinfo(ai_result);
        panic(sprintf("Invalid socket (%d)", WSAGetLastError()));
    }

    r = bind(listen_socket, ai_result->ai_addr, (int)ai_result->ai_addrlen);
    if (r == SOCKET_ERROR) {
        freeaddrinfo(ai_result);
        closesocket(listen_socket);
        panic(sprintf("Bind failed (%d)", WSAGetLastError()));
    }

    // Once bind is called the address information is no longer needed
    freeaddrinfo(ai_result);

    // After socket is bound, we should listen on that addr for incoming
    // connection requests
    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listen_socket);
        panic(sprintf("Listen failed (%d)", WSAGetLastError()));
    }
}

void info(const char *s) {
    printf("[I] %s\n", s);
}

void panic(const char *s) {
    printf("[E] %s\n", s);
    WSACleanup();
    exit(EXIT_FAILURE);
}
