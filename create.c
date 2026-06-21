#include <stdio.h>
#include <string.h>
#include "dados.h"

//menu
void escolherRegiao(char *destino) {
    int opcao_regiao;
    do {
        printf("\nSelecione a Regiao do Time:\n");
        printf("1. Americas\n");
        printf("2. Europa\n");
        printf("3. Asia\n");
        printf("4. Pacifico\n");
        printf("5. China\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao_regiao) != 1) {
            limparBuffer();
            opcao_regiao = -1;
        }

        switch (opcao_regiao) {
            case 1: strcpy(destino, "Americas"); break;
            case 2: strcpy(destino, "Europa"); break;
            case 3: strcpy(destino, "Asia"); break;
            case 4: strcpy(destino, "Pacifico"); break;
            case 5: strcpy(destino, "China"); break;
            default: printf("\n[Erro] Opcao invalida. Tente novamente.\n");
        }
    } while (opcao_regiao < 1 || opcao_regiao > 5);
    limparBuffer();
}

void escolherFuncao(char *destino) {
    int opcao_funcao;
    do {
        printf("\nSelecione a Função do Player:\n");
        printf("1. Duelista\n");
        printf("2. Controlador\n");
        printf("3. Iniciador\n");
        printf("4. Sentinela\n");
        printf("5. Flex\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao_funcao) != 1) {
            limparBuffer();
            opcao_funcao = -1;
        }

        switch (opcao_funcao) {
            case 1: strcpy(destino, "Duelista"); break;
            case 2: strcpy(destino, "Controlador"); break;
            case 3: strcpy(destino, "Iniciador"); break;
            case 4: strcpy(destino, "Sentinela"); break;
            case 5: strcpy(destino, "Flex"); break;
            default: printf("\n[Erro] Opcao invalida. Tente novamente.\n");
        }
    } while (opcao_funcao < 1 || opcao_funcao > 5);
    limparBuffer();
}


//add time
void adicionarTime(void) {
    if (total_times >= MAX_TIMES) {
        printf("\n[Erro] Limite maximo de %d times atingido!\n", MAX_TIMES);
        return;
    }

    Time novoTime;

    //id
    novoTime.id = gerarProximoId(proximo_id);
    proximo_id = novoTime.id + 1;

    novoTime.qtd_jogadores = 0;

    printf("\n--- Adicionar Novo Time de Valorant ---\n");

    limparBuffer();
    printf("Nome da Organizacao: ");
    fgets(novoTime.nome, MAX_STRING, stdin);
    novoTime.nome[strcspn(novoTime.nome, "\n")] = 0;

    escolherRegiao(novoTime.regiao);

    printf("Nome do Coach: ");
    fgets(novoTime.coach, MAX_STRING, stdin);
    novoTime.coach[strcspn(novoTime.coach, "\n")] = 0;

    tabela_times[total_times] = novoTime;
    int indice_salvo = total_times; 
    total_times++;

    printf("\n[Sucesso] Time adicionado! (ID: %d)\n", novoTime.id);
    salvarDados();

    char resposta;
    printf("Deseja comecar a adicionar jogadores para este time agora? (s/n): ");
    scanf(" %c", &resposta); /* O espaço antes de %c consome quebras de linha pendentes */

    if (resposta == 's' || resposta == 'S') {
        executarFluxoAdicionarJogador(indice_salvo);
    }
}

void executarFluxoAdicionarJogador(int indice) {
    char continuar = 'n';

    do {
        int pos = tabela_times[indice].qtd_jogadores;
        if (pos >= MAX_JOGADORES) {
            printf("\n[Aviso] A lineup da %s ja atingiu o limite maximo de 5 jogadores!\n",
                   tabela_times[indice].nome);
            break;
        }

        printf("\n--- Cadastrando Player %d de 5 ---\n", pos + 1);
        Jogador novoJogador;
        novoJogador.id = pos + 1;

        limparBuffer();
        printf("Nickname do Player: ");
        fgets(novoJogador.nome, MAX_STRING, stdin);
        novoJogador.nome[strcspn(novoJogador.nome, "\n")] = 0;

        escolherFuncao(novoJogador.funcao);

        tabela_times[indice].jogadores[pos] = novoJogador;
        tabela_times[indice].qtd_jogadores++;

        printf("\n[Sucesso] %s (ID: %d) adicionado a %s!\n",
               novoJogador.nome, novoJogador.id, tabela_times[indice].nome);

        salvarDados();

        if (tabela_times[indice].qtd_jogadores >= MAX_JOGADORES) {
            printf("[Info] Lineup completa com 5 jogadores!\n");
            break;
        }

        printf("Deseja adicionar mais um jogador a este time? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

void adicionarJogador(void) {
    int id, indice;

    printf("\n--- Adicionar Pro-Player ---\n");
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

    if (tabela_times[indice].qtd_jogadores >= MAX_JOGADORES) {
        printf("\n[Erro] A lineup da %s ja esta completa (5 jogadores)!\n",
               tabela_times[indice].nome);
        return;
    }

    executarFluxoAdicionarJogador(indice);
}
