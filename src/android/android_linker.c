#include <androidModules/android.h>
#include <androidModules/android_linker.h>
#include <android/dlext.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void* android_dload(const char* path) {
  GenisiHandle* lib = malloc(sizeof(GenisiHandle));
  if (!lib) {
    android_log(ERRO, "genisi", "Failed to allocate library handle %s", path);
    return NULL;
  }
  lib->handle = android_dlopen_ext(path, RTLD_LAZY, NULL);
  if (!lib->handle) {
    android_log(ERRO, "genisi", "Failed to load library %s", path);
    free(lib);
    return NULL;
  }
  return lib;
}

void* android_dlMethod(GenisiHandle* handle, const char* name) {
  if (!handle || !name) {
    android_log(INFO, "genisi", "Incorrect parameters passed in android_dlMethod!");
    return NULL;
  }
  void* func = dlsym(handle->handle, name);
  if (!func) {
    android_log(ERRO, "genisi", "Error loading library function %s", name);
    return NULL;
  }
  return func;
}

void android_dlexit(GenisiHandle* handle) {
  if (!handle) {
    android_log(ERRO, "genisi", "Error trying to close NULL!");
    return;
  }
  if (handle->handle) {
      dlclose(handle->handle);
  }
  handle->handle = NULL;
  free(handle);
}

GenisiHandle* android_dlauto(const char* name) {
  char buffer[400];
  snprintf(buffer, sizeof(buffer), "/system/lib/%s", name);
  return android_dload(buffer);
}