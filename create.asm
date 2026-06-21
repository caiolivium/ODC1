; ============================================================
; create.asm
; Módulo CREATE - parte em Assembly (NASM, sintaxe Intel, 32-bit, ELF, cdecl)
;
; int gerarProximoId(int proximo_id_atual);
;
; Recebe o valor atual do contador global "proximo_id" e
; retorna o valor que deve ser usado como ID do novo time/jogador,
; já incrementado. Também garante que o ID nunca seja menor que 1
; (validação simples, caso o valor recebido esteja corrompido).
;
; Equivalente em C seria:
;
;     int gerarProximoId(int proximo_id_atual) {
;         if (proximo_id_atual < 1) {
;             proximo_id_atual = 1;
;         }
;         return proximo_id_atual;
;     }
;
; (O incremento do contador global "proximo_id++" continua sendo
;  feito em C, em create.c, após receber o valor validado daqui.)
; ============================================================

section .text
    global gerarProximoId

gerarProximoId:
    ; --- prólogo (convenção cdecl) ---
    push    ebp
    mov     ebp, esp

    ; argumento: [ebp+8] = proximo_id_atual
    mov     eax, [ebp+8]

    ; validação: se proximo_id_atual < 1, força para 1
    cmp     eax, 1
    jge     .fim
    mov     eax, 1

.fim:
    ; resultado já está em eax (valor de retorno em cdecl)

    ; --- epílogo ---
    mov     esp, ebp
    pop     ebp
    ret
