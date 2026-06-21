%define SIZEOF_TIME 680
%define OFFSET_ID 0

section .text
    global encontrarIndicePorId

encontrarIndicePorId:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi

    mov     esi, [ebp+8]    ; esi=base do array
    mov     ecx, [ebp+12]   ; ecx=total_times_atual
    mov     edx, [ebp+16]   ; edx=id procurado
    xor     ebx, ebx        ; ebx=indice i=0

.loop:
    cmp     ebx, ecx
    jge     .nao_encontrado ; se i >= total_times_atual, não achou

    mov     eax, ebx
    imul    eax, SIZEOF_TIME
    add     eax, esi
    add     eax, OFFSET_ID 

    mov     eax, [eax]       ; eax=id do time i
    cmp     eax, edx
    je      .encontrado      ; se id_atual == id procurado, retorna i

    inc     ebx
    jmp     .loop

.encontrado:
    mov     eax, ebx         ; retorno=i
    jmp     .fim

.nao_encontrado:
    mov     eax, -1          ; retorno = -1

.fim:
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
