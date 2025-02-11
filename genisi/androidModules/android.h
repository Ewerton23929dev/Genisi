#ifndef GENISI_LIB
#define GENISI_LIB
/* 
Implementação do basico do sistema da lib funções de execução de binario em ambiente android e pegar arquitetura do android e verificação de root e logs android com entrada de AndroidLoggin. Sistema não incluido abiguidade de versão do android ou check.
*/
#pragma once
#define ANDROID_TMP "/data/local/tmp"
typedef enum {
     INFO,
     WARN,
     ERRO,
     DEBUG,
     FATAL,
     VERBOSE
} AndroidLoggin;
extern int android_runner(const char* bin);
extern const char* android_arch();
extern int android_isroot();
extern int android_log(AndroidLoggin mode,const char* tag,const char* fmt);

#endif