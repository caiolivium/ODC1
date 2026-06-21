; ============================================================
; create.asm
; Módulo CREATE - parte em Assembly (NASM, sintaxe Intel, 32-bit, ELF, cdecl)
;
; Funções implementadas aqui (critério: laço simples sobre array,
; aritmética/comparação pura, acesso direto a campos de struct).
; Tudo que envolve I/O (scanf/fgets/printf) ou lógica de negócio
; ramificada permanece em create.c.
;
;   int  gerarProximoId(int proximo_id_atual);
;   int  limiteAtingido(int valor_atual, int limite_maximo);
;
; NOTA: encontrarIndicePorId NÃO está aqui — segundo dados.h ela
; pertence ao módulo update.asm. create.c apenas a CHAMA (a
; declaração já vem de dados.h); a definição mora em update.asm.
; ============================================================

section .text
    global gerarProximoId
    global limiteAtingido

; ------------------------------------------------------------
; int gerarProximoId(int proximo_id_atual);
;
; Recebe o valor atual do contador global "proximo_id" e
; retorna o valor que deve ser usado como ID do novo time/jogador.
; Garante que o ID nunca seja menor que 1.
;
; Equivalente em C:
;     int gerarProximoId(int proximo_id_atual) {
;         if (proximo_id_atual < 1) proximo_id_atual = 1;
;         return proximo_id_atual;
;     }
; ------------------------------------------------------------
gerarProximoId:
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp+8]        ; eax = proximo_id_atual
    cmp     eax, 1
    jge     .fim_gerar
    mov     eax, 1
.fim_gerar:
    ; resultado em eax (retorno cdecl)

    mov     esp, ebp
    pop     ebp
    ret


; ------------------------------------------------------------
; int limiteAtingido(int valor_atual, int limite_maximo);
;
; Comparação pura, reutilizada tanto para checar
; "total_times >= MAX_TIMES" quanto "qtd_jogadores >= MAX_JOGADORES".
; Retorna 1 (verdadeiro) se valor_atual >= limite_maximo, senão 0.
;
; Equivalente em C:
;     int limiteAtingido(int valor_atual, int limite_maximo) {
;         return (valor_atual >= limite_maximo) ? 1 : 0;
;     }
; ------------------------------------------------------------
limiteAtingido:
    push    ebp
    mov     ebp, esp

    mov     eax, [ebp+8]        ; eax = valor_atual
    mov     edx, [ebp+12]       ; edx = limite_maximo

    xor     ecx, ecx            ; ecx = 0 (assume "não atingiu")
    cmp     eax, edx
    jl      .fim_limite         ; se valor_atual < limite_maximo, mantém 0
    mov     ecx, 1              ; senão, atingiu o limite

.fim_limite:
    mov     eax, ecx            ; resultado em eax (retorno cdecl)

    mov     esp, ebp
    pop     ebp
    ret

section .note.GNU-stack noalloc noexec nowrite progbits