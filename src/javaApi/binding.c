#ifndef JNI_H_INCLUDED
#define JNI_H_INCLUDED
#include <java/jni.h>
#endif
#include <androidModules/android.h>

//ponte para c++.
#define GENISI_BIND_CPP(class, nome, retorno, ...) \
    extern "C" JNIEXPORT retorno JNICALL Java_##class_##nome(JNIEnv* env, jobject obj, __VA_ARGS__)

// ponte para C.
#define GENISI_BIND_C(class, nome, retorno, ...) \
    JNIEXPORT retorno JNICALL Java_##class_##nome(JNIEnv* env, jobject obj, __VA_ARGS__)