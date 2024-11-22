#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/servico.h"
#include "../bibliotecas/utils.h"
Servico * readServicos() {
    return getServicos();
}
int createServico(Servico **servicos, Servico *servico) {
    int tamanhoAtual = getTamanhoServicos();
    Servico *novoServicos = realloc(*servicos, (tamanhoAtual + 1) * sizeof(Servico));
    if (novoServicos == NULL) {
        printf("Erro ao alocar mais memória para serviços.\n");
        return 0; // Retorna 0 indicando falha
    }

    *servicos = novoServicos;
    int index = tamanhoAtual;
    (*servicos)[index].codigo = buscaNovoIDServico(*servicos); // Função para buscar novo ID de serviço
    strcpy((*servicos)[index].descricao, servico->descricao);
    (*servicos)[index].preco = servico->preco;
    (*servicos)[index].comicao = servico->comicao;
    (*servicos)[index].ativo = 1;

    setTamanhoServicos(); // Atualiza o tamanho dos serviços

    // Grava os dados no arquivo, se o tipo não for MEM
    if (getTipoArquivo() != MEM) setServicos(*servicos);

    return TRUE; // Retorna 1 indicando sucesso
}

int showServico(Servico *servicos, int codigo) {
    if (servicos == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoServicos();

    // Procura o serviço com o código especificado dentro do limite do array
    while (posicao < tamanho && servicos[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o serviço foi encontrado
    if (posicao == tamanho)
        return FALSE;

    return posicao;
}
int updateServico(Servico *servicos, Servico *servico) {
    int posicao = showServico(servicos, servico->codigo);

    if (posicao == FALSE) return FALSE;

    // Atualiza os campos necessários
    servicos[posicao].codigo = servico->codigo;
    strcpy(servicos[posicao].descricao, servico->descricao);
    servicos[posicao].preco = servico->preco;
    servicos[posicao].comicao = servico->comicao;

    if (getTipoArquivo() != MEM) setServicos(servicos);
    return TRUE;
}

int deleteServico(Servico *servicos, int codigo) {
    int posicao = showServico(servicos, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o serviço existe e está ativo

    servicos[posicao].ativo = FALSE; // Marca o serviço como inativo
    if (getTipoArquivo() != MEM) setServicos(servicos);
    return TRUE;
}

int buscaNovoIDServico(Servico *servicos) {
    int maior = 1;
    if (getTamanhoServicos() == 0) return maior; // Caso não haja nenhum serviço registrado
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (maior <= servicos[i].codigo) {
            maior = servicos[i].codigo + 1;
        }
    }
    return maior;
}

