#include <androidModules/android.h>
#include <androidModules/android_memory.h>
#include <stdlib.h>

#define SIZE (10 * 1024)

#define CHECK_ALLOC(ptr, msg) if (!(ptr)) { android_log(FATAL, "genisi", msg); return 1; }

// partições.
Partion* USER = NULL;
Partion* GENISI = NULL;
Partion* JAVA = NULL;

int android_memoryInit()
{
  USER = malloc(sizeof(Partion));
  GENISI = malloc(sizeof(Partion));
  JAVA = malloc(sizeof(Partion));
  
  CHECK_ALLOC(USER,"Erro to allocated USER partition!");
  CHECK_ALLOC(GENISI,"Erro to allocated GENISI partition!");
  CHECK_ALLOC(JAVA,"Erro to allocated JAVA partition!");
  
  USER->usedsize = 0;
  USER->size_bytes = SIZE;
  GENISI->usedsize = 0;
  GENISI->size_bytes = SIZE;
  JAVA->size_bytes = SIZE;
  JAVA->usedsize = 0;
  
  USER->memory = malloc((SIZE / sizeof(Alloc)) * sizeof(Alloc*));
  GENISI->memory = malloc((SIZE / sizeof(Alloc)) * sizeof(Alloc*));
  JAVA->memory = malloc((SIZE / sizeof(Alloc)) * sizeof(Alloc*));
  if (!USER->memory || !GENISI->memory || !JAVA->memory) {
    android_log(FATAL, "genisi", "Failed to allocate partition memory");
    return 2;
  }
  android_log(INFO, "genisi", "Partitions allocated successfully!");
  return 0;
}

Alloc* android_malloc(unsigned int size, androidSpaces sp)
{
  Alloc* diretive = malloc(sizeof(Alloc));
  void* prt = malloc(size);
  if (!prt || !diretive) {
    android_log(ERRO, "genisi", "Error allocating pointer %p!", diretive);
    return NULL;
  }
  diretive->ptr = prt;
  diretive->size = size;
  /*
  Melhoria:
    Ao invez de usar switch para cada partições usar um LINKER para indicar a partição e apenas escrever uma logica.
  */
  switch (sp) {
    case USER_SPACE:
    diretive->pose = USER->usedsize;
    USER->memory[USER->usedsize] = diretive;
    USER->size_bytes += size;
    USER->usedsize++;
    break;
    case GENISI_SPACE:
    diretive->pose = GENISI->usedsize;
    GENISI->memory[GENISI->usedsize] = diretive;
    GENISI->size_bytes += size;
    GENISI->usedsize++;
    break;
    case JAVA_SPACE:
    diretive->pose = JAVA->usedsize;
    JAVA->memory[JAVA->usedsize] = diretive;
    break;
  }
  android_log(INFO, "genisi", "Successfully allocated pointer %p in %d", diretive, diretive->pose);
  return diretive;
}

void android_free(Alloc* ptr, androidSpaces sp)
{
  int pose = ptr->pose;
  free(ptr->ptr);
  /*
  Melhoria:
    Ao invez de usar switch para cada partições usar um LINKER para indicar a partição e apenas escrever uma logica.
  */
  switch (sp) {
    case USER_SPACE:
    if (pose+1 < USER->usedsize) {
      USER->memory[pose] = USER->memory[pose+1];
      USER->memory[pose+1]->pose--;
    } else {
      USER->memory[pose] = NULL;
    }
    free(ptr);
    USER->usedsize--;
    break;
    case GENISI_SPACE:
    if (pose+1 < GENISI->usedsize) {
      GENISI->memory[pose] = GENISI->memory[pose+1];
      GENISI->memory[pose+1]->pose--;
    } else {
      GENISI->memory[pose] = NULL;
    }
    free(ptr);
    GENISI->usedsize--;
    break;
    case JAVA_SPACE:
    if (pose+1 < JAVA->usedsize) {
      JAVA->memory[pose] = JAVA->memory[pose+1];
      JAVA->memory[pose+1]->pose--;
    } else {
      JAVA->memory[pose] = NULL;
    }
    free(ptr);
    JAVA->usedsize--;
    break;
  }
  android_log(INFO, "genisi", "Pointer deleted at: %d", pose);
}

void android_memoryClose()
{
  if (GENISI == NULL || USER == NULL || JAVA == NULL) {
    android_log(INFO, "genisi", "Partitions be closed!");
    return;
  }
  if (0 < USER->usedsize || 0 < GENISI->usedsize || JAVA->usedsize) {
    free(USER->memory);
    free(USER);
    free(GENISI->memory);
    free(JAVA->memory);
    free(JAVA);
    free(GENISI);
    android_log(INFO, "genisi", "Partitions released successfully!");
    return;
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
  USER = NULL;
  GENISI = NULL;
  JAVA = NULL;
  android_log(INFO, "genisi", "Partitions released successfully!");
}