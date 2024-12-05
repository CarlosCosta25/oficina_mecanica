#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

Fornecedor* readFornecedores() {
    return  getFornecedores();
}

int createFornecedor(Fornecedor **fornecedores, Fornecedor *fornecedor) {
    int tamanhoAtual = getTamanhoFornecedores();

    // Realoca a memória para acomodar o novo fornecedor
    Fornecedor *novoFornecedores = realloc(*fornecedores, (tamanhoAtual + 1) * sizeof(Fornecedor));
    if (novoFornecedores == NULL) {
        printf("Erro ao alocar memória para fornecedores.\n");
        return FALSE; // Retorna -1 indicando falha
    }

    *fornecedores = novoFornecedores; // Atualiza o ponteiro de fornecedores com o novo endereço
    int index = tamanhoAtual; // Novo índice é o tamanho atual

    // Preenche os dados do novo fornecedor no array
    (*fornecedores)[index].codigo = buscaNovoIDFornecedor(*fornecedores);
    strcpy((*fornecedores)[index].nome_fantasia, fornecedor->nome_fantasia);
    strcpy((*fornecedores)[index].razao_social, fornecedor->razao_social);
    (*fornecedores)[index].incricao_estadual = fornecedor->incricao_estadual;
    strcpy((*fornecedores)[index].cnpj, fornecedor->cnpj);
    strcpy((*fornecedores)[index].endereco, fornecedor->endereco);
    strcpy((*fornecedores)[index].telefone, fornecedor->telefone);
    strcpy((*fornecedores)[index].email, fornecedor->email);
    (*fornecedores)[index].ativo = 1; // Fornecedor ativo ao ser criado
    printf("Tamanho do vetor de fornecedores: %d\n", getTamanhoFornecedores());
    setTamanhoFornecedores(); // Atualiza o tamanho dos fornecedores
printf("Tamanho do vetor de fornecedores: %d\n", getTamanhoFornecedores());
    // Salva fornecedores se o tipo de arquivo não for memória
    if (getTipoArquivo() != MEM) setFornecedores(*fornecedores);

    return TRUE;
}

int showFornecedor(Fornecedor *fornecedores, int codigo) {
    if (fornecedores == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoFornecedores();

    // Procura o fornecedor com o código especificado dentro do limite do array
    while (posicao < tamanho && fornecedores[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o fornecedor foi encontrado e se está ativo
    if (posicao == tamanho || fornecedores[posicao].ativo == FALSE)
        return FALSE;

    return posicao;
}

// Função para atualizar os dados de um fornecedor existente
int updateFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor) {

    int posicao = showFornecedor(fornecedores, fornecedor->codigo);

    if (posicao == FALSE) return FALSE; // Retorna FALSE se o fornecedor não for encontrado ou estiver inativo

    // Atualiza os campos necessários
    fornecedores[posicao].codigo = fornecedor->codigo;
    strcpy(fornecedores[posicao].nome_fantasia, fornecedor->nome_fantasia);
    strcpy(fornecedores[posicao].razao_social, fornecedor->razao_social);
    fornecedores[posicao].incricao_estadual = fornecedor->incricao_estadual;
    strcpy(fornecedores[posicao].cnpj, fornecedor->cnpj);
    strcpy(fornecedores[posicao].endereco, fornecedor->endereco);
    strcpy(fornecedores[posicao].telefone, fornecedor->telefone);
    strcpy(fornecedores[posicao].email, fornecedor->email);
    fornecedores[posicao].ativo = fornecedor->ativo; // Atualiza o campo ativo

    if (getTipoArquivo() != MEM) setFornecedores(fornecedores);
    return TRUE;
}

// Função para deletar (ou desativar) um fornecedor
int deleteFornecedor(Fornecedor* fornecedores, int codigo) {
    int posicao = showFornecedor(fornecedores, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o fornecedor existe e está ativo

    fornecedores[posicao].ativo = FALSE; // Marca o fornecedor como inativo
    if (getTipoArquivo() != MEM) setFornecedores(fornecedores);
    return TRUE;
}

// Função para gerar um novo ID exclusivo para um fornecedor
int buscaNovoIDFornecedor(Fornecedor * fornecedores) {
    int maior = 1;
    if(getTamanhoFornecedores() == 0 ) return maior;
    for(int i = 0; i < getTamanhoFornecedores(); i++) {
        if(maior <= fornecedores[i].codigo) {
            maior = fornecedores[i].codigo+1;
        }
    }
    return maior;
}
