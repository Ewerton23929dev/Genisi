#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <androidModules/android.h>
#include <string.h>
#include <android/log.h>

// constantes.
#define ANDROID_TMP "/data/local/tmp"

// sistema de log
int android_log(AndroidLoggin mode, const char* tag,const char* fmt) {
     switch (mode) {
          // cases de implementação.
          case INFO:
              printf("[INFO:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_INFO,tag,"%s",fmt);
          case WARN:
              printf("[WARN:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_WARN,tag,"%s",fmt);
          case ERRO:
              printf("[ERRO:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_ERROR,tag,"%s",fmt);
          case DEBUG:
              printf("[DEBUG:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_DEBUG,tag,"%s",fmt);
          case FATAL:
              printf("[FATAL:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_FATAL,tag,"%s",fmt);
          case VERBOSE:
              printf("[VERBOSE:%s] - %s",tag,fmt);
              __android_log_print(ANDROID_LOG_VERBOSE,tag,"%s",fmt);
          default:
             return 1;
     }
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
        perror("Erro ao copiar o binário");
        return -1;
    }
    if (system(chmodBuffer) != 0) {
        perror("Erro ao alterar permissões");
        return -1;
    }
    if (system(RunnerBuffer) != 0) {
       perror("Erro fatal na execução do cache!");
       return -1;
    }
    return 0;
}