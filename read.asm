%define SIZEOF_TIME 680
%define OFFSET_QTD_JOGADORES 676

section .text
    global contarJogadoresTotal

contarJogadoresTotal:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi

    mov     esi, [ebp+8]    ; esi=base do array(ponteiro)
    mov     ecx, [ebp+12]   ; ecx=contador de times(total_times_atual)
    xor     eax, eax        ; eax=soma acumulada=0
    xor     ebx, ebx        ; ebx=índice i=0

.loop:
    cmp     ebx, ecx
    jge     .fim            ; se i >= total_times_atual, encerra

    mov     edx, ebx
    imul    edx, SIZEOF_TIME
    add     edx, esi
    add     edx, OFFSET_QTD_JOGADORES

    mov     edx, [edx]      ; edx=qtd_jogadores do time i
    add     eax, edx        ; soma += qtd_jogadores

    inc     ebx
    jmp     .loop

.fim:
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
