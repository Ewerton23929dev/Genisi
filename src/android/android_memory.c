#include <androidModules/android.h>
#include <androidModules/android_memory.h>
#include <stdlib.h>

#define SIZE (10 * 1024)

// partições.
Partion* USER = NULL;
Partion* GENISI = NULL;
Partion* JAVA = NULL;

int android_memoryInit() {
  USER = malloc(sizeof(Partion));
  GENISI = malloc(sizeof(Partion));
  JAVA = malloc(sizeof(Partion));
  if (!USER) {
    android_log(FATAL, "genisi", "Falha ao montar partiçao de memoria USER!");
    return 1;
  }
  if (!GENISI) {
    android_log(FATAL, "genisi", "Falha ao montar partiçao de memoria GENISI!");
    return 1;
  }
  if (!JAVA) {
    android_log(FATAL, "genisi", "Falha ao alocar partiçao de memoria JAVA!");
  }
  
  USER->usedsize = 0;
  USER->size_bytes = SIZE;
  GENISI->usedsize = 0;
  GENISI->size_bytes = SIZE;
  JAVA->size_bytes = SIZE;
  JAVA->usedsize = 0;
  
  USER->memory = malloc(SIZE * sizeof(Alloc));
  GENISI->memory = malloc(SIZE * sizeof(Alloc));
  JAVA->memory = malloc(SIZE * sizeof(Alloc));
  if (!USER->memory || !GENISI->memory || !JAVA->memory) {
    android_log(FATAL, "genisi", "Falha ao alocar memoria das partiçoes");
    return 2;
  }
  android_log(INFO, "genisi", "Partiçoes alocadas com sucesso!");
  return 1;
}

Alloc* android_malloc(int size, androidSpaces sp) {
  Alloc* diretive = malloc(sizeof(Alloc));
  void* prt = malloc(size);
  if (!prt || !diretive) {
    android_log(ERRO, "genisi", "Erro ao alocar ponteiro!");
    return NULL;
  }
  diretive->prt = prt;
  diretive->size = size;
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
  android_log(INFO, "genisi", "Ponteiro alocado com sucesso %p em %d", diretive, diretive->pose);
  return diretive;
}

void android_free(Alloc* prt, androidSpaces sp) {
  int pose = prt->pose;
  switch (sp) {
    case USER_SPACE:
    free(prt->prt);
    if (pose+1 < USER->usedsize) {
      USER->memory[pose] = USER->memory[pose+1];
      USER->memory[pose+1]->pose--;
    } else {
      USER->memory[pose] = NULL;
    }
    free(prt);
    break;
    case GENISI_SPACE:
    free(prt->prt);
    if (pose+1 < USER->usedsize) {
      USER->memory[pose] = USER->memory[pose+1];
      USER->memory[pose+1]->pose--;
    } else {
      USER->memory[pose] = NULL;
    }
    free(prt);
    break;
    case JAVA_SPACE:
    free(prt->prt);
    if (pose+1 < JAVA->usedsize) {
      JAVA->memory[pose] = JAVA->memory[pose+1];
      JAVA->memory[pose+1]->pose--;
    } else {
      JAVA->memory[pose] = NULL;
    }
    free(prt);
    break;
  }
  android_log(INFO, "genisi", "Ponteiro eliminado em: %d", pose);
}

void android_memoryClose() {
  if (GENISI == NULL || USER == NULL || JAVA == NULL) {
    android_log(ERRO, "genisi", "Partiçoes fechadas!");
    return;
  }
  if (0 < USER->usedsize || 0 < GENISI->usedsize || JAVA->usedsize) {
    free(USER->memory);
    free(USER);
    free(GENISI->memory);
    free(JAVA->memory);
    free(JAVA);
    free(GENISI);
    android_log(INFO, "genisi", "Partiçoes limpas liberadas!");
    return;
  }
  for (int i = 0; i < USER->usedsize; i++) {
    free(USER->memory[i]->prt);
    free(USER->memory[i]);
  }
  for (int i = 0; i < GENISI->usedsize; i++) {
    free(GENISI->memory[i]->prt);
    free(GENISI->memory[i]);
  }
  for (int i = 0; i < JAVA->usedsize; i++) {
    free(JAVA->memory[i]->prt);
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
  android_log(INFO, "genisi", "Partiçoes liberadas com sucesso!");
}