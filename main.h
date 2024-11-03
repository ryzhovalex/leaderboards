#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int type;
    char* val;
    int len;
} Request;
typedef struct {
    char* header;
    char* filename, filepath;
    int err;
} Response;

#define nil NULL
#define DEFAULT_PORT "3000"
extern void panic(const char*);
extern void info(const char*);
