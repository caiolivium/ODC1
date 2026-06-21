#include <stdio.h>
#include "dados.h"

void listarTimes(void) {
    printf("\n--- Lista de Times VCT ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("%-5s | %-15s | %-15s | %-15s | %-10s\n", "ID", "ORGANIZACAO", "REGIAO", "COACH", "PLAYERS");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < total_times; i++) {
        printf("%-5d | %-15s | %-15s | %-15s | %-10d\n",
               tabela_times[i].id,
               tabela_times[i].nome,
               tabela_times[i].regiao,
               tabela_times[i].coach,
               tabela_times[i].qtd_jogadores);
    }

    int total_players = contarJogadoresTotal(tabela_times, total_times);
    printf("-----------------------------------------------------------------------\n");
    printf("Total de pro-players cadastrados no sistema: %d\n", total_players);
}

void verElenco(void) {
    int id, indice;

    printf("\n--- Ver Lineup ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndicePorId(tabela_times, total_times, id);
    if (indice == -1) {
        printf("\n[Erro] ID %d nao encontrado.\n", id);
        return;
    }

    printf("\n================================\n");
    printf(" LINEUP DA %s\n", tabela_times[indice].nome);
    printf(" COACH: %s\n", tabela_times[indice].coach);
    printf("================================\n");

    if (tabela_times[indice].qtd_jogadores == 0) {
        printf("Nenhum player cadastrado nesta organizacao.\n");
        return;
    }

    printf("%-5s | %-20s | %-15s\n", "ID", "NICKNAME", "FUNCAO");
    printf("----------------------------------------------\n");
    for (int i = 0; i < tabela_times[indice].qtd_jogadores; i++) {
        printf("%-5d | %-20s | %-15s\n",
               tabela_times[indice].jogadores[i].id,
               tabela_times[indice].jogadores[i].nome,
               tabela_times[indice].jogadores[i].funcao);
    }
}
