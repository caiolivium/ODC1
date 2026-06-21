#ifndef DADOS_H
#define DADOS_H

#define MAX_TIMES 16
#define MAX_STRING 50
#define MAX_JOGADORES 5
#define ARQUIVO "valorant_vct.txt"

typedef struct {
    int id;                  
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

extern Time tabela_times[MAX_TIMES];
extern int total_times;
extern int proximo_id;

void limparBuffer(void);
void salvarDados(void);
void carregarDados(void);


//create.asm
int gerarProximoId(int proximo_id_atual);

//read.asm
int contarJogadoresTotal(void *tabela, int total_times_atual);

//update.asm
int encontrarIndicePorId(void *tabela, int total_times_atual, int id);

//delete.asm
void removerElemento(void *tabela, int *total_times_ptr, int indice);

//create.c
void escolherRegiao(char *destino);
void escolherFuncao(char *destino);

//create.c
void adicionarTime(void);
void executarFluxoAdicionarJogador(int indice);
void adicionarJogador(void);

//read.c
void listarTimes(void);
void verElenco(void);

//update.c
void atualizarTime(void);

//delete.c
void deletarTime(void);

#endif 
