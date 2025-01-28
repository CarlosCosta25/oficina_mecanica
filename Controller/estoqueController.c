#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"
#include "../bibliotecas/fornecedor.h"

// Função para registrar uma nota de entrada
void registrarCompra() {
    char cnpj[20], nomeFornecedor[100];
    float frete, imposto;
    int continuar = 1;
    int totalQtdPecas = 0;

    printf("\n=== REGISTRANDO UMA NOTA DE ENTRADA ===\n");

    // Registrar fornecedor
    printf("Digite o CNPJ do fornecedor: ");
    scanf("%s", cnpj);

    printf("Digite o nome do fornecedor: ");
    scanf(" %[^\n]s", nomeFornecedor);
    Fornecedor *fornecedores = migraDadosFornecedor();

    int codFornecedor = buscarOuCadastrarFornecedor(&fornecedores, nomeFornecedor, cnpj);

    printf("Digite o valor total do frete: ");
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

        Peca * pecas= migraDadosPeca();

        int codPeca = buscarOuCadastrarPeca(&pecas, fornecedores,nomePeca,codFornecedor );

        printf("Digite a quantidade da peça comprada: ");
        scanf("%d", &qtdPecas);

        printf("Digite o preço de custo unitário da peça: ");
        scanf("%f", &precoCusto);

        totalQtdPecas += qtdPecas;

        float fretePorProduto = frete / totalQtdPecas;
        float impostoPorProduto = imposto / totalQtdPecas;
        float lucro = 0;

        atualizarEstoquePeca(pecas,codPeca, qtdPecas, precoCusto, fretePorProduto, impostoPorProduto,lucro);

        printf("Deseja registrar outra peça?\n1 - Sim\n2 - Não\n=> ");
        scanf("%d", &continuar);

    } while (continuar == 1);

    printf("\nNota de entrada registrada com sucesso!\n");
}

void consultarPeca(int codPeca) {
    Peca *pecas = migraDadosPeca();
    CompraPeca *estoque = migraDadosEstoque();

    // Procura a peça no array de peças
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].codigo == codPeca) {
            printf("\n=== DETALHES DA PEÇA ===\n");
            printf("Código: %d\n", pecas[i].codigo);
            printf("Descrição: %s\n", pecas[i].descricao);
            printf("Estoque atual: %d\n", pecas[i].estoque);
            printf("Preço de custo: R$ %.2f\n", pecas[i].preco_custo);
            printf("Preço de venda: R$ %.2f\n", pecas[i].preco_venda);

            // Busca informações adicionais no estoque
            for (int j = 0; j < getTamanhoEstoque(); j++) {
                if (estoque[j].codPeca == codPeca) {
                    printf("Último fornecedor (código): %d\n", estoque[j].codFornecedor);
                    printf("Último valor de frete: R$ %.2f\n", estoque[j].valorFrete);
                    printf("Último valor de imposto: R$ %.2f\n", estoque[j].valorImposto);
                    break;
                }
            }
            return;
        }
    }
    printf("Peça não encontrada no sistema.\n");
}
int atualizarEstoquePeca(Peca *pecas, int codigoPeca, int qtdComprada, float precoCusto, float frete, float imposto, float lucro) {
    CompraPeca *estoque = migraDadosEstoque();
    int novoTamanho = getTamanhoEstoque() + 1;

    // Atualiza o estoque da peça
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].codigo == codigoPeca) {
            // Atualiza informações da peça
            pecas[i].estoque += qtdComprada;
            pecas[i].preco_custo = precoCusto;
            pecas[i].preco_venda = (precoCusto + frete + imposto) * (1 + lucro);

            // Registra a compra no estoque
            estoque = realloc(estoque, novoTamanho * sizeof(CompraPeca));
            CompraPeca novaCompra = {
                .codigo = novoTamanho,
                .codPeca = codigoPeca,
                .qtdPecas = qtdComprada,
                .codFornecedor = pecas[i].fornecedor,
                .valorImposto = imposto,
                .valorFrete = frete,
                .valorTotalPeca = precoCusto * qtdComprada,
                .codTransacao = novoTamanho  // Simplifidado para exemplo
            };

            estoque[novoTamanho - 1] = novaCompra;
            setTamanhoEstoque(novoTamanho);
            setEstoque(estoque);
            setPecas(pecas);

            return 1; // Sucesso
        }
    }

    return 0; // Peça não encontrada
}

