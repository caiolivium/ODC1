#include <stdio.h>
#include "dados.h"

void deletarTime(void) {
    int id, indice;

    printf("\n--- Deletar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    // encontrar id
    indice = encontrarIndicePorId(tabela_times, total_times, id);
    if (indice == -1) {
        printf("\n[Erro] ID %d nao encontrado.\n", id);
        return;
    }

    // remove
    removerElemento(tabela_times, &total_times, indice);

    printf("\n[Sucesso] Time removido!\n");

    salvarDados();
}
