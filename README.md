# **GenesisLib**

**GenesisLib** é uma biblioteca em C que fornece uma abstração para o sistema Android. O objetivo do projeto é facilitar a interação com o Android, fornecendo funções e módulos reutilizáveis para tarefas comuns, como gerenciamento de logs, verificação de root, e obtenção de informações do sistema Android.

## **Descrição**

GenesisLib é uma biblioteca que abstrai várias funcionalidades do sistema Android para facilitar o desenvolvimento de aplicativos e ferramentas que precisem interagir com o sistema operacional. A biblioteca inclui funções como:

- **Gerenciamento de logs**: Funções para logar mensagens de diferentes níveis de gravidade.
- **Verificação de root**: Função para verificar se o dispositivo Android está "rootado".
- **Informações sobre o sistema**: Função para obter a versão do Android em execução.

A biblioteca foi projetada para ser leve e de fácil integração em projetos C, proporcionando uma maneira simples e eficiente de trabalhar com o sistema Android em nível baixo.

## **Funcionalidades**

- `android_log`: Função para logar mensagens com diferentes níveis de severidade.
- `android_isroot`: Função que verifica se o dispositivo está rootado.
- `get_android_version`: Função que retorna a versão do sistema Android em execução.
- `android_runner`: Função para executar comandos específicos no Android.
- `android_arch`: Função que retorna a arquitetura do dispositivo Android.
- `android_globals`: Variáveis globais que armazenam configurações específicas do Android.

## **Estrutura do Projeto.
- **src/**: Contém o código-fonte da biblioteca.
- **include/**: Contém os arquivos de cabeçalho, onde as funções da biblioteca são declaradas.
- **Makefile**: Arquivo para compilar e gerar a biblioteca.

## **Instalação**

Para usar a biblioteca **GenesisLib** em seu projeto, basta seguir os passos abaixo:

### **1. Clonar o repositório:**
```bash
git clone https://github.com/seuusuario/genesislib.git

2. Compilar a biblioteca:

cd genesislib
make
```
Isso irá gerar o arquivo libgenesis.so (ou o arquivo compilado apropriado).

3. Incluir no seu projeto:

E vincule a biblioteca ao seu projeto durante a compilação, incluindo o diretório include e o arquivo libgenesis.a.

# **Exemplo de Uso**

Aqui está um exemplo simples de como utilizar a biblioteca GenesisLib:
```c
#include "genesi/AndroidModules/android.h"

int main() {
    // Exemplo de uso do log
    android_log(LOG_INFO, "Main", "Iniciando o sistema");

    // Verificar se o dispositivo está rootado
    if (android_isroot()) {
        android_log(LOG_WARN, "Root Check", "O dispositivo está rootado");
    }

    // Obter versão do Android
    AndroidVersion *version = get_android_version();
    android_log(LOG_INFO, "Android Version", version);

    return 0;
}
```
# **Contribuição**

Se você deseja contribuir para o projeto GenesisLib, fique à vontade para abrir issues ou pull requests. Todos os tipos de contribuições são bem-vindos!

1. Faça um fork do repositório.


2. Crie uma branch para a sua contribuição:` git checkout -b minha-contribuicao`.


3. Faça suas alterações e commit:` git commit -am 'Adiciona nova funcionalidade' `.


4. Envie o pull request.



# **Licença**

Este projeto está licenciado sob a MIT License - veja o arquivo LICENSE para mais detalhes.
