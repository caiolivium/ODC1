#include <stdio.h>
#include <string.h>
#include "dados.h"

void atualizarTime(void) {
    int id, indice;

    printf("\n--- Atualizar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndicePorId(tabela_times, total_times, id);
    if (indice == -1) {
        printf("\n[Erro] Time ID %d nao encontrado.\n", id);
        return;
    }

    limparBuffer();
    printf("Novo nome (atual: %s): ", tabela_times[indice].nome);
    fgets(tabela_times[indice].nome, MAX_STRING, stdin);
    tabela_times[indice].nome[strcspn(tabela_times[indice].nome, "\n")] = 0;

    printf("Regiao atual: %s", tabela_times[indice].regiao);
    escolherRegiao(tabela_times[indice].regiao);

    printf("Novo Coach (atual: %s): ", tabela_times[indice].coach);
    fgets(tabela_times[indice].coach, MAX_STRING, stdin);
    tabela_times[indice].coach[strcspn(tabela_times[indice].coach, "\n")] = 0;

    printf("\n[Sucesso] Informacoes atualizadas!\n");

    salvarDados();
}
