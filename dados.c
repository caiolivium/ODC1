#include <stdio.h>
#include <string.h>
#include "dados.h"

Time tabela_times[MAX_TIMES];
int total_times = 0;
int proximo_id = 1;

void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvarDados(void) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("\n[Erro] Nao foi possivel abrir o arquivo para salvar os dados.\n");
        return;
    }

    fprintf(arquivo, "%d\n", total_times);
    fprintf(arquivo, "%d\n", proximo_id);

    for (int i = 0; i < total_times; i++) {
        fprintf(arquivo, "%d\n", tabela_times[i].id);
        fprintf(arquivo, "%s\n", tabela_times[i].nome);
        fprintf(arquivo, "%s\n", tabela_times[i].regiao);
        fprintf(arquivo, "%s\n", tabela_times[i].coach);
        fprintf(arquivo, "%d\n", tabela_times[i].qtd_jogadores);

        for (int j = 0; j < tabela_times[i].qtd_jogadores; j++) {
            fprintf(arquivo, "%d\n", tabela_times[i].jogadores[j].id);
            fprintf(arquivo, "%s\n", tabela_times[i].jogadores[j].nome);
            fprintf(arquivo, "%s\n", tabela_times[i].jogadores[j].funcao);
        }
    }

    fclose(arquivo);
}

void carregarDados(void) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        return;
    }

    if (fscanf(arquivo, "%d\n", &total_times) != 1) total_times = 0;
    if (fscanf(arquivo, "%d\n", &proximo_id) != 1) proximo_id = 1;

    for (int i = 0; i < total_times; i++) {
        fscanf(arquivo, "%d\n", &tabela_times[i].id);

        fgets(tabela_times[i].nome, MAX_STRING, arquivo);
        tabela_times[i].nome[strcspn(tabela_times[i].nome, "\n")] = 0;

        fgets(tabela_times[i].regiao, MAX_STRING, arquivo);
        tabela_times[i].regiao[strcspn(tabela_times[i].regiao, "\n")] = 0;

        fgets(tabela_times[i].coach, MAX_STRING, arquivo);
        tabela_times[i].coach[strcspn(tabela_times[i].coach, "\n")] = 0;

        fscanf(arquivo, "%d\n", &tabela_times[i].qtd_jogadores);

        for (int j = 0; j < tabela_times[i].qtd_jogadores; j++) {
            fscanf(arquivo, "%d\n", &tabela_times[i].jogadores[j].id);

            fgets(tabela_times[i].jogadores[j].nome, MAX_STRING, arquivo);
            tabela_times[i].jogadores[j].nome[strcspn(tabela_times[i].jogadores[j].nome, "\n")] = 0;

            fgets(tabela_times[i].jogadores[j].funcao, MAX_STRING, arquivo);
            tabela_times[i].jogadores[j].funcao[strcspn(tabela_times[i].jogadores[j].funcao, "\n")] = 0;
        }
    }

    fclose(arquivo);
}
