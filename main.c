#include <stdio.h>
#include "dados.h"

int main(void) {
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
