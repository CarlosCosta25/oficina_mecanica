#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

// Função para obter a lista de peças existentes
Peca* readPecas() {
    return getPecas(); // Retorna o array de peças do sistema, carregado a partir de uma fonte externa
}

// Função para adicionar uma nova peça à lista de peças
int createPeca(Peca **pecas, Peca *peca) {
    int tamanhoAtual = getTamanhoPecas(); // Obtém o tamanho atual do array de peças

    // Realoca memória para incluir a nova peça
    Peca *novoPecas = realloc(*pecas, (tamanhoAtual + 1) * sizeof(Peca));
    if (novoPecas == NULL) { // Verifica se a realocação falhou
        printf("Erro ao alocar mais memória para peças.\n");
        return FALSE; // Retorna falha
    }
    *pecas = novoPecas; // Atualiza o ponteiro para o array realocado
    int index = tamanhoAtual; // Define o índice da nova peça

    // Preenche os dados da nova peça
    (*pecas)[index].codigo = buscaNovoIDPeca(*pecas); // Gera um novo ID exclusivo para a peça
    strcpy((*pecas)[index].descricao, peca->descricao);
    strcpy((*pecas)[index].fabricante, peca->fabricante);
    (*pecas)[index].fornecedor = peca->fornecedor;
    (*pecas)[index].preco_custo = peca->preco_custo;
    (*pecas)[index].preco_venda = peca->preco_venda;
    (*pecas)[index].estoque = peca->estoque;
    (*pecas)[index].estoque_min = peca->estoque_min;
    (*pecas)[index].ativo = 1; // Marca a peça como ativa

    setTamanhoPecas(); // Atualiza o tamanho total do array de peças no sistema

    // Salva as peças no armazenamento persistente, se aplicável
    if (getTipoArquivo() != MEM) setPecas(*pecas);

    return TRUE; // Retorna sucesso
}

// Função para buscar o índice de uma peça pelo código
int showPeca(Peca *pecas, int codigo) {
    if (pecas == NULL) return FALSE; // Retorna falha se o array de peças for nulo

    int posicao = 0;
    int tamanho = getTamanhoPecas(); // Obtém o tamanho do array de peças

    // Busca a peça com o código especificado
    while (posicao < tamanho && pecas[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se a peça foi encontrada e está ativa
    if (posicao == tamanho || pecas[posicao].ativo == FALSE)
        return FALSE; // Retorna falha se não encontrou ou está inativa

    return posicao; // Retorna o índice da peça
}

// Função para atualizar os dados de uma peça existente
int updatePeca(Peca *pecas, Peca *peca) {
    int posicao = showPeca(pecas, peca->codigo); // Busca a peça pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se a peça não foi encontrada

    // Atualiza os campos da peça
    pecas[posicao].codigo = peca->codigo;
    strcpy(pecas[posicao].descricao, peca->descricao);
    strcpy(pecas[posicao].fabricante, peca->fabricante);
    pecas[posicao].fornecedor = peca->fornecedor;
    pecas[posicao].preco_custo = peca->preco_custo;
    pecas[posicao].preco_venda = peca->preco_venda;
    pecas[posicao].estoque = peca->estoque;
    pecas[posicao].estoque_min = peca->estoque_min;
    pecas[posicao].ativo = peca->ativo; // Atualiza o status ativo/inativo

    // Salva as peças no armazenamento persistente, se aplicável
    if (getTipoArquivo() != MEM) setPecas(pecas);
    return TRUE; // Retorna sucesso
}

// Função para marcar uma peça como inativa
int deletePeca(Peca* pecas, int codigo) {
    int posicao = showPeca(pecas, codigo); // Busca a peça pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se a peça não foi encontrada ou está inativa

    pecas[posicao].ativo = FALSE; // Marca a peça como inativa
    if (getTipoArquivo() != MEM) setPecas(pecas); // Salva as alterações, se aplicável
    return TRUE; // Retorna sucesso
}

// Função para gerar um novo ID único para uma peça
int buscaNovoIDPeca(Peca *pecas) {
    int maior = 1; // Inicia com o ID mínimo
    if (getTamanhoPecas() == 0) return maior; // Retorna 1 se não há peças

    // Itera pelas peças para encontrar o maior ID
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (maior <= pecas[i].codigo) {
            maior = pecas[i].codigo + 1; // Atualiza o maior ID
        }
    }
    return maior; // Retorna o novo ID único
}
