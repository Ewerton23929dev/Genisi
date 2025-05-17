#ifndef JNI_H_INCLUDED
#define JNI_H_INCLUDED
#include <java/jni.h>
#endif
#include <androidModules/android.h>

//java get string.
__attribute__((used)) const char* java_getString(JNIEnv* env, jstring str) {
    const char* result = (*env)->GetStringUTFChars(env, str, NULL);
    if (result == NULL) {
        android_log(ERRO, "genisi_java", "Erro to get string in java!");
        return NULL;
    }
    return result;
}

// free buffer alocated for get string.
__attribute__((used)) void java_releaseString(JNIEnv* env, jstring str, const char* chars) {
    (*env)->ReleaseStringUTFChars(env, str, chars);
}

//call java object.
__attribute__((used)) jobject java_callObject(JNIEnv* env, jobject obj, const char* methodName, const char* methodSignature) {
    jclass cls = (*env)->GetObjectClass(env, obj);
    if (cls == NULL)
    {
      android_log(ERRO,"genisi_java","Class not find!");
      return NULL;
    }
    jmethodID mid = (*env)->GetMethodID(env, cls, methodName, methodSignature);
    if (mid == NULL) {
        android_log(ERRO, "genisi_java", "Erro to call object! %s signature %s", methodName, methodSignature);
        return NULL;
    }
    return (*env)->CallObjectMethod(env, obj, mid);
}

// create object.
__attribute__((used)) jobject java_createObject(JNIEnv* env, const char* className, const char* constructorSignature) {
    jclass cls = (*env)->FindClass(env, className);
    if (cls == NULL)
    {
      android_log(ERRO,"genisi_java","Class not find!");
      return NULL;
    }
    jmethodID ctor = (*env)->GetMethodID(env, cls, "<init>", constructorSignature);
    if (ctor == NULL)
    {
      android_log(ERRO,"genisi_java","Builder not find: %s",constructorSignature);
      return NULL;
    }
    return (*env)->NewObject(env, cls, ctor);
}