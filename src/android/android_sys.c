#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <androidModules/android_sys.h>
#include <android/versioning.h>
#include <android/log.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

// suporte para android 10++ api 29++
// Definição do enum para representar versões do Android

long int android_memoryLimits() {
    struct rlimit limit;
    getrlimit(RLIMIT_AS, &limit);
    return limit.rlim_cur;
}

AndroidGlobals android_globals() {
    AndroidGlobals global = {-1,-1,-1,-1};
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
       global.total_ram = info.totalram;
       global.free_ram = info.freeram;
       global.shared_ram = info.sharedram;
       global.proc = info.procs;
    } else {
      __android_log_print(ANDROID_LOG_ERROR, "genisi", "Error extracting globals!");
      perror("Error extracting globals!");
    }
    return global;
}

// Função que retorna o enum baseado no valor da API em tempo de execução
AndroidVersion get_android_version() {
    int api_level = android_get_device_api_level();  // Obtém a API real do sistema

    switch (api_level) {
        case 1: return ANDROID_BASE;
        case 3: return ANDROID_CUPCAKE;
        case 4: return ANDROID_DONUT;
        case 5: return ANDROID_ECLAIR;
        case 8: return ANDROID_FROYO;
        case 9: return ANDROID_GINGERBREAD;
        case 11: return ANDROID_HONEYCOMB;
        case 14: return ANDROID_ICE_CREAM_SANDWICH;
        case 16: return ANDROID_JELLY_BEAN;
        case 19: return ANDROID_KITKAT;
        case 21: return ANDROID_LOLLIPOP;
        case 23: return ANDROID_MARSHMALLOW;
        case 24: return ANDROID_NOUGAT;
        case 26: return ANDROID_OREO;
        case 28: return ANDROID_PIE;
        case 29: return ANDROID_10;
        case 30: return ANDROID_11;
        case 31: return ANDROID_12;
        case 32: return ANDROID_12L;
        case 33: return ANDROID_13;
        case 34: return ANDROID_14;
        default: return ANDROID_UNKNOWN;
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