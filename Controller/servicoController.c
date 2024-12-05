#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/servico.h"
#include "../bibliotecas/utils.h"

// Função para obter a lista de serviços do sistema
Servico *readServicos() {
    return getServicos(); // Retorna um array contendo todos os serviços cadastrados
}

// Função para criar um novo serviço e adicioná-lo à lista de serviços
int createServico(Servico **servicos, Servico *servico) {
    int tamanhoAtual = getTamanhoServicos(); // Obtém o tamanho atual do array de serviços

    // Realoca memória para adicionar um novo serviço
    Servico *novoServicos = realloc(*servicos, (tamanhoAtual + 1) * sizeof(Servico));
    if (novoServicos == NULL) { // Verifica se a realocação falhou
        printf("Erro ao alocar mais memória para serviços.\n");
        return FALSE; // Retorna falha
    }

    *servicos = novoServicos; // Atualiza o ponteiro para o array realocado
    int index = tamanhoAtual; // Define o índice para o novo serviço

    // Preenche os campos do novo serviço
    (*servicos)[index].codigo = buscaNovoIDServico(*servicos); // Gera um novo ID único
    strcpy((*servicos)[index].descricao, servico->descricao);  // Copia a descrição
    (*servicos)[index].preco = servico->preco;                // Define o preço
    (*servicos)[index].comicao = servico->comicao;            // Define a comissão
    (*servicos)[index].ativo = 1;                             // Marca o serviço como ativo

    setTamanhoServicos(); // Atualiza o tamanho total do array de serviços

    // Salva as alterações no armazenamento persistente, se aplicável
    if (getTipoArquivo() != MEM) setServicos(*servicos);

    return TRUE; // Retorna sucesso
}

// Função para buscar o índice de um serviço pelo código
int showServico(Servico *servicos, int codigo) {
    if (servicos == NULL) return FALSE; // Verifica se a lista de serviços é nula

    int posicao = 0;
    int tamanho = getTamanhoServicos(); // Obtém o tamanho do array de serviços

    // Busca o serviço pelo código
    while (posicao < tamanho && servicos[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o serviço foi encontrado
    if (posicao == tamanho)
        return FALSE; // Retorna falha se o serviço não foi encontrado

    return posicao; // Retorna o índice do serviço
}

// Função para atualizar os dados de um serviço existente
int updateServico(Servico *servicos, Servico *servico) {
    int posicao = showServico(servicos, servico->codigo); // Busca o índice do serviço pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se o serviço não foi encontrado

    // Atualiza os campos do serviço
    servicos[posicao].codigo = servico->codigo;
    strcpy(servicos[posicao].descricao, servico->descricao);
    servicos[posicao].preco = servico->preco;
    servicos[posicao].comicao = servico->comicao;

    // Salva as alterações no armazenamento persistente, se aplicável
    if (getTipoArquivo() != MEM) setServicos(servicos);

    return TRUE; // Retorna sucesso
}

// Função para marcar um serviço como inativo
int deleteServico(Servico *servicos, int codigo) {
    int posicao = showServico(servicos, codigo); // Busca o índice do serviço pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se o serviço não foi encontrado

    servicos[posicao].ativo = FALSE; // Marca o serviço como inativo

    // Salva as alterações no armazenamento persistente, se aplicável
    if (getTipoArquivo() != MEM) setServicos(servicos);

    return TRUE; // Retorna sucesso
}

// Função para gerar um novo ID exclusivo para um serviço
int buscaNovoIDServico(Servico *servicos) {
    int maior = 1; // Inicia com o ID mínimo
    if (getTamanhoServicos() == 0) return maior; // Retorna 1 se não há serviços cadastrados

    // Itera pela lista de serviços para encontrar o maior ID
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (maior <= servicos[i].codigo) {
            maior = servicos[i].codigo + 1; // Atualiza o maior ID
        }
    }

    return maior; // Retorna o novo ID único
}
