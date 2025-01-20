#include <stdio.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"

void registrarCompra() {
    int codigoPeca, qtdComprada;
    float precoCusto, frete, imposto, lucro;


   /* if (atualizarEstoquePeca(pecas, codigoPeca, qtdComprada, precoCusto, frete, imposto, lucro) == 1) {
        printf("Compra registrada e estoque atualizado com sucesso!\n");
    } else {
        printf("Erro ao registrar a compra ou atualizar o estoque.\n");
    }
    /*/
}

int atualizarEstoquePeca(Peca *pecas, int codigoPeca, int qtdComprada, float precoCusto, float frete, float imposto, float lucro) {
    int posicao = showPeca(pecas, codigoPeca);
    if (posicao == -1) {
        printf("Peça não encontrada.\n");
        return -1;
    }

    pecas[posicao].estoque += qtdComprada;
    float totalAtual = pecas[posicao].preco_custo * pecas[posicao].estoque;
    float totalNovo = precoCusto * qtdComprada;
    pecas[posicao].preco_custo = (totalAtual + totalNovo) / (pecas[posicao].estoque);
    pecas[posicao].preco_venda = pecas[posicao].preco_custo + frete + imposto;
    pecas[posicao].preco_venda += pecas[posicao].preco_venda * lucro;

    return updatePeca(pecas, &pecas[posicao]);
}
