# **Genisi Android**
![version](https://img.shields.io/badge/Version-1.0.5-green) ![C](https://img.shields.io/badge/Linguagem-C-blue?logo=c) ![Linux](https://img.shields.io/badge/Plataforma_para-Linux-black?logo=linux) ![Android](https://img.shields.io/badge/Feito_para-Android-green?logo=android) ![MIT License](https://img.shields.io/badge/License-MIT-blue.svg)

Genisi a biblioteca para suporte para android em C/C++.

## **Instalação:**
```bash
git clone https://github.com/Ewerton23929dev/Genisi.git
```
Clone o repositório e logo em seguida execute.
```bash
cd genisi
make
```
**Atenção**: Este projeto requer bibliotecas de ambiente android certifique-se que possui as bibliotecas para copilação.

Assim criará um arquivo chamado ``libgenisi.so`` atravez dele ja pode ser usado a biblioteca.

## **Uso:**
Para usar a biblioteca copie a pasta ``genisi`` que esta no diretorio principal do repositório ou use diretamente a pasta no copilador passando ``-I./genisi``.
```c
#include <AndroidModules/android.h>

// utilizando a função de log.
int main() {
   android_log(INFO,"exemplo","Hello World!");
   return 0;
}
```
Copile passando o diretorio ``genisi`` ou coloque em seus projetos!
Pode encontrar mais sobre na [WIKI](https://github.com/Ewerton23929dev/Genisi/wiki).

MIT License © 2025 Ewerton23929dev
