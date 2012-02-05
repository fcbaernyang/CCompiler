#include "utils.h"

char current_file[MAX_FILE_NAME_LENGTH];
int current_line;

void* safe_malloc(size_t size) {
    void* mem = malloc(size);
    if (mem == NULL)
        FatalError("Failed to allocate memory");
    return mem;
}

void* safe_realloc(void *old, size_t size) {
    void* mem = realloc(old, size);
    if (mem == NULL)
        FatalError("Failed to allocate memory");
    return mem;
}

void error(const char *message, const char *param) {
    printf("In file \"%s\": line %d\n", current_file, current_line);
    printf("Compile error: %s%s\n", message, param);
    exit(EXIT_FAILURE);
}

void FatalError(const char* message) {
    printf("Fatal error: %s\n", message);
    exit(EXIT_FAILURE);
}

void InputError(const char* message, const char* filename) {
    printf("Fatal error while processing file \"%s\": %s\n", filename, message);
    exit(EXIT_FAILURE);
}
