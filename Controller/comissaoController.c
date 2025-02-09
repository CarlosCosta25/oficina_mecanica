#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/Modulo2.h"
#include "../bibliotecas/utils.h"

Cliente* readComisoes() {
    return getClientes();            // Retorna o ponteiro para os clientes
}
int createComisao(Comissao **comissoes, Comissao *comisao) {
    int tamanhoAtual = getTamanhoComissoes(); // Obtém o tamanho atual da lista de comissões

    // Realoca a memória para incluir a nova comissão
    Comissao *novasComissoes = realloc(*comissoes, (tamanhoAtual + 1) * sizeof(Comissao));
    if (novasComissoes == NULL) {
        printf("Erro ao alocar memória para comissões.\n");
        return FALSE; // Retorna -1 em caso de falha na alocação
    }

    *comissoes = novasComissoes; // Atualiza o ponteiro para o novo bloco de memória
    int index = tamanhoAtual; // O índice da nova comissão é igual ao tamanho atual da lista

    // Preenche os dados da nova comissão
    (*comissoes)[index].codigo = buscaNovoIDComissao(*comissoes); // Atribui um novo ID à comissão
    (*comissoes)[index].CodigoOrdem = comisao->CodigoOrdem;
    (*comissoes)[index].valorComisao = comisao->valorComisao;
    (*comissoes)[index].tempoGasto = comisao->tempoGasto;

    setTamanhoComissoes(); // Atualiza o tamanho total da lista de comissões

    // Salva os dados no arquivo se o modo de armazenamento não for somente memória
    if (getTipoArquivo() != MEM) setComissoes(*comissoes);

    return TRUE;
}
// Função para exibir uma comissão com base no código
int showComisao(Comissao *comissoes, int codigo) {
    if (comissoes == NULL) return FALSE; // Retorna FALSE se a lista de comissões for vazia

    int posicao = 0;
    int tamanho = getTamanhoComissoes(); // Obtém o tamanho atual da lista de comissões

    // Procura pela comissão com o código especificado
    while (posicao < tamanho && comissoes[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se a comissão foi encontrada
    if (posicao == tamanho)
        return FALSE;

    return posicao; // Retorna a posição da comissão na lista
}

// Função para gerar um novo ID exclusivo para uma comissão
int buscaNovoIDComissao(Comissao *comissoes) {
    int maior = 1; // Inicializa o maior ID como 1
    if (getTamanhoComissoes() == 0) return maior; // Retorna 1 se não houver comissões

    // Itera sobre a lista de comissões para encontrar o maior ID
    for (int i = 0; i < getTamanhoComissoes(); i++) {
        if (maior <= comissoes[i].codigo) {
            maior = comissoes[i].codigo + 1; // Define o próximo ID como maior + 1
        }
    }
    return maior; // Retorna o novo ID
}

