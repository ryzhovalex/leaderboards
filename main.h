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

#define DEFAULT_PORT 3000
extern void panic(const char*);
extern void info(const char*);
