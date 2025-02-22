#ifndef JNI_H_INCLUDED
#define JNI_H_INCLUDED
#include <java/jni.h>
#endif
#include <javaApi/binding.h>
#include <androidModules/android.h>
#include <androidModules/android_sys.h>
#include <androidModules/android_linker.h>
#include <androidModules/android_memory.h>

GENISI_BIND_C(Genisi, getVersion, jint, ...) {
  return get_android_version();
}