#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

Fornecedor* readFornecedores() {
    Fornecedor *fornecedores = NULL;
    fornecedores = getFornecedores();
    return fornecedores;
}

int createFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor) {
    fornecedores = realloc(fornecedores, (getTamanhoFornecedores() + 1) * sizeof(Fornecedor));
    if (fornecedores == NULL) {
        return FALSE;
    }
    fornecedores[getTamanhoFornecedores()].codigo = buscaNovoIDFornecedor(fornecedores);
    strcpy(fornecedores[getTamanhoFornecedores()].nome_fantasia, fornecedor->nome_fantasia);
    strcpy(fornecedores[getTamanhoFornecedores()].razao_social, fornecedor->razao_social);
    fornecedores[getTamanhoFornecedores()].incricao_estadual = fornecedor->incricao_estadual;
    strcpy(fornecedores[getTamanhoFornecedores()].cnpj, fornecedor->cnpj);
    strcpy(fornecedores[getTamanhoFornecedores()].endereco, fornecedor->endereco);
    strcpy(fornecedores[getTamanhoFornecedores()].telefone, fornecedor->telefone);
    strcpy(fornecedores[getTamanhoFornecedores()].email, fornecedor->email);
    fornecedores[getTamanhoFornecedores()].ativo = 1;
    setTamanhoFornecedores();
    setFornecedores(fornecedores);
    return TRUE;
}

int showFornecedor(Fornecedor *fornecedores, int codigo) {
    int i = 0;
    while (fornecedores[i].codigo != codigo /*&& i < getTamanhoFornecedores()*/) {
        i++;
    }
    if (i == getTamanhoFornecedores() || fornecedores[i].ativo == FALSE)
        return FALSE;

    return i;
}

int updateFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor) {
    int posicao = showFornecedor(fornecedores, fornecedor->codigo);

    if (posicao == FALSE) return FALSE;

    fornecedores[posicao].codigo = fornecedor->codigo;
    strcpy(fornecedores[posicao].nome_fantasia, fornecedor->nome_fantasia);
    strcpy(fornecedores[posicao].razao_social, fornecedor->razao_social);
    fornecedores[posicao].incricao_estadual = fornecedor->incricao_estadual;
    strcpy(fornecedores[posicao].cnpj, fornecedor->cnpj);
    strcpy(fornecedores[posicao].endereco, fornecedor->endereco);
    strcpy(fornecedores[posicao].telefone, fornecedor->telefone);
    strcpy(fornecedores[posicao].email, fornecedor->email);
    fornecedores[posicao].ativo = fornecedor->ativo; // Mantém o estado ativo

    setFornecedores(fornecedores);
    return TRUE;
}

int deleteFornecedor(Fornecedor* fornecedores, int codigo) {
    int posicao = showFornecedor(fornecedores, codigo);
    if (posicao == FALSE) return FALSE;
    fornecedores[posicao].ativo = FALSE;
    setFornecedores(fornecedores);
    return TRUE;
}

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
