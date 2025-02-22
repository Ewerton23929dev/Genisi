#ifndef __ANDROID_MEM_H
#define __ANDROID_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

#pragma once

typedef enum {
  USER_SPACE,
  GENISI_SPACE,
  JAVA_SPACE
} androidSpaces;
typedef struct {
  void* prt;
  int pose;
  int size;
} Alloc;
typedef struct {
  Alloc** memory;
  int usedsize;
  int size_bytes;
} Partion;

int android_memoryInit();
Alloc* android_malloc(int size, androidSpaces sp);
void android_free(Alloc* prt, androidSpaces sp);
void android_memoryClose();
#ifdef _cplusplus
}
#endif

#endif