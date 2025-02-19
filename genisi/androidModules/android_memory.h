#ifndef __ANDROID_MEM_H
#define __ANDROID_MEM_H

#ifdef _cplusplus
extern "C" {
#endif

#pragma once
/*
Implementação do sistema de memoria alocaçao no ambiente android.
*/

#define MEM_INIT 500
/**
 * @brief Lista de alocamentos.
 *
 * Lista de allocamentos.
 * 
 */
void** androidAllocs;
int androidMax;
int androidSize;
long int androidSpace;
/**
 * @brief Inicia a memoria.
 *
 * Funçao que inicia a memoria.
 * 
 * @param 
 * @return int
 */
int android_memoryInit();
/**
 * @brief Alocação de memoria.
 *
 * Responsavel por alocar memoria.
 * 
 * @param size_t size
 * @return void*
 */
void* android_malloc(size_t size);
/**
 * @brief libera memoria especifica. 
 *
 * @param void* prt
 * @return int
 */
int android_free(void* prt);
/**
 * @brief Fecha todas as memorias.
 *
 * @param 
 * @return
 */
void android_memoryClose();

#ifdef _cplusplus
}
#endif

#endif