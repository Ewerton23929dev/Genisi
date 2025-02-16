#include <android/log.h>
#include <stdlib.h>
#include <stddef.h>

#define MEM_INIT 500
void** androidAllocs = NULL;
// variavel para maximo de memoria.
int androidMax = 12 * (1024 * 1024);
int androidSize = 0;
long int androidSpace = MEM_INIT;



int android_memoryInit() {
  androidAllocs = (void**) malloc(MEM_INIT * sizeof(void*));
  if (!androidAllocs) {
    __android_log_print(ANDROID_LOG_ERROR, "genisi", "Erro alocate head memory!");
    return 1;
  }
  __android_log_print(ANDROID_LOG_INFO,"genisi", "Head memory alocate!");
  androidSize = 0;
  androidSpace = 0;
  return 0;
}

void* android_malloc(size_t size) {
  if (androidSpace + size > androidMax) {
    if (size < androidMax) {
      __android_log_print(ANDROID_LOG_FATAL,"genisi", " Fatal size larger than maximum memory!");
      return NULL;
    }
    void* prt = malloc(size);
    if (!prt) {
      __android_log_print(ANDROID_LOG_ERROR, "genisi", "Error allocating pointer!");
      return NULL;
    }
    __android_log_print(ANDROID_LOG_INFO, "genisi", "Memory allocate %p", prt);
    androidAllocs[androidSize] = prt;
    androidSize++;
    androidSpace += size;
    return prt;
  }
  return NULL;
}

int android_free(void* prt) {
  for (size_t t = 0; t < androidSize; t++) {
    if (androidAllocs[t] == prt) {
      free(prt);
      androidAllocs[t] = NULL;
      __android_log_print(ANDROID_LOG_INFO, "genisi", "Pointer released!");
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
      __android_log_print(ANDROID_LOG_INFO, "genisi", "Pointer released %p!",  androidAllocs[i]);
    }
  }
  free(androidAllocs);
  androidSize = 0;
  androidSpace = MEM_INIT;
  __android_log_print(ANDROID_LOG_INFO, "genisi", "All pointers freed!");
}