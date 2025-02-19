#ifndef __ANDROID_LINKER_H
#define __ANDROID_LINKER_H

#pragma once
#ifdef _cplusplus
extern "C" {
#endif

/**
 * @brief Struct do handle.
 *
 * Struct para o carregamento do handle.
 * 
 */

typedef struct {
  void* handle;
} GenisiHandle;

/**
 * @brief Carrega a biblioteca so.
 *
 * @param const char* path
 * @return void*
 */
void* android_dload(const char* path);
/**
 * @brief Pega funçao da biblioteca.
 *
 * @param GenisiHandle* handle
 * @return void*
 */
void* android_dlMethod(GenisiHandle* handle, const char* name);
/**
 * @brief Fecha a biblioteca. 
 *
 * @param GenisiHandle* handle
 * @return void
 */
void android_dlexit(GenisiHandle* handle);
GenisiHandle* android_autoLoad(const char* name);

#ifdef _cplusplus
}
#endif

#endif