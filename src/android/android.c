#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <androidModules/android.h>
#include <string.h>
#include <android/log.h>

// constantes.
int androidDebug = ON;
const char* pathLoggin;

__attribute__((used)) void android_FileLog(const char* path) {
  pathLoggin = path;
}

// sistema de log
__attribute__((used)) int android_log(AndroidLoggin mode, const char* tag,const char* fmt, ...) {
  char buffer[1000];
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
              __android_log_print(ANDROID_LOG_INFO,tag,"%s",buffer);
              break;
          case WARN:
             strcpy(type,"WARN");
              __android_log_print(ANDROID_LOG_WARN,tag,"%s",buffer);
              break;
          case ERRO:
              strcpy(type,"\033[31mERRO\033[0m");
              __android_log_print(ANDROID_LOG_ERROR,tag,"%s",buffer);
              break;
          case DEBUG:
              strcpy(type,"\033[33mDEBUG\033[0m");
              __android_log_print(ANDROID_LOG_DEBUG,tag,"%s",buffer);
              break;
          case FATAL:
              strcpy(type,"\033[31mFATAL\033[0m");
              __android_log_print(ANDROID_LOG_FATAL,tag,"%s",buffer);
              break;
          case VERBOSE:
              strcpy(type,"\033[35mVERBOSE\033[0m");
              __android_log_print(ANDROID_LOG_VERBOSE,tag,"%s",buffer);
              break;
          default:
             return 1;
     }
     if (androidDebug == ON) {
       if (!pathLoggin) {
         printf("[\033[32m%02d-%02d:%02d-%02d-%02d\033[0m] - %s:%s - %s\n",tm_info->tm_mon + 1,tm_info->tm_mday,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec,type,tag,buffer);
         return 0;
       }
       FILE *logfile = fopen(pathLoggin, "a");
       if (!logfile) {
       printf("[\033[32m%02d-%02d:%02d-%02d-%02d\033[0m] - %s:%s - %s\n",tm_info->tm_mon + 1,tm_info->tm_mday,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec,type,tag,buffer);
       return 1;
       }
       printf("[\033[32m%02d-%02d:%02d-%02d-%02d\033[0m] - %s:%s - %s\n",tm_info->tm_mon + 1,tm_info->tm_mday,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec,type,tag,buffer);
       fprintf(logfile, "[%02d-%02d:%02d-%02d-%02d] - %s:%s - %s\n",tm_info->tm_mon + 1,tm_info->tm_mday,tm_info->tm_hour,tm_info->tm_min,tm_info->tm_sec,type,tag,buffer);
       fclose(logfile);
     }
     return 0;
}
