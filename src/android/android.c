#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <androidModules/android.h>
#include <string.h>
#include <android/log.h>

// constantes.
int androidDebug = true;
#define ANDROID_TMP "/data/local/tmp"

// sistema de log
int android_log(AndroidLoggin mode, const char* tag,const char* fmt, ...) {
  char buffer[600];
  va_list args;
  va_start(args,fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  struct tm *tm_info;
  tm_info = localtime(&ts.tv_sec);
  char type[500];
     switch (mode) {
          // cases de implementação.
          case INFO:
              strcpy(type,"INFO");
              __android_log_print(ANDROID_LOG_INFO,tag,"%s",fmt);
              break;
          case WARN:
             strcpy(type,"WARN");
              __android_log_print(ANDROID_LOG_WARN,tag,"%s",fmt);
              break;
          case ERRO:
              strcpy(type,"\033[31mERRO\033[0m");
              __android_log_print(ANDROID_LOG_ERROR,tag,"%s",fmt);
              break;
          case DEBUG:
              strcpy(type,"\033[33mDEBUG\033[0m");
              __android_log_print(ANDROID_LOG_DEBUG,tag,"%s",fmt);
              break;
          case FATAL:
              strcpy(type,"\033[31mFATAL\033[0m");
              __android_log_print(ANDROID_LOG_FATAL,tag,"%s",fmt);
              break;
          case VERBOSE:
              strcpy(type,"\033[35mVERBOSE\033[0m");
              __android_log_print(ANDROID_LOG_VERBOSE,tag,"%s",fmt);
              break;
          default:
             return 1;
     }
     if (androidDebug) {
       printf("[\033[32m%02d-%02d:%02d-%02d-%02d\033[0m] - %s:%s - %s\n",tm_info->tm_mon + 1,tm_info->tm_mday,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec,type,tag,buffer);
     }
     return 0;
}

//checa ser e root!
int android_isroot() {
    return getuid() == 0;
}

// pega a arquitera do sistema!
const char* android_arch() {
    #if defined(__x86_64__) || defined(__amd64__)
        return "x86_64";
    #elif defined(__i386__)
        return "x86";
    #elif defined(__aarch64__)
        return "arm64";
    #elif defined(__arm__)
        return "arm";
    #elif defined(__mips__)
        return "mips";
    #elif defined(__riscv)
        return "riscv";
    #else
        return "unknown";
    #endif
}

// Função que executa binarios em ambiente android.
int android_runner(const char* bin) {
    if (access(bin, X_OK) == 0) {
        return 1;
    }
    //buffer para cada chamada.
    char cmdBuffer[600];
    char chmodBuffer[600];
    char destPath[700];
    char RunnerBuffer[70];

    snprintf(destPath, sizeof(destPath), "%s/%s", ANDROID_TMP, strrchr(bin, '/') ? strrchr(bin, '/') + 1 : bin);
    snprintf(cmdBuffer, sizeof(cmdBuffer), "cp %s %s", bin, destPath);
    snprintf(chmodBuffer, sizeof(chmodBuffer), "chmod +x %s", destPath);
  
   //chama pelo nome que esta no buffer  snprintf(RunnerBuffer,sizeof(RunnerBuffer,".%s/%s",ANDROID_TMP,strrchr(bin, '/') ? strrchr(bin, '/') + 1 : bin);
    // executa!
    if (system(cmdBuffer) != 0) {
        android_log(ERRO, "genisi", "Erro ao copiar o binário!");
        perror("Erro ao copiar o binário");
        return -1;
    }
    if (system(chmodBuffer) != 0) {
        android_log(ERRO, "genisi", "Erro ao alterar permissões!");
        perror("Erro ao alterar permissões");
        return -1;
    }
    if (system(RunnerBuffer) != 0) {
       android_log(FATAL, "genisi", "Erro fatal na execução do cache!");
       perror("Erro fatal na execução do cache!");
       return -1;
    }
    return 0;
}