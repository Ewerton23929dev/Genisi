#include <androidModules/android_sys.h>
#include <androidModules/android.h>
#include <androidModules/android_memory.h>
#include <stdio.h>

int main() {
  androidDebug = ON;
  android_FileLog("log/log.log");
  AndroidGlobals infos = android_globals();
  printf("Infos %ld \n", infos.total_ram);
  printf("Versão: %d \n", get_android_version());
  printf("Limites de memoria: %ld\n", infos.free_ram);
  android_log(INFO, "teste", "HELLO WORLD!");
  printf("Informaçoes do android_memory %d\n", android_memoryInit());
  Alloc* prt = android_malloc(500, USER_SPACE);
  printf("Informaçoes do ponteiro: %p\n", prt->ptr);
  android_free(prt, USER_SPACE);
  android_memoryClose();
  return 0;
}