#ifndef __ANDROID_DEBUG
#define __ANDROID_DEBUG

#pragma once
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Definição do modelo da função recebida.
 *
 * Este modelo de função.
 *
 */
typedef int (*goto_moldel)(int code, const char* fixe);

/**
 * @brief Modelo dos argumentos. 
 *
 * Struct de modelo dos paramentros.
 *
 */

typedef struct {
  goto_moldel func;
  int code;
  const char* fixe;
} android_goto_args;
/**
 * @brief Realiza um thead dedicada.
 *
 * Esta função cria uma thead dedicada para execução de uma função de forma interna ao programa.
 *
 * @param goto_model func, int code, const char* fixe. 
 * @return int 
 */
int android_goto(goto_moldel func, int code, const char* fixe);

#ifdef __cplusplus
}
#endif

#endif