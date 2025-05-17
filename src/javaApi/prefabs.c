#ifndef JNI_H_INCLUDED
#define JNI_H_INCLUDED
#include <java/jni.h>
#endif
#include <androidModules/android.h>
#include <androidModules/android_sys.h>
#include <androidModules/android_linker.h>
#include <androidModules/android_memory.h>

// Java_Genisi_getVersion
__attribute__((used)) JNIEXPORT jstring JNICALL Java_Genisi_getVersion(JNIEnv *env, jobject obj)
{
    return (*env)->NewStringUTF(env, "Genisi v1.0");
}

// Java_Genisi_InitMemory
__attribute__((used)) JNIEXPORT void JNICALL Java_Genisi_InitMemory(const JNIEnv *env, jobject obj) {
    android_memoryInit();
}

// Java_Genisi_CloseMemory
__attribute__((used)) JNIEXPORT void JNICALL Java_Genisi_CloseMemory(const JNIEnv *env, jobject obj) {
    android_memoryClose();
}