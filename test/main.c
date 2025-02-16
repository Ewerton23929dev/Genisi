#include <AndroidModules/android_sys.h>
#include <AndroidModules/android.h>
#include <AndroidModules/android_memory.h>
#include <stdio.h>

int main() {
  AndroidGlobals infos = android_globals();
  printf("Infos %ld \n", infos.total_ram);
  printf("Versão: %d \n", get_android_version());
  android_log(INFO, "teste", "HELLO WORLD!");
  printf("Informaçoes do android_memory %d\n", android_memoryInit());
  void* prt = android_malloc(200);
  printf("Informaçoes do ponteiro: %p\n", prt);
  android_close();
  return 0;
}