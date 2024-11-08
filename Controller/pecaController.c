#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

Peca* readPecas() {
    return  getPecas();
}

int createPeca(Peca **pecas, Peca *peca) {
    int tamanhoAtual = getTamanhoPecas();
    Peca *novoPecas = realloc(*pecas, (tamanhoAtual + 1) * sizeof(Peca));
    if (novoPecas == NULL) {
        printf("Erro ao alocar mais meoria para peças.\n");
        return 0; // Retorna 0 indicando falha
    }
    *pecas = novoPecas;
    int index = tamanhoAtual;
    (*pecas)[index].codigo = buscaNovoIDPeca(*pecas);
    strcpy((*pecas)[index].descricao, peca->descricao);
    strcpy((*pecas)[index].fabricante, peca->fabricante);
    (*pecas)[index].fornecedor = peca->fornecedor;
    (*pecas)[index].preco_custo = peca->preco_custo;
    (*pecas)[index].preco_venda = peca->preco_venda;
    (*pecas)[index].estoque = peca->estoque;
    (*pecas)[index].estoque_min = peca->estoque_min;
    (*pecas)[index].ativo = 1; // Fornecedor ativo ao ser criado
    setTamanhoPecas(); // Atualiza o tamanho dos fornecedores

    if (getTipoArquivo() != MEM) setPecas(*pecas);

    return TRUE;
}

int showPeca(Peca *pecas, int codigo) {
    if (pecas == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoPecas();

    // Procura o fornecedor com o código especificado dentro do limite do array
    while (posicao < tamanho && pecas[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o fornecedor foi encontrado e se está ativo
    if (posicao == tamanho || pecas[posicao].ativo == FALSE)
        return FALSE;

    return posicao;
}
int updatePeca(Peca *pecas, Peca *peca) {

    int posicao = showPeca(pecas, peca->codigo);

    if (posicao == FALSE) return FALSE;

    // Atualiza os campos necessários
    pecas[posicao].codigo = peca->codigo;
    strcpy(pecas[posicao].descricao, peca->descricao);
    strcpy(pecas[posicao].fabricante, peca->fabricante);
    pecas[posicao].fornecedor = peca->fornecedor;
    pecas[posicao].preco_custo = peca->preco_custo;
    pecas[posicao].preco_venda = peca->preco_venda;
    pecas[posicao].estoque = peca->estoque;
    pecas[posicao].estoque_min = peca->estoque_min;
    pecas[posicao].ativo = peca->ativo; // Atualiza o campo ativo

    if (getTipoArquivo() != MEM) setPecas(pecas);
    return TRUE;
}
int deletePeca(Peca* pecas, int codigo) {
    int posicao = showPeca(pecas, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o fornecedor existe e está ativo

    pecas[posicao].ativo = FALSE; // Marca o fornecedor como inativo
    if (getTipoArquivo() != MEM) setPecas(pecas);
    return TRUE;
}

int buscaNovoIDPeca(Peca * pecas) {
    int maior = 1;
    if(getTamanhoPecas() == 0 ) return maior;
    for(int i = 0; i < getTamanhoPecas(); i++) {
        if(maior <= pecas[i].codigo) {
            maior = pecas[i].codigo+1;
        }
    }
    return maior;
}
