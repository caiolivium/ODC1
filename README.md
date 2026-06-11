# ODC1

Comandos para compilar/ligar código C e assembly (.asm) juntos (exemplos para Linux x86_64 usando NASM):

1) Montar o arquivo assembly para objeto:

	nasm -f elf32 arquivo.asm -o arquivo.o

2) Compilar o código C para objeto (com cabeçalhos e otimizações desejadas):

	gcc -c -o arquivo_c.o arquivo.c

3) Ligar os objetos e gerar executável:

	gcc arquivo_c.o arquivo.o -o programa

4) Executar:

	./programa

Observações:
- Se sua assembly usa convenções de chamada C, exporte símbolos globais (por exemplo: global func_name) e use a mesma convenção (sysv AMD64 para Linux).
- Para 32 bits troque "elf64" por "elf32" e use gcc -m32 se o toolchain suportar.

Exemplo mínimo (32 bits):

- arquivo.asm:
  global add_one
  section .text
  add_one:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    add eax, 1
    pop ebp
    ret

- main.c:
  #include <stdio.h>
  extern int add_one(int);
  int main(){ printf("%d\n", add_one(41)); return 0; }

Comandos (32 bits):
  nasm -f elf32 arquivo.asm -o arquivo.o
  gcc -m32 -c -o arquivo_c.o main.c
  gcc -m32 arquivo_c.o arquivo.o -o programa
  ./programa

