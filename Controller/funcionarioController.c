#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/funcionario.h"
#include "../bibliotecas/utils.h"

// Função para ler os funcionários do sistema
Funcionario* readFuncionarios() {
    Funcionario * funcionarios = NULL; // Inicializa o ponteiro como NULL
    funcionarios = getFuncionarios(); // Obtém os funcionários armazenados (função externa)
    return funcionarios; // Retorna o ponteiro para a lista de funcionários
}

// Função para criar e adicionar um novo funcionário à lista
int createFuncionario(Funcionario **funcionarios, Funcionario *funcionario) {
    int tamanhoAtual = getTamanhoFuncionarios(); // Obtém o tamanho atual da lista de funcionários

    // Realoca memória para incluir o novo funcionário
    Funcionario *novoFuncionarios = realloc(*funcionarios, (tamanhoAtual + 1) * sizeof(Funcionario));
    if (novoFuncionarios == NULL) { // Verifica falha na alocação
        printf("Erro ao alocar memória para Funcionários.\n");
        return FALSE; // Retorna -1 indicando falha
    }

    *funcionarios = novoFuncionarios; // Atualiza o ponteiro da lista de funcionários
    int index = tamanhoAtual; // Índice do novo funcionário

    // Preenche os dados do novo funcionário
    (*funcionarios)[index].codigo = buscaNovoIDFuncionario(*funcionarios);
    strcpy((*funcionarios)[index].nome, funcionario->nome);
    strcpy((*funcionarios)[index].cpf, funcionario->cpf);
    strcpy((*funcionarios)[index].endereco, funcionario->endereco);
    strcpy((*funcionarios)[index].telefone, funcionario->telefone);
    strcpy((*funcionarios)[index].cargo, funcionario->cargo);
    (*funcionarios)[index].salario = funcionario->salario;
    (*funcionarios)[index].ativo = 1; // Define o funcionário como ativo

    setTamanhoFuncionarios(); // Atualiza o tamanho total da lista

    // Salva os dados atualizados caso o tipo de arquivo seja diferente de memória
    if (getTipoArquivo() != MEM) setFuncionarios(*funcionarios);

    return TRUE; // Retorna sucesso
}

// Função para exibir os dados de um funcionário com base no código
int showFuncionario(Funcionario *funcionarios, int codigo) {
    if (funcionarios == NULL) return FALSE; // Verifica se a lista está vazia

    int posicao = 0;
    int tamanho = getTamanhoFuncionarios(); // Obtém o tamanho da lista

    // Procura pelo funcionário com o código especificado
    while (posicao < tamanho && funcionarios[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o funcionário foi encontrado e está ativo
    if (posicao == tamanho || funcionarios[posicao].ativo == FALSE)
        return FALSE;

    return posicao; // Retorna a posição do funcionário encontrado
}

// Função para atualizar os dados de um funcionário
int updateFuncionario(Funcionario *funcionarios, Funcionario *funcionario) {
    int posicao = showFuncionario(funcionarios, funcionario->codigo); // Encontra a posição do funcionário

    if (posicao == FALSE) return FALSE; // Verifica se o funcionário existe

    // Atualiza os dados do funcionário na posição encontrada
    funcionarios[posicao].codigo = funcionario->codigo;
    strcpy(funcionarios[posicao].nome, funcionario->nome);
    strcpy(funcionarios[posicao].cpf, funcionario->cpf);
    strcpy(funcionarios[posicao].endereco, funcionario->endereco);
    strcpy(funcionarios[posicao].telefone, funcionario->telefone);
    strcpy(funcionarios[posicao].cargo, funcionario->cargo);
    funcionarios[posicao].salario = funcionario->salario;
    funcionarios[posicao].ativo = funcionario->ativo; // Atualiza o status ativo

    if (getTipoArquivo() != MEM) setFuncionarios(funcionarios); // Salva os dados atualizados
    return TRUE; // Retorna sucesso
}

// Função para deletar (desativar) um funcionário
int deleteFuncionario(Funcionario* funcionarios, int codigo) {
    int posicao = showFuncionario(funcionarios, codigo); // Encontra a posição do funcionário

    if (posicao == FALSE) return FALSE; // Verifica se o funcionário existe

    funcionarios[posicao].ativo = FALSE; // Marca o funcionário como inativo
    if (getTipoArquivo() != MEM) setFuncionarios(funcionarios); // Salva os dados atualizados
    return TRUE; // Retorna sucesso
}

// Função para buscar um novo ID único para um funcionário
int buscaNovoIDFuncionario(Funcionario * funcionarios) {
    int maior = 1; // Inicializa o maior ID com 1
    if(getTamanhoFuncionarios() == 0) return maior; // Se não há funcionários, retorna 1

    // Percorre a lista para encontrar o maior ID atual
    for(int i = 0; i < getTamanhoFuncionarios(); i++) {
        if(maior <= funcionarios[i].codigo) {
            maior = funcionarios[i].codigo + 1; // Atualiza o maior ID
        }
    }
    return maior; // Retorna o novo ID
}
