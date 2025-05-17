#ifndef __JAVA_BIND_H
#define __JAVA_BIND_H

#include <java/jni.h>

#ifdef __cplusplus
extern "C" {
#endif

// Ponte para C++
#define GENISI_BIND_CPP(class, nome, retorno, ...) \
    extern "C" JNIEXPORT retorno JNICALL Java_##class##_##nome(JNIEnv* env, jobject obj, ##__VA_ARGS__)

// Ponte para C puro
#define GENISI_BIND_C(class, nome, retorno, ...) \
    JNIEXPORT retorno JNICALL Java_##class##_##nome(JNIEnv* env, jobject obj, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // __JAVA_BIND_H