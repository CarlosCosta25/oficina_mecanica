#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/peca.h"

// Funções do controlador

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

// Função para buscar ou cadastrar um fornecedor pelo CNPJ
int buscarOuCadastrarFornecedor(Fornecedor ***fornecedores, char *cnpj) {
    // Carrega os fornecedores caso necessário
    if (getTipoArquivo() != MEM) {
        **fornecedores = readFornecedores(); // Garante que a lista é carregada do arquivo
    }

    int tamanho = getTamanhoFornecedores();
    if (tamanho <= 0 || *fornecedores == NULL) {
        printf("Nenhum fornecedor cadastrado. Cadastrando um novo fornecedor.\n");
        *fornecedores = (Fornecedor **)malloc(sizeof(Fornecedor *));
        if (*fornecedores == NULL) {
            printf("Erro ao alocar memória para fornecedores\n");
            return -1;
        }
        novoFornecedor(*fornecedores);
        return (*fornecedores)[0]->codigo;
    }

    // Busca o fornecedor pelo CNPJ
    for (int i = 0; i < tamanho; i++) {
        printf("Fornecedores[%d]: ", i);
        printf("%d", tamanho);
        printf("aqui %s", (*fornecedores)[i]->cnpj);

        if ((*fornecedores)[i] == NULL) continue; // Verifica se o ponteiro não é NULL

        int result = equalsString((*fornecedores)[i]->cnpj, cnpj);
        if (result == 1) {
            printf("Fornecedor já cadastrado: %s (Código: %d)\n",
                   (*fornecedores)[i]->nome_fantasia, (*fornecedores)[i]->codigo);
            return (*fornecedores)[i]->codigo; // Retorna o código se encontrar o fornecedor
        }
    }

    // Caso não encontre, cadastra um novo fornecedor
    printf("Fornecedor não encontrado. Cadastrando um novo fornecedor...\n");

    // Realoca memória para adicionar mais um fornecedor
    *fornecedores = (Fornecedor **)realloc(*fornecedores, (tamanho + 1) * sizeof(Fornecedor *));
    if (*fornecedores == NULL) {
        printf("Erro ao realocar memória para fornecedores\n");
        return -1;
    }

    novoFornecedor(*fornecedores);

    // Retorna o código do último fornecedor cadastrado
    return (*fornecedores)[getTamanhoFornecedores() - 1]->codigo;
}
int atualizarEstoquePeca(Peca *pecas, int codigoPeca, int qtdComprada, float precoCusto, float frete, float imposto, float lucro) {
    // Implementar atualização do estoque de peças
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].codigo == codigoPeca) {
            pecas[i].estoque += qtdComprada;
            pecas[i].preco_custo = precoCusto;
            //pecas[i].frete = frete;
           // pecas[i].imposto = imposto;
           // pecas[i].lucro = lucro;
            return 1; // Sucesso
        }
    }
    return 0; // Peça não encontrada
}

int buscarPecaPorNome(Peca *pecas, char *nome) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (strcmp(pecas[i].descricao, nome) == 0) {
            return pecas[i].codigo;
        }
    }
    return -1; // Peça não encontrada
}

void consultarPeca(int codPeca) {
    Peca *pecas = migraDadosPeca();
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].codigo == codPeca) {
            printf("Código: %d\n", pecas[i].codigo);
            printf("Nome: %s\n", pecas[i].descricao);
            printf("Quantidade: %d\n", pecas[i].estoque);
            printf("Preço de Venda: %.2f\n", pecas[i].preco_venda);
            return;
        }
    }
    printf("Peça não encontrada.\n");
}
int buscarOuCadastrarPeca(Peca **pecas, char *nomePeca, int codFornecedor) {
    // Procura a peça pelo nome
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (strcmp((*pecas)[i].descricao, nomePeca) == 0) {
            return (*pecas)[i].codigo;
        }
    }

    // Caso não encontre, cadastrar nova peça
    printf("Peça não encontrada. Cadastrando nova peça: %s\n", nomePeca);

    Peca novaPeca;
    novaPeca.codigo = getTamanhoPecas() + 1;
    strcpy(novaPeca.descricao, nomePeca);
    novaPeca.estoque = 0;  // Inicializa o estoque com 0
    novaPeca.preco_custo = 0.0;
    novaPeca.preco_venda = 0.0;
    //novaPeca.frete = 0.0;
    //novaPeca.imposto = 0.0;
    //novaPeca.lucro = 0.0;

    setTamanhoPecas(getTamanhoPecas() + 1);
    *pecas = realloc(*pecas, sizeof(Peca) * getTamanhoPecas());
    if (*pecas == NULL) {
        printf("Erro ao realocar memória.\n");
        exit(1);
    }
    (*pecas)[getTamanhoPecas() - 1] = novaPeca;
    return novaPeca.codigo;
}