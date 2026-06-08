#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 100
#define MAX_STRING 50
#define MAX_JOGADORES 25 // Limite de jogadores por time

// --- 1. Estruturas de Dados ---

// Struct para os Jogadores
typedef struct {
    char nome[MAX_STRING];
    char posicao[MAX_STRING];
    int numero;
} Jogador;

// Struct para o Time
typedef struct {
    int id;
    char nome[MAX_STRING];
    char cidade[MAX_STRING];
    int ano_fundacao;
    char treinador[MAX_STRING];       // Treinador do time
    Jogador jogadores[MAX_JOGADORES]; // Vetor de jogadores do time
    int qtd_jogadores;                // Contador de jogadores cadastrados neste time
} Time;

// --- 2. Variáveis Globais ---
Time tabela_times[MAX_TIMES];
int total_times = 0;
int proximo_id = 1;

// --- Funções Auxiliares ---

// Limpa o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Encontra o índice do time no array pelo ID
int encontrarIndice(int id) {
    for (int i = 0; i < total_times; i++) {
        if (tabela_times[i].id == id) {
            return i;
        }
    }
    return -1; // Retorna -1 se não encontrar
}

// --- Operações CRUD de Times ---

void adicionarTime() {
    if (total_times >= MAX_TIMES) {
        printf("\n[Erro] Limite maximo de %d times atingido!\n", MAX_TIMES);
        return;
    }

    Time novoTime;
    novoTime.id = proximo_id++;
    novoTime.qtd_jogadores = 0; // Inicializa o time vazio (sem jogadores)

    printf("\n--- Adicionar Novo Time ---\n");
    
    limparBuffer();
    printf("Nome do time: ");
    fgets(novoTime.nome, MAX_STRING, stdin);
    novoTime.nome[strcspn(novoTime.nome, "\n")] = 0;

    printf("Cidade: ");
    fgets(novoTime.cidade, MAX_STRING, stdin);
    novoTime.cidade[strcspn(novoTime.cidade, "\n")] = 0;

    printf("Nome do Treinador: ");
    fgets(novoTime.treinador, MAX_STRING, stdin);
    novoTime.treinador[strcspn(novoTime.treinador, "\n")] = 0;

    printf("Ano de fundacao: ");
    scanf("%d", &novoTime.ano_fundacao);

    tabela_times[total_times++] = novoTime;
    printf("\n[Sucesso] Time adicionado! (ID: %d)\n", novoTime.id);
}

void listarTimes() {
    printf("\n--- Lista de Times ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado no momento.\n");
        return;
    }

    printf("%-5s | %-15s | %-15s | %-15s | %-10s\n", "ID", "NOME", "CIDADE", "TREINADOR", "JOGADORES");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < total_times; i++) {
        printf("%-5d | %-15s | %-15s | %-15s | %-10d\n",
               tabela_times[i].id,
               tabela_times[i].nome,
               tabela_times[i].cidade,
               tabela_times[i].treinador,
               tabela_times[i].qtd_jogadores);
    }
}

void atualizarTime() {
    int id, indice;
    
    printf("\n--- Atualizar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado para atualizar.\n");
        return;
    }

    printf("Digite o ID do time que deseja atualizar: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] Time com ID %d nao encontrado.\n", id);
        return;
    }

    limparBuffer();
    printf("Novo nome (atual: %s): ", tabela_times[indice].nome);
    fgets(tabela_times[indice].nome, MAX_STRING, stdin);
    tabela_times[indice].nome[strcspn(tabela_times[indice].nome, "\n")] = 0;

    printf("Nova cidade (atual: %s): ", tabela_times[indice].cidade);
    fgets(tabela_times[indice].cidade, MAX_STRING, stdin);
    tabela_times[indice].cidade[strcspn(tabela_times[indice].cidade, "\n")] = 0;

    printf("Novo treinador (atual: %s): ", tabela_times[indice].treinador);
    fgets(tabela_times[indice].treinador, MAX_STRING, stdin);
    tabela_times[indice].treinador[strcspn(tabela_times[indice].treinador, "\n")] = 0;

    printf("Novo ano de fundacao (atual: %d): ", tabela_times[indice].ano_fundacao);
    scanf("%d", &tabela_times[indice].ano_fundacao);

    printf("\n[Sucesso] Time atualizado!\n");
}

void deletarTime() {
    int id, indice;
    
    printf("\n--- Deletar Time ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado para deletar.\n");
        return;
    }

    printf("Digite o ID do time que deseja deletar: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] Time com ID %d nao encontrado.\n", id);
        return;
    }

    // Desloca os times subsequentes para "cobrir" o deletado
    for (int i = indice; i < total_times - 1; i++) {
        tabela_times[i] = tabela_times[i + 1];
    }
    
    total_times--; 
    printf("\n[Sucesso] Time deletado!\n");
}

// --- Operações de Jogadores e Elenco ---

void adicionarJogador() {
    int id, indice;

    printf("\n--- Adicionar Jogador ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado. Cadastre um time primeiro.\n");
        return;
    }

    printf("Digite o ID do time para adicionar o jogador: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] Time com ID %d nao encontrado.\n", id);
        return;
    }

    // Verifica se o time já atingiu o limite de jogadores
    if (tabela_times[indice].qtd_jogadores >= MAX_JOGADORES) {
        printf("\n[Erro] O elenco do %s ja esta cheio (%d jogadores)!\n", tabela_times[indice].nome, MAX_JOGADORES);
        return;
    }

    Jogador novoJogador;
    limparBuffer();
    
    printf("Nome do jogador: ");
    fgets(novoJogador.nome, MAX_STRING, stdin);
    novoJogador.nome[strcspn(novoJogador.nome, "\n")] = 0;

    printf("Posicao (ex: Atacante, Goleiro): ");
    fgets(novoJogador.posicao, MAX_STRING, stdin);
    novoJogador.posicao[strcspn(novoJogador.posicao, "\n")] = 0;

    printf("Numero da camisa: ");
    scanf("%d", &novoJogador.numero);

    // Salva o jogador na última posição livre do time
    int pos = tabela_times[indice].qtd_jogadores;
    tabela_times[indice].jogadores[pos] = novoJogador;
    tabela_times[indice].qtd_jogadores++;

    printf("\n[Sucesso] Jogador %s adicionado ao time %s!\n", novoJogador.nome, tabela_times[indice].nome);
}

void verElenco() {
    int id, indice;

    printf("\n--- Ver Elenco ---\n");
    if (total_times == 0) {
        printf("Nenhum time cadastrado no momento.\n");
        return;
    }

    printf("Digite o ID do time: ");
    scanf("%d", &id);

    indice = encontrarIndice(id);
    if (indice == -1) {
        printf("\n[Erro] Time com ID %d nao encontrado.\n", id);
        return;
    }

    printf("\n================================\n");
    printf(" ELENCO DO: %s\n", tabela_times[indice].nome);
    printf(" TREINADOR: %s\n", tabela_times[indice].treinador);
    printf("================================\n");

    if (tabela_times[indice].qtd_jogadores == 0) {
        printf("Nenhum jogador cadastrado neste time ainda.\n");
        return;
    }

    printf("%-5s | %-20s | %-15s\n", "NUM", "NOME DO JOGADOR", "POSICAO");
    printf("----------------------------------------------\n");
    for (int i = 0; i < tabela_times[indice].qtd_jogadores; i++) {
        printf("%-5d | %-20s | %-15s\n",
               tabela_times[indice].jogadores[i].numero,
               tabela_times[indice].jogadores[i].nome,
               tabela_times[indice].jogadores[i].posicao);
    }
}

// --- Fluxo Principal ---
int main() {
    int opcao;

    do {
        printf("\n================================\n");
        printf("  SISTEMA DE GESTAO DE TIMES\n");
        printf("================================\n");
        printf("1. Adicionar Time\n");
        printf("2. Listar Times\n");
        printf("3. Atualizar Time\n");
        printf("4. Deletar Time\n");
        printf("5. Adicionar Jogador ao Time\n");
        printf("6. Ver Elenco de um Time\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
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
            case 0: printf("\nEncerrando o sistema...\n"); break;
            default: printf("\n[Erro] Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}