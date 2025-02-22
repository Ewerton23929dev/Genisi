#ifndef __JAVA_BIND_H
#define __JAVA_BIND_H

#include <java/jni.h>

#ifdef _cplusplus
extern "C" {
#endif

//ponte para c++.
#define GENISI_BIND_CPP(class, nome, retorno, ...) \
    extern "C" JNIEXPORT retorno JNICALL Java_##class##_##nome(JNIEnv* env, jobject obj, ##__VA_ARGS__)

#ifdef _cplusplus
}
#endif

// ponte para C.
#define GENISI_BIND_C(class, nome, retorno, ...) \
    JNIEXPORT retorno JNICALL Java_##class##_##nome(JNIEnv* env, jobject obj, ##__VA_ARGS__)

#endif