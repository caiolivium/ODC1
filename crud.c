#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 16
#define MAX_STRING 50
#define MAX_JOGADORES 5
#define ARQUIVO "valorant_vct.txt"

typedef struct {
    int id;                  // Gerado automaticamente
    char nome[MAX_STRING];
    char funcao[MAX_STRING]; 
} Jogador;

typedef struct {
    int id;
    char nome[MAX_STRING];
    char regiao[MAX_STRING];
    char coach[MAX_STRING];
    Jogador jogadores[MAX_JOGADORES];
    int qtd_jogadores;
} Time;

Time tabela_times[MAX_TIMES];
int total_times = 0;
int proximo_id = 1;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int encontrarIndice(int id) {
    for (int i = 0; i < total_times; i++) {
        if (tabela_times[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Menu de seleção para a Região do Time
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

// Menu de seleção para a Função do Pro-Player
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

void salvarDados() {
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

void carregarDados() {
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

// Protótipo necessário pois adicionarTime agora pode chamar a função de loop do jogador
void executarFluxoAdicionarJogador(int indice);

void adicionarTime() {
    if (total_times >= MAX_TIMES) {
        printf("\n[Erro] Limite maximo de %d times atingido!\n", MAX_TIMES);
        return;
    }

    Time novoTime;
    novoTime.id = proximo_id++;
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
    int indice_salvo = total_times; // Guarda a posição onde foi inserido
    total_times++;
    
    printf("\n[Sucesso] Time adicionado! (ID: %d)\n", novoTime.id);
    salvarDados();

    // MODIFICAÇÃO: Pergunta se deseja começar a adicionar jogadores imediatamente
    char resposta;
    printf("Deseja comecar a adicionar jogadores para este time agora? (s/n): ");
    scanf(" %c", &resposta); // O espaço antes de %c consome quebras de linha pendentes

    if (resposta == 's' || resposta == 'S') {
        executarFluxoAdicionarJogador(indice_salvo);
    }
}

void listarTimes() {
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
}

void atualizarTime() {
    int id, indice;
    
    printf("\n--- Atualizar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
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

void deletarTime() {
    int id, indice;
    
    printf("\n--- Deletar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] ID %d nao encontrado.\n", id);
        return;
    }

    for (int i = indice; i < total_times - 1; i++) {
        tabela_times[i] = tabela_times[i + 1];
    }
    
    total_times--; 
    printf("\n[Sucesso] Time removido!\n");
    
    salvarDados();
}

// Nova função isolada para gerenciar o loop de adicionar jogadores
void executarFluxoAdicionarJogador(int indice) {
    char continuar;
    
    do {
        int pos = tabela_times[indice].qtd_jogadores;
        if (pos >= MAX_JOGADORES) {
            printf("\n[Aviso] A lineup da %s ja atingiu o limite maximo de 5 jogadores!\n", tabela_times[indice].nome);
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

        // Se o time encheu após essa inserção, encerra o loop automaticamente
        if (tabela_times[indice].qtd_jogadores >= MAX_JOGADORES) {
            printf("[Info] Lineup completa com 5 jogadores!\n");
            break;
        }

        // MODIFICAÇÃO: Pergunta se deseja adicionar mais um jogador
        printf("Deseja adicionar mais um jogador a este time? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');
}

// Função chamada diretamente pelo menu principal (Opção 5)
void adicionarJogador() {
    int id, indice;

    printf("\n--- Adicionar Pro-Player ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] Time ID %d nao encontrado.\n", id);
        return;
    }

    if (tabela_times[indice].qtd_jogadores >= MAX_JOGADORES) {
        printf("\n[Erro] A lineup da %s ja esta completa (5 jogadores)!\n", tabela_times[indice].nome);
        return;
    }

    // Chama a rotina com o loop interativo de perguntas
    executarFluxoAdicionarJogador(indice);
}

void verElenco() {
    int id, indice;

    printf("\n--- Ver Lineup ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
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

int main() {
    int opcao;

    carregarDados();

    do {
        printf("\n=========================================\n");
        printf("   GESTAO DE TIMES - VALORANT VCT\n");
        printf("=========================================\n");
        printf("1. Adicionar Time\n");
        printf("2. Listar Times\n");
        printf("3. Atualizar Time\n");
        printf("4. Deletar Time\n");
        printf("5. Adicionar Player ao Time\n");
        printf("6. Ver Lineup de um Time\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:\n");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1; 
        }

        switch (opcao) {
            case 1: adicionarTime(); break;
            case 2: listarTimes(); break;
            case 3: atualizarTime(); break;
            case 4: deletarTime(); break;
            case 5: adicionarJogador(); break;
            case 6: verElenco(); break;
            case 0: printf("\nSaindo do sistema VCT...\n"); break;
            default: printf("\n[Erro] Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}