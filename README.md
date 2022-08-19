# Experimentos com Hashmap

Este repositório implementa um hashmap genérico com sondagem quadrática. Também há supporte para sondagem linar utilizando a flag de compilador `LINEAR_PROBING=1`.

## Requisitos

Para compilar este programa, serão necessários o g++ (C++ 17), _make_ e o módulo program_options da biblioteca Boost.

Dependendo de seu sistema, pode ser possível instalá-los com `sudo apt install build-essential libboost-all-dev`. 

### Desenvolvimento

Para o desenvolvimento é recomendado o clang-format. Você pode instalá-lo com `sudo apt install clang-format`
Também é recomendada a extensão [Clang-Format para VSCode](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format).

## Uso

- Instale os requisitos
- Clone este repositório
- Compilando e executando:
  - `make` para compilar e executar com parâmetros padrão
  - `make LINEAR_PROBING=1` para compilar e executar com sondagem linear (invés de quadrática)
  - `make hashmap` para compilar
  - `make run` para executar com parâmetros padrão
  - `make clean` para deletar arquivos gerados