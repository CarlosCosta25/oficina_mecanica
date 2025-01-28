#include <stdio.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"

// Função para exibir o menu de estoque
void menuEstoque() {
    int opcao;

    do {
        printf("\n=== MENU ESTOQUE ===\n");
        printf("1 - Registrar Nota de Entrada\n");
        printf("2 - Listar Estoque\n");
        printf("3 - Consultar Peça\n");
        printf("0 - Sair\n");
        printf("=> ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            registrarCompra();
            break;

        case 2:
            printf("\n=== LISTA COMPLETA DO ESTOQUE ===\n");
            listarEstoque();
            break;

        case 3: {
                char nomePeca[100];
                printf("Digite o nome da peça para consultar: ");
                scanf(" %[^\n]s", nomePeca);

                Peca *pecas = migraDadosPeca();
                int codPeca = buscarPecaPorNome(pecas, nomePeca);
                if (codPeca != -1) {
                    consultarPeca(codPeca);
                } else {
                    printf("Peça não encontrada.\n");
                }
                break;
        }

        case 0:
            printf("Saindo do menu estoque...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função para listar todas as peças no estoque
void listarEstoque() {
    Peca *pecas = migraDadosPeca();
    for (int i = 0; i < getTamanhoPecas(); i++) {
        printf("Código: %d | Nome: %s | Quantidade: %d | Preço Venda: %.2f\n",
               pecas[i].codigo, pecas[i].descricao, pecas[i].estoque, pecas[i].preco_venda);
    }
}
