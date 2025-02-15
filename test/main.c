#include <AndroidModules/android_sys.h>
#include <AndroidModules/android.h>
#include <stdio.h>

int main() {
  AndroidGlobals infos = android_globals();
  printf("Infos %ld \n", infos.total_ram);
  printf("Versão: %d \n", get_android_version());
  android_log(INFO, "teste", "HELLO WORLD!");
  return 0;
}