#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <windows.h>

enum Code {
    SendRecord,
    GetRecordsTop10,
};
typedef struct {
    char* author;
    float val;
} Record;

#define nil NULL
#define DEFAULT_PORT "3000"
#define DEFAULT_BUFLEN 512
extern void panic(const char*);
extern void info(const char*);
