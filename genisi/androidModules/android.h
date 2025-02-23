#ifndef GENISI_LIB
#define GENISI_LIB

#ifdef _cplusplus
extern "C" {
#endif
/* 
Implementação do basico do sistema da lib funções de execução de binario em ambiente android e pegar arquitetura do android e verificação de root e logs android com entrada de AndroidLoggin. Sistema não incluido abiguidade de versão do android ou check.
*/
#pragma once

/**
 * @brief Enum para opçoes do android_log
 *
 * Enun utilizando em androidDebug para ativar ou desativar os logs em shell.
 *
 */
typedef enum {
  OFF,
  ON
} androidMode;
/**
 * @brief enum para tipos de log.
 *
 *  Enum utilizando para tipos do android_log como primeiro paramentro.
 * 
 */
typedef enum {
     INFO,
     WARN,
     ERRO,
     DEBUG,
     FATAL,
     VERBOSE
} AndroidLoggin;

/**
 * @brief Variavel de log em shell.
 * 
 * Passe ON ou OFF para ter os logs em shell.
 *
 */
extern int androidDebug;

/**
 * @brief Funçao para logs.
 *
 * Funçao para logs.
 * 
 * @param AndroidLoggin mode, const char* tag, const char* fmt, ...
 * @return int 
 */
extern int android_log(AndroidLoggin mode,const char* tag,const char* fmt, ...);


#ifdef _cplusplus
}
#endif

#endif