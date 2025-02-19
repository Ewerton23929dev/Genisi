#include <androidModules/android.h>
#include <androidModules/android_debug.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* android_goto_wrapper(void* arg) {
    android_goto_args* data = (android_goto_args*)arg;
    if (data->func) {
        int result = data->func(data->code, data->fixe);
        android_log(INFO, "genisi", "Threaded function exit code: %d", result);
    }
    free(data);
    return NULL;
}

int android_goto(goto_moldel func, int code, const char* fixe) {
    pthread_t thread;

    android_goto_args* data = malloc(sizeof(android_goto_args));
    if (!data) return -1;
    data->func = func;
    data->code = code;
    data->fixe = fixe;

    if (pthread_create(&thread, NULL, android_goto_wrapper, data) != 0) {
        android_log(ERRO, "genisi", "Error creating debug thread!");
        free(data);
        return -1;
    }
    pthread_detach(thread);
    return 0;
}