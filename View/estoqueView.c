#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"
#include "../bibliotecas/fornecedor.h"


void menuEstoque(Peca *pecas, Fornecedor *fornecedores) {
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
        case 1: {
                char nomeFornecedor[100];
                char cnpj[20];
                float frete, imposto;
                int continuar = 1;

                printf("\n=== REGISTRANDO UMA NOTA DE ENTRADA ===\n");
                //printf("Digite o nome do fornecedor: ");
                //scanf(" %[^\n]s", nomeFornecedor);

                printf("Digite o CNPJ da empresa: ");
                scanf("%s", cnpj);

                // Verifica se o fornecedor já está cadastrado
                int codFornecedor = buscarOuCadastrarFornecedor(&fornecedores, nomeFornecedor, cnpj);
                printf("Fornecedor associado: Código %d\n", codFornecedor);

                printf("Digite o valor total do frete: ");
                scanf("%f", &frete);

                printf("Digite o valor total do imposto: ");
                scanf("%f", &imposto);

                do  {
                    char nomePeca[100];
                    int qtdPecas;
                    float precoCusto;

                    printf("\n=== REGISTRANDO PEÇA ===\n");
                    printf("Digite o nome da peça: ");
                    scanf(" %[^\n]s", nomePeca);

                    // Verifica se a peça já está cadastrada
                   // int codPeca = buscarOuCadastrarPeca(pecas, nomePeca, codFornecedor);

                    int codPeca = buscarOuCadastrarPeca(&pecas, fornecedores, nomePeca, codFornecedor);

                    printf("Digite a quantidade da peça: ");
                    scanf("%d", &qtdPecas);

                    printf("Digite o preço de custo unitário da peça: ");
                    scanf("%f", &precoCusto);

                    //aqui tenho que fazer o preco total que seria qtd da peça * preço de custo

                    //aqui tenho que fazer um vetor que guarda a quantidade de peças

                    printf("A nota de entrada ainda possui peça?\n"
                           "1-Sim\n"
                           "2-Não\n"
                           "=> ");
                    scanf("%d", &continuar);



                }while (continuar<2);
                //logo abaixo fazer o imposto por produto, que seria a imposto/quantidade
                //calcular frete por produto, que seria frete/quantidade

            }
            break;

        case 2:
            printf("\n=== LISTA COMPLETA DO ESTOQUE ===\n");
            mostrarTodasPecas(pecas);
            break;

        case 3:
                char nomePeca[100];
                printf("Digite o nome da peça para consultar: ");
                scanf(" %[^\n]s", nomePeca);

                //int codPeca = buscarPecaPorNome(pecas, nomePeca);
                /*/if (codPeca != -1) {
                    int posicao = showPeca(pecas, codPeca);
                    if (posicao != -1) {
                        mostrarPeca(&pecas[posicao]);
                    }
                } else {
                    printf("Peça não encontrada.\n");
                }
            }/*/
            break;

        case 0:
            printf("Saindo do menu estoque...\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}


