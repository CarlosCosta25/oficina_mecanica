#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

// Função para exibir o menu de estoque
void novaNotaEntrada(Peca *pecas, Fornecedor **fornecedores) {
    char cnpj[100];
    float imposto, frete;
    int continuar = 1;

    printf("\n=== REGISTRANDO UMA NOTA DE ENTRADA ===\n");

    printf("Digite o CNPJ do fornecedor: ");
    scanf("%s", cnpj);
    int codfornecedor = buscarOuCadastrarFornecedor(&fornecedores, cnpj);
    //printf("O código do fornecedor é %d\n", codfornecedor);

    printf("\nDigite o valor total do frete: ");
    scanf("%f", &frete);

    printf("Digite o valor total do imposto: ");
    scanf("%f", &imposto);

    do {
        char nomePeca[100];
        int qtdPecas;
        float precoCusto;

        printf("\n=== REGISTRANDO PEÇA ===\n");
        printf("Digite o nome da peça: ");
        scanf(" %[^\n]s", nomePeca);

        // Verifica se a peça já está cadastrada
        int codPeca = buscarOuCadastrarPeca(&pecas, nomePeca, codfornecedor);

        printf("Digite a quantidade da peça: ");
        scanf("%d", &qtdPecas);

        printf("Digite o preço de custo unitário da peça: ");
        scanf("%f", &precoCusto);

        // Atualiza o estoque da peça
        atualizarEstoquePeca(pecas, codPeca, qtdPecas, precoCusto, frete, imposto, 0);

        continuar = lerInt("A nota de entrada possui mais peças?\n1 - SIM\n0 - NÃO\n=> ");
    } while (continuar != 0);
}

void menuEstoque(Peca *pecas, Fornecedor **fornecedores) {
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
                novaNotaEntrada(pecas, fornecedores);
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