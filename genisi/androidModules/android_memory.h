#ifndef __ANDROID_MEM_H
#define __ANDROID_MEM_H
#pragma once
#include <android/log.h>
#include <stddef.h>
/*
Implementação do sistema de memoria alocaçao no ambiente android.
*/

#define MEM_INIT 500
void** androidAllocs;
int androidMax;
int androidSize;
long int androidSpace;
int android_memoryInit();
void* android_malloc(size_t size);
int android_free(void* prt);
void android_close();
#endif