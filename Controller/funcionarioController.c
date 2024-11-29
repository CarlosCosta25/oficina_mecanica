#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/funcionario.h"
#include "../bibliotecas/utils.h"

Funcionario* readFuncionarios() {
    Funcionario * funcionarios = NULL;
    funcionarios = getFuncionarios();
        return funcionarios;
    }

int createFuncionario(Funcionario **funcionarios, Funcionario *funcionario) {
    int tamanhoAtual = getTamanhoFuncionarios();

    // Realoca a memória para acomodar um novo Funcionario
    Funcionario *novoFuncionarios = realloc(*funcionarios, (tamanhoAtual + 1) * sizeof(Funcionario));
    if (novoFuncionarios == NULL) {
        printf("Erro ao alocar memória para Funcionários.\n");
        return FALSE; // Retorna -1 indicando falha
    }

    *funcionarios = novoFuncionarios; // Atualiza o ponteiro de Funcionario com o novo endereço
    int index = tamanhoAtual; // Novo índice é o tamanho atual

    // Preenche os dados do novo Funcionario no array
    (*funcionarios)[index].codigo = buscaNovoIDFuncionario(*funcionarios);
    strcpy((*funcionarios)[index].nome, funcionario->nome);
    strcpy((*funcionarios)[index].cpf, funcionario->cpf);
    strcpy((*funcionarios)[index].endereco, funcionario->endereco);
    strcpy((*funcionarios)[index].telefone, funcionario->telefone);
    strcpy((*funcionarios)[index].cargo, funcionario->cargo);
    (*funcionarios)[index].salario = funcionario->salario;
    (*funcionarios)[index].ativo = 1; // Funcionário ativo ao ser criado

    setTamanhoFuncionarios(); // Atualiza o tamanho dos Funcionarios

    // Salva Funcionarios se o tipo de arquivo não for memória
    if (getTipoArquivo() != MEM) setFuncionarios(*funcionarios);
    return TRUE;
}

int showFuncionario(Funcionario *funcionarios, int codigo) {
    if (funcionarios == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoFuncionarios();

    // Procura o Funcionario com o código especificado dentro do limite do array
    while (posicao < tamanho && funcionarios[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o Funcionario foi encontrado e se está ativo
    if (posicao == tamanho || funcionarios[posicao].ativo == FALSE)
        return FALSE;

    return posicao;
}
int updateFuncionario(Funcionario *funcionarios, Funcionario *funcionario) {

    int posicao = showFuncionario(funcionarios, funcionario->codigo);

    if (posicao == FALSE) return FALSE;

    // Atualiza os campos necessários
    funcionarios[posicao].codigo = funcionario->codigo;
    strcpy(funcionarios[posicao].nome, funcionario->nome);
    strcpy(funcionarios[posicao].cpf, funcionario->cpf);
    strcpy(funcionarios[posicao].endereco, funcionario->endereco);
    strcpy(funcionarios[posicao].telefone, funcionario->telefone);
    strcpy(funcionarios[posicao].cargo, funcionario->cargo);
    funcionarios[posicao].salario = funcionario->salario;
    funcionarios[posicao].ativo = funcionario->ativo; // Atualiza o campo ativo

    if (getTipoArquivo() != MEM) setFuncionarios(funcionarios);
    return TRUE;
}

int deleteFuncionario(Funcionario* funcionarios, int codigo) {
    int posicao = showFuncionario(funcionarios, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o Funcionario existe e está ativo

    funcionarios[posicao].ativo = FALSE; // Marca o Funcionario como inativo
    if (getTipoArquivo() != MEM) setFuncionarios(funcionarios);
    return TRUE;
}

int buscaNovoIDFuncionario(Funcionario * funcionarios) {
    int maior = 1;
    if(getTamanhoFuncionarios() == 0 ) return maior;
    for(int i = 0; i < getTamanhoFuncionarios(); i++) {
        if(maior <= funcionarios[i].codigo) {
            maior = funcionarios[i].codigo+1;
        }
    }
        return maior;
}
