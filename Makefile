# Makefile - VCT CRUD (C + NASM x86 32-bit)
#
# Requer: nasm, gcc com suporte a -m32 (pacote gcc-multilib no Ubuntu/Debian)
#
# Uso:
#   make        -> compila tudo e gera o executável "vct"
#   make run    -> compila e executa
#   make clean  -> remove objetos e executável

CC = gcc
ASM = nasm
CFLAGS = -m32 -Wall -Wextra -g
ASFLAGS = -f elf32
LDFLAGS = -m32

TARGET = vct

C_SOURCES = main.c dados.c create.c read.c update.c delete.c
ASM_SOURCES = create.asm read.asm update.asm delete.asm

C_OBJS = $(C_SOURCES:.c=.o)
# Objetos do NASM recebem sufixo _asm para não colidir com os .o dos .c
# (create.asm -> create_asm.o, etc.)
ASM_OBJS = $(ASM_SOURCES:.asm=_asm.o)

OBJS = $(C_OBJS) $(ASM_OBJS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c dados.h
	$(CC) $(CFLAGS) -c $< -o $@

%_asm.o: %.asm
	$(ASM) $(ASFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) valorant_vct.txt

.PHONY: all run clean
