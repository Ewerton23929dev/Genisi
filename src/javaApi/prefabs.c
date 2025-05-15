#ifndef JNI_H_INCLUDED
#define JNI_H_INCLUDED
#include <java/jni.h>
#endif
#include <androidModules/android.h>
#include <androidModules/android_sys.h>
#include <androidModules/android_linker.h>
#include <androidModules/android_memory.h>

// Java_Genisi_getVersion
JNIEXPORT jstring JNICALL Java_Genisi_getVersion(JNIEnv *env, jobject obj)
{
    return (*env)->NewStringUTF(env, "Genisi v1.0");
}

// Java_Genisi_InitMemory
JNIEXPORT void JNICALL Java_Genisi_InitMemory(JNIEnv *env, jobject obj) {
    android_memoryInit();
}

// Java_Genisi_CloseMemory
JNIEXPORT void JNICALL Java_Genisi_CloseMemory(JNIEnv *env, jobject obj) {
    android_memoryClose();
}