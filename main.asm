; ============================================================
; main.asm
; Módulo auxiliar chamado por main.c
;
; void imprimirMenu(void);
;
; Imprime o menu principal do sistema VCT.
; Separado em ASM para demonstrar uso de section .data,
; chamada a printf e convenção cdecl sem argumentos.
; ============================================================

section .data
    menu db 10, "=========================================", 10,\
            "   GESTAO DE TIMES - VALORANT VCT",       10,\
            "=========================================", 10,\
            "1. Adicionar Time",                        10,\
            "2. Listar Times",                          10,\
            "3. Atualizar Time",                        10,\
            "4. Deletar Time",                          10,\
            "5. Adicionar Player ao Time",              10,\
            "6. Ver Lineup de um Time",                 10,\
            "0. Sair",                                  10,\
            "Escolha uma opcao:",                       10, 0

section .text
    global imprimirMenu
    extern printf

imprimirMenu:
    push    ebp
    mov     ebp, esp

    push    menu
    call    printf
    add     esp, 4

    mov     esp, ebp
    pop     ebp
    ret