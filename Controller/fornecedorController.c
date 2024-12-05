#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

// Obtém a lista de fornecedores a partir do armazenamento
Fornecedor* readFornecedores() {
    return getFornecedores();
}

// Cria um novo fornecedor e adiciona à lista
int createFornecedor(Fornecedor **fornecedores, Fornecedor *fornecedor) {
    int tamanhoAtual = getTamanhoFornecedores(); // Obtém o tamanho atual da lista

    // Realoca memória para adicionar o novo fornecedor
    Fornecedor *novoFornecedores = realloc(*fornecedores, (tamanhoAtual + 1) * sizeof(Fornecedor));
    if (novoFornecedores == NULL) {
        printf("Erro ao alocar memória para fornecedores.\n");
        return 0; // Retorna 0 indicando falha na alocação
    }

    *fornecedores = novoFornecedores; // Atualiza o ponteiro para a nova lista
    int index = tamanhoAtual; // Índice onde será adicionado o novo fornecedor

    // Preenche os dados do novo fornecedor
    (*fornecedores)[index].codigo = buscaNovoIDFornecedor(*fornecedores); // Gera um novo ID
    strcpy((*fornecedores)[index].nome_fantasia, fornecedor->nome_fantasia);
    strcpy((*fornecedores)[index].razao_social, fornecedor->razao_social);
    (*fornecedores)[index].incricao_estadual = fornecedor->incricao_estadual;
    strcpy((*fornecedores)[index].cnpj, fornecedor->cnpj);
    strcpy((*fornecedores)[index].endereco, fornecedor->endereco);
    strcpy((*fornecedores)[index].telefone, fornecedor->telefone);
    strcpy((*fornecedores)[index].email, fornecedor->email);
    (*fornecedores)[index].ativo = 1; // Marca o fornecedor como ativo

    printf("Tamanho do vetor de fornecedores: %d\n", getTamanhoFornecedores());
    setTamanhoFornecedores(); // Atualiza o tamanho da lista
    printf("Tamanho do vetor de fornecedores: %d\n", getTamanhoFornecedores());

    // Salva os fornecedores caso o armazenamento não seja apenas em memória
    if (getTipoArquivo() != MEM) setFornecedores(*fornecedores);

    return TRUE; // Retorna 1 indicando sucesso
}

// Exibe o fornecedor com base no código
int showFornecedor(Fornecedor *fornecedores, int codigo) {
    if (fornecedores == NULL) return FALSE; // Verifica se a lista está vazia

    int posicao = 0;
    int tamanho = getTamanhoFornecedores(); // Obtém o tamanho da lista

    // Procura o fornecedor pelo código fornecido
    while (posicao < tamanho && fornecedores[posicao].codigo != codigo) {
        posicao++;
    }

    // Retorna falso se não encontrar ou se estiver inativo
    if (posicao == tamanho || fornecedores[posicao].ativo == FALSE)
        return FALSE;

    return posicao; // Retorna a posição do fornecedor
}

// Atualiza os dados de um fornecedor existente
int updateFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor) {
    int posicao = showFornecedor(fornecedores, fornecedor->codigo); // Busca a posição do fornecedor

    if (posicao == FALSE) return FALSE; // Retorna falso se não encontrar o fornecedor

    // Atualiza os dados do fornecedor
    fornecedores[posicao].codigo = fornecedor->codigo;
    strcpy(fornecedores[posicao].nome_fantasia, fornecedor->nome_fantasia);
    strcpy(fornecedores[posicao].razao_social, fornecedor->razao_social);
    fornecedores[posicao].incricao_estadual = fornecedor->incricao_estadual;
    strcpy(fornecedores[posicao].cnpj, fornecedor->cnpj);
    strcpy(fornecedores[posicao].endereco, fornecedor->endereco);
    strcpy(fornecedores[posicao].telefone, fornecedor->telefone);
    strcpy(fornecedores[posicao].email, fornecedor->email);
    fornecedores[posicao].ativo = fornecedor->ativo; // Atualiza o estado ativo/inativo

    // Salva a lista atualizada se não for apenas em memória
    if (getTipoArquivo() != MEM) setFornecedores(fornecedores);
    return TRUE;
}

// Remove um fornecedor (desativando-o)
int deleteFornecedor(Fornecedor* fornecedores, int codigo) {
    int posicao = showFornecedor(fornecedores, codigo); // Busca a posição do fornecedor

    if (posicao == FALSE) return FALSE; // Retorna falso se o fornecedor não existir

    fornecedores[posicao].ativo = FALSE; // Marca o fornecedor como inativo
    if (getTipoArquivo() != MEM) setFornecedores(fornecedores); // Salva a lista atualizada
    return TRUE;
}

// Gera um novo ID para o próximo fornecedor
int buscaNovoIDFornecedor(Fornecedor * fornecedores) {
    int maior = 1; // ID inicial é 1
    if (getTamanhoFornecedores() == 0) return maior; // Retorna 1 se a lista estiver vazia

    // Itera pelos fornecedores para encontrar o maior ID
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        if (maior <= fornecedores[i].codigo) {
            maior = fornecedores[i].codigo + 1; // Incrementa o ID para o próximo disponível
        }
    }
    return maior; // Retorna o novo ID gerado
}
