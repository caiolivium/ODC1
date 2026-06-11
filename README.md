# ODC1

Guia para compilar e ligar código C e Assembly (.asm) juntos.

## Passo a passo

1) Montar o arquivo Assembly para objeto:

```bash
nasm -f elf32 arquivo.asm -o arquivo.o
```

2) Compilar o código C para objeto (com cabeçalhos e otimizações desejadas):

```bash
gcc -c -o arquivo_c.o arquivo.c
```

3) Ligar os objetos e gerar o executável:

```bash
gcc arquivo_c.o arquivo.o -o programa
```

4) Executar:

```bash
./programa
```

## Observações

- Se sua Assembly usa convenções de chamada C, exporte símbolos globais com `global nome_da_funcao`.
- Use a mesma convenção de chamada do Linux x86_64 (System V AMD64) ou a convenção de 32 bits adequada.
- Para 32 bits, troque `elf64` por `elf32` e use `gcc -m32` se o toolchain suportar.

## Exemplo mínimo (32 bits)

### arquivo.asm

```asm
global add_one
section .text

add_one:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    add eax, 1
    pop ebp
    ret
```

### main.c

```c
#include <stdio.h>

extern int add_one(int);

int main() {
    printf("%d\n", add_one(41));
    return 0;
}
```

## Comandos (32 bits)

```bash
nasm -f elf32 arquivo.asm -o arquivo.o
gcc -m32 -c -o arquivo_c.o main.c
gcc -m32 arquivo_c.o arquivo.o -o programa
./programa
```

