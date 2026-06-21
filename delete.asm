%define SIZEOF_TIME 680

section .text
    global removerElemento

removerElemento:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi

    mov     ebx, [ebp+8]     ; ebx=base do array
    mov     edx, [ebp+12]    ; edx=ponteiro para total_times
    mov     ecx, [ebp+16]    ; ecx=indice

    mov     eax, [edx]       ; eax=total_times atual
    dec     eax              ; eax=total_times - 1 

.loop_shift:
    cmp     ecx, eax
    jge     .fim_loop        ; se i >= total_times - 1, encerra o shift

    mov     edi, ecx
    imul    edi, SIZEOF_TIME
    add     edi, ebx         ; edi=endereço de destino (tabela[i])

    mov     esi, ecx
    inc     esi
    imul    esi, SIZEOF_TIME
    add     esi, ebx         ; esi=endereço de origem (tabela[i+1])

    push    ecx              
    mov     ecx, SIZEOF_TIME
    rep     movsb
    pop     ecx              

    inc     ecx
    jmp     .loop_shift

.fim_loop:
    mov     ecx, [edx]       ; ecx=total_times atual
    dec     ecx
    mov     [edx], ecx       

    pop     edi
    pop     esi
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
