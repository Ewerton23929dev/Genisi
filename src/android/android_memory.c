#include <android/log.h>
#include <stdlib.h>
#include <stddef.h>

#define MEM_INIT 500
void** androidAllocs = NULL;

// Variável para máximo de memória.
const int androidMax = 12 * (1024 * 1024);
// Espaço usado em número de itens.
int androidSize = 0;
// Espaço usado em bytes.
long int androidSpace = 0;

int android_memoryInit() {
    androidAllocs = (void**) malloc(MEM_INIT * sizeof(void*));
    if (!androidAllocs) {
        __android_log_print(ANDROID_LOG_ERROR, "genisi", "Error allocating initial memory!");
        return 1;
    }
    __android_log_print(ANDROID_LOG_INFO, "genisi", "Initial memory allocated!");
    androidSize = 0;
    androidSpace = 0;
    return 0;
}

void* android_malloc(size_t size) {
    if (androidSpace + size > androidMax) {
        __android_log_print(ANDROID_LOG_FATAL, "genisi", "Fatal error: size exceeds maximum memory!");
        return NULL;
    }

    void* ptr = malloc(size);
    if (!ptr) {
        __android_log_print(ANDROID_LOG_ERROR, "genisi", "Error allocating memory!");
        return NULL;
    }

    androidAllocs[androidSize++] = ptr;
    androidSpace += size;
    __android_log_print(ANDROID_LOG_INFO, "genisi", "Memory allocated: %p", ptr);

    return ptr;
}

int android_free(void* ptr) {
    for (size_t t = 0; t < androidSize; t++) {
        if (androidAllocs[t] == ptr) {
            free(ptr);
            androidSpace -= sizeof(ptr);
            
            // Replace with the last pointer and reduce size
            androidAllocs[t] = androidAllocs[--androidSize];

            __android_log_print(ANDROID_LOG_INFO, "genisi", "Pointer freed!");
            return 0;
        }
    }
    __android_log_print(ANDROID_LOG_ERROR, "genisi", "Pointer not found!");
    return 1;
}

void android_close() {
    for (int i = 0; i < androidSize; i++) {
        if (androidAllocs[i]) {
            free(androidAllocs[i]);
            __android_log_print(ANDROID_LOG_INFO, "genisi", "Pointer freed: %p!", androidAllocs[i]);
        }
    }
    free(androidAllocs);
    androidSize = 0;
    androidSpace = 0;
    __android_log_print(ANDROID_LOG_INFO, "genisi", "All pointers freed!");
}