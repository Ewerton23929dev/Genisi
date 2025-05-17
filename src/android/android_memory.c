#include <androidModules/android.h>
#include <androidModules/android_memory.h>
#include <stdlib.h>

#define SIZE (10 * 1024)

#define CHECK_ALLOC(ptr) if (!(ptr)) { goto ERRO_PARTITION; }

#define INIT_PARTION(p) \
  p->usedsize = 0; \
  p->size_bytes = SIZE; \
  p->memory = malloc(SIZE * sizeof(Alloc*)); \
  CHECK_ALLOC(p->memory)

static int total_allocs = 0;
static int total_free = 0;

// partições.
Partion* USER = NULL;
Partion* GENISI = NULL;
Partion* JAVA = NULL;

__attribute__((used)) int android_memoryInit()
{
  USER = malloc(sizeof(Partion));
  GENISI = malloc(sizeof(Partion));
  JAVA = malloc(sizeof(Partion));
  
  CHECK_ALLOC(USER);
  CHECK_ALLOC(GENISI);
  CHECK_ALLOC(JAVA);
  INIT_PARTION(USER);
  INIT_PARTION(GENISI);
  INIT_PARTION(JAVA);
  
  android_log(INFO, "genisi", "Partitions allocated successfully!");
  return 0;
  
  ERRO_PARTITION: // goto
  free(GENISI);
  free(USER);
  free(JAVA);
  android_log(ERRO,"genisi","Erro to alocated partition!");
  return 1;
}

static Partion* get_partion(androidSpaces sp)
{
  /* 
    Retorna a partição do tipo.
  */
  switch (sp) {
    case USER_SPACE:
    return USER;
    case GENISI_SPACE:
    return GENISI;
    case JAVA_SPACE:
    return JAVA;
    default:
    android_log(ERRO,"genisi","Invalid space!");
    return NULL;
  }
}

static const char* get_namePartion(androidSpaces sp)
{
  switch (sp) {
    case USER_SPACE:
    return "USER";
    case JAVA_SPACE:
    return "JAVA";
    case GENISI_SPACE:
    return "GENISI";
  }
}
__attribute__((used)) Alloc* android_malloc(unsigned int size, androidSpaces sp)
{
  Alloc* diretive = malloc(sizeof(Alloc));
  void* prt = malloc(size);
  if (!prt || !diretive) {
    free(prt);
    free(diretive);
    android_log(ERRO, "genisi", "Error allocating pointer in %s!", get_namePartion(sp));
    return NULL;
  }
  diretive->ptr = prt;
  diretive->size = size;
  Partion* linker = get_partion(sp);
  diretive->pose = linker->usedsize;
    linker->memory[linker->usedsize] = diretive;
  linker->size_bytes += size;
  linker->usedsize++;
  android_log(INFO, "genisi", "Successfully allocated pointer %p in %s", diretive, get_namePartion(sp));
  total_allocs++;
  return diretive;
}

__attribute__((used)) void android_free(Alloc* ptr, androidSpaces sp)
{
  int pose = ptr->pose;
  free(ptr->ptr);
  Partion* linker = get_partion(sp);
 for (int i = pose; i < linker->usedsize - 1; i++) {
    linker->memory[i] = linker->memory[i + 1];
    linker->memory[i]->pose = i;
  }
  linker->memory[linker->usedsize - 1] = NULL;
  linker->usedsize--;
  free(ptr);
  android_log(INFO, "genisi", "Pointer deleted in %s to %d", get_namePartion(sp), pose);
  total_free++;
}

__attribute__((used)) void android_memoryClose()
{
  android_log(INFO,"genisi","total allocs: %d!",total_allocs);
  android_log(INFO,"genisi","total free: %d!",total_free);
  if (GENISI == NULL || USER == NULL || JAVA == NULL) {
    goto END_MEMORY_CLOSE;
  }
  if (USER->usedsize == 0 && GENISI->usedsize == 0 && JAVA->usedsize == 0)
  {
    free(USER->memory);
    free(GENISI->memory);
    free(JAVA->memory);
    free(USER);
    free(GENISI);
    free(JAVA);
    goto END_MEMORY_CLOSE;
  }
  for (int i = 0; i < USER->usedsize; i++) {
    free(USER->memory[i]->ptr);
    free(USER->memory[i]);
  }
  for (int i = 0; i < GENISI->usedsize; i++) {
    free(GENISI->memory[i]->ptr);
    free(GENISI->memory[i]);
  }
  for (int i = 0; i < JAVA->usedsize; i++) {
    free(JAVA->memory[i]->ptr);
    free(JAVA->memory[i]);
  }
  free(USER->memory);
  free(USER);
  free(GENISI->memory);
  free(GENISI);
  free(JAVA->memory);
  free(JAVA);
  END_MEMORY_CLOSE: // goto
  USER = NULL;
  GENISI = NULL;
  JAVA = NULL;
  android_log(INFO, "genisi", "Partitions released successfully!");
  return;
}