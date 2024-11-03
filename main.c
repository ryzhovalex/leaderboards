#include "main.h"

void _loop(SOCKET);
void _loop(SOCKET listen_socket) {
    int code;
    // We support up to 4 arguments
    char* arg0 = malloc(DEFAULT_BUFLEN * sizeof(char));
    char* arg1 = malloc(DEFAULT_BUFLEN * sizeof(char));
    char* arg2 = malloc(DEFAULT_BUFLEN * sizeof(char));
    char* arg3 = malloc(DEFAULT_BUFLEN * sizeof(char));

    // We continiously listen for incoming connections. Once a new connection
    // arrive, we grab the initial sent data, return response, and close
    // the connection.
    while (1) {
        // After socket is bound, we should listen on that addr for incoming
        // connection requests
        if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
            closesocket(listen_socket);
            panic("Failed listen");
        }

        SOCKET client_socket;
        // In the best case we listen, accept, then pass the accepted connection to
        // a separate thread, then continue listening.
        client_socket = accept(listen_socket, nil, nil);
        if (client_socket == INVALID_SOCKET) {
            closesocket(listen_socket);
            panic("Failed accept");
        }

        char* recvbuf = malloc(DEFAULT_BUFLEN * sizeof(char));
        int recv_result, send_result;
        int recvbuflen = DEFAULT_BUFLEN;
        // The send and recv functions both return an integer value of the number
        // of bytes sent or received, respectively, or an erro. Each function also
        // takes the same parameters: the active socket, a char buffer, the number
        // of bytes to send or receive, and any flags to use.

        do {
            recv_result = recv(client_socket, recvbuf, recvbuflen, 0);
            if (recv_result > 0) {
                // printf("[I] Bytes received: %d\n", recv_result);
                char* parts = strtok(recvbuf, " ");
                int i = 0;
                while (parts) {
                    switch (i) {
                        case 0:
                            code = atoi(parts);
                            break;
                        case 1:
                            arg0 = parts;
                            break;
                        case 2:
                            arg1 = parts;
                            break;
                        case 3:
                            arg2 = parts;
                            break;
                        case 4:
                            arg3 = parts;
                            break;
                    }
                    // Don't know how it works, for now,
                    // taken from: https://en.cppreference.com/w/c/string/byte/strtok
                    parts = strtok(nil, " ");
                    i++;
                }
                printf("Code: %d, Args: %s, %s, %s, %s\n", code, arg0, arg1, arg2, arg3);
                // Echo the buffer back to the sender
                send_result = send(client_socket, recvbuf, recv_result, 0);
                if (send_result == SOCKET_ERROR) {
                    closesocket(client_socket);
                    panic("Failed send");
                }
                // printf("[I] Bytes sent: %d\n", send_result);
            } else {
                closesocket(client_socket);
            }
        } while (recv_result > 0);
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

void _on_sigint(int);
void _on_sigint(int sig) {
    signal(SIGINT, _on_sigint);
    printf("[I] Interrupting...\n");
    exit(0);
}

DWORD WINAPI _boot_socket();
DWORD WINAPI _boot_socket() {
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) == SOCKET_ERROR) {
        panic("Unable to startup");
    }

    struct addrinfo *ai_result = NULL, *ptr = NULL, hints;
    ZeroMemory(&hints, sizeof(hints));
    // Fill in the address structure, AF_INET = IPv4
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // DEFAULT_PORT must be a string! If i write a number, it crashes with
    // STATUS_ACCESS_VIOLATION
    int r = getaddrinfo(NULL, DEFAULT_PORT, &hints, &ai_result);
    if (r != 0) {
        panic("Invalid socket");
    }

    SOCKET listen_socket = socket(
        ai_result->ai_family,
        ai_result->ai_socktype,
        ai_result->ai_protocol
    );
    if (listen_socket == INVALID_SOCKET) {
        freeaddrinfo(ai_result);
        panic("Invalid socket");
    }

    r = bind(listen_socket, ai_result->ai_addr, (int)ai_result->ai_addrlen);
    if (r == SOCKET_ERROR) {
        freeaddrinfo(ai_result);
        closesocket(listen_socket);
        panic("Bind failed");
    }

    // Once bind is called the address information is no longer needed
    freeaddrinfo(ai_result);
    _loop(listen_socket);
}

int main() {
    HANDLE thread = CreateThread(nil, 0, _boot_socket, nil, 0, nil);
    char cmd[8];
    while (1) {
        printf("> ");
        scanf("%s", cmd);
        if (strcmp(cmd, "q") == 0) {
            exit(0);
        }
    }
}
