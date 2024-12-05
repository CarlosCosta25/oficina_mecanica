#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"
#include "../bibliotecas/peca.h"

// Função principal do menu de peças
void menuPecas(Peca **pecas, Fornecedor *fornecedores) {
    // Verifica se a leitura deve ser feita do arquivo ou da memória
    if (getTipoArquivo() != 3) {
        *pecas = readPecas();
        fornecedores = readFornecedores(); // Lê os fornecedores
    }

    int opcao = -1;
    // Loop do menu até que o usuário escolha a opção de sair
    while (opcao != 0) {
        printf("==== MENU PEÇAS ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar nova peça\n"
            "2- Ver peça\n"
            "3- Editar peça\n"
            "4- Excluir peça\n"
            "0- Sair\n");

        // Estrutura de controle de fluxo com base na escolha do usuário
        switch (opcao) {
            case 1:
                novaPeca(pecas, fornecedores); // Cadastra uma nova peça
                if (getTipoArquivo() != MEM) *pecas = readPecas(); // Atualiza as peças
                break;

            case 2:
                mostrarPeca(*pecas); // Exibe informações de uma peça
                break;
            case 3:
                editarPeca(*pecas, fornecedores); // Edita uma peça existente
                break;
            case 4:
                apagarPeca(*pecas); // Exclui uma peça
                break;
        }
    }
}

// Função que cadastra uma nova peça
void novaPeca(Peca **pecas, Fornecedor *fornecedores) {
    Peca *peca = malloc(sizeof(Peca)); // Aloca memória para a nova peça
    if (peca == NULL) {
        printf("Erro ao alocar memória para a nova peça!\n");
        return;
    }

    // Coleta informações do usuário sobre a peça
    strcpy(peca->descricao, lerString("Digite a descrição da peça: "));
    strcpy(peca->fabricante, lerString("Digite o nome do fabricante: "));

    printf("\tFORNECEDORES: \n");
    mostrarTodosFornecedores(fornecedores); // Exibe todos os fornecedores disponíveis

    peca->fornecedor = lerInt("Digite o código do fornecedor: ");
    if (showFornecedor(fornecedores, peca->fornecedor) == FALSE) {
        printf("Fornecedor não existe, por favor tente novamente");
        free(peca);
        return;
    }

    peca->preco_custo = lerFloat("Digite o preço de custo da peça: ");
    peca->preco_venda = lerFloat("Digite o preço de venda da peça: ");
    peca->estoque = lerInt("Digite a quantidade em estoque: ");
    peca->estoque_min = lerInt("Digite o estoque mínimo: ");

    // Chama a função para adicionar a peça à lista
    if (createPeca(pecas, peca) != FALSE) {
        printf("Peça cadastrada com sucesso!\n");
    } else {
        printf("Erro no cadastro da peça!\n");
    }

    // Exibe o tamanho da lista de peças
    printf("Tamanho das peças: %d\n", getTamanhoPecas());

    free(peca); // Libera a memória alocada para a peça
}

// Função que exibe os dados de uma peça
void mostrarPeca(Peca *pecas) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada até o momento\n");
        return;
    }

    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas); // Exibe todas as peças cadastradas

    // Solicita ao usuário o código da peça que deseja visualizar
    int codigo = lerInt("Digite o código da peça que você deseja ver: ");
    int posicao = showPeca(pecas, codigo); // Verifica se a peça existe

    if (posicao != FALSE) {
        // Exibe os detalhes da peça encontrada
        printf("Código: %d\n"
               "Descrição: %s\n"
               "Fabricante: %s\n"
               "Código do Fornecedor: %d\n"
               "Preço de Custo: %.2f\n"
               "Preço de Venda: %.2f\n"
               "Estoque: %d\n"
               "Estoque Mínimo: %d\n",
               pecas[posicao].codigo,
               pecas[posicao].descricao,
               pecas[posicao].fabricante,
               pecas[posicao].fornecedor,
               pecas[posicao].preco_custo,
               pecas[posicao].preco_venda,
               pecas[posicao].estoque,
               pecas[posicao].estoque_min
        );
    } else {
        printf("Peça não encontrada!\n");
    }
}

// Função que edita uma peça existente
void editarPeca(Peca *pecas, Fornecedor *fornecedores) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada\n");
        return;
    }

    Peca *novaPeca = malloc(sizeof(Peca)); // Aloca memória para a nova versão da peça
    if (novaPeca == NULL) {
        printf("Erro ao alocar memória para a edição da peça\n");
        return;
    }

    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas); // Exibe todas as peças cadastradas

    novaPeca->codigo = lerInt("Digite o código da peça que você deseja editar: ");

    int posicao = showPeca(pecas, novaPeca->codigo); // Procura pela peça

    if (posicao == FALSE) {
        printf("Peça não encontrada.\n");
        free(novaPeca);
        return;
    }

    // Solicita ao usuário para editar os dados da peça, conforme necessário
    // Para cada campo, o programa pergunta se o usuário deseja alterar o valor ou manter o valor atual

    // [Processo similar para descrição, fabricante, fornecedor, preço de custo, preço de venda, estoque, estoque mínimo]

    if (updatePeca(&pecas[posicao], novaPeca) == FALSE) {
        printf("Erro na edição dos dados da peça\n");
    } else {
        printf("Peça editada com sucesso!\n");
    }

    free(novaPeca);
}

// Função que exclui uma peça
void apagarPeca(Peca *pecas) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada\n");
        return;
    }

    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas); // Exibe todas as peças cadastradas

    int codigo = lerInt("Digite o código da peça que você deseja apagar: ");
    if (deletePeca(pecas, codigo) == TRUE) {
        printf("Peça apagada com sucesso\n");
    } else {
        printf("Peça não existe\n");
    }
}

// Função que exibe todas as peças cadastradas
void mostrarTodasPecas(Peca *pecas) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].ativo != FALSE)  // Verifica se a peça está ativa
            printf("Peça: %s Codigo: %d\n", pecas[i].descricao, pecas[i].codigo);
    }
}
