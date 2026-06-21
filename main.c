#include <stdio.h>
#include "dados.h"

// Declara a função definida em main.asm
void imprimirMenu(void);

int main(void) {
    int opcao;
    carregarDados();
    do {
        imprimirMenu();   // <-- substitui os printf do menu

        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
        }

        switch (opcao) {
            case 1: adicionarTime();    break;
            case 2: listarTimes();      break;
            case 3: atualizarTime();    break;
            case 4: deletarTime();      break;
            case 5: adicionarJogador(); break;
            case 6: verElenco();        break;
            case 0: printf("\nSaindo do sistema VCT...\n"); break;
            default: printf("\n[Erro] Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}