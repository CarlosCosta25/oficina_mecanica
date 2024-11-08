#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"
#include "../bibliotecas/peca.h"

void menuPecas(Peca **pecas, Fornecedor *fornecedores) {
    if (getTipoArquivo() != 3) {
        *pecas = readPecas();
        fornecedores = readFornecedores();
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("==== MENU PEÇAS ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar nova peça\n"
            "2- Ver peça\n"
            "3- Editar peça\n"
            "4- Excluir peça\n"
            "0- Sair\n");
        switch (opcao) {
            case 1:
                novaPeca(pecas, fornecedores);
                if (getTipoArquivo() != MEM) *pecas = readPecas();
                opcao = -1;
                break;

            case 2:
                mostrarPeca(*pecas);
                opcao = -1;
                break;
            case 3:
                editarPeca(*pecas, fornecedores);
                opcao = -1;
                break;
            case 4:
                apagarPeca(*pecas);
                opcao = -1;
                break;
        }
    }
}

void novaPeca(Peca **pecas, Fornecedor *fornecedores) {
    Peca *peca = malloc(sizeof(Peca));
    if (peca == NULL) {
        printf("Erro ao alocar memória para a nova peça!\n");
        return;
    }
    strcpy(peca->descricao, lerString("Digite a descrição da peça: "));
    strcpy(peca->fabricante, lerString("Digite o nome do fabricante: "));
    printf("\tFORNECEDORES: \n");
    mostrarTodosFornecedores(fornecedores);

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

    if (createPeca(pecas, peca) != FALSE) {
        printf("Peça cadastrada com sucesso!\n");
    } else {
        printf("Erro no cadastro da peça!\n");
    }

    printf("Tamanho das peças: %d\n", getTamanhoPecas());

    free(peca); // Libera a memória da peça após o cadastro
}

void mostrarPeca(Peca *pecas) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada até o momento\n");
        return;
    }

    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas);

    int codigo = lerInt("Digite o código da peça que você deseja ver: ");
    int posicao = showPeca(pecas, codigo); // Assume que showPeca foi implementada

    if (posicao != FALSE) {
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
        ); // Exibe as informações da peça
    } else {
        printf("Peça não encontrada!\n");
    }
}

void editarPeca(Peca *pecas, Fornecedor *fornecedores) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada\n");
        return;
    }

    Peca *peca = malloc(sizeof(Peca));
    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas);
    if (peca == NULL) {
        printf("Erro ao alocar memória para a edição da peça\n");
        return;
    }

    peca->codigo = lerInt("Digite o código da peça que você deseja editar: ");

    // Procurar a peça
    int posicao = showPeca(pecas, peca->codigo); // Assume que showPeca foi implementada

    if (posicao == FALSE) {
        printf("Peça não encontrada.\n");
        free(peca);
        return;
    }

    strcpy(peca->descricao, lerString("Digite a nova descrição da peça: "));
    strcpy(peca->fabricante, lerString("Digite o novo nome do fabricante: "));

    // Atualização do campo `fornecedor`

    int fornecedor = lerInt("Digite o código do fornecedor: ");

    printf("\tFORNECEDORES: \n");
    mostrarTodosFornecedores(fornecedores);
    if (showFornecedor(fornecedores, fornecedor) == FALSE) {
        // Assume que showFornecedor foi implementada
        printf("Fornecedor não existe, por favor tente novamente.\n");
        return;
    }

    peca->fornecedor = fornecedor;

    peca->preco_custo = lerFloat("Digite o novo preço de custo da peça: ");
    peca->preco_venda = lerFloat("Digite o novo preço de venda da peça: ");
    peca->estoque = lerInt("Digite a nova quantidade em estoque: ");
    peca->estoque_min = lerInt("Digite o novo estoque mínimo: ");

    if (updatePeca(pecas, peca) == FALSE) {
        // Assume que updatePeca foi implementada
        printf("Erro na edição dos dados da peça\n");
    } else {
        printf("Peça editada com sucesso!\n");
    }

    free(peca); // Libera a memória alocada
}

void apagarPeca(Peca *pecas) {
    if (getTamanhoPecas() == 0) {
        printf("Nenhuma peça cadastrada\n");
        return;
    }
    printf("\tPEÇAS:\n");
    mostrarTodasPecas(pecas);
    int codigo = lerInt("Digite o código da peça que você deseja apagar: ");
    if (deletePeca(pecas, codigo) == TRUE) {
        // Presumindo que deletePeca foi implementada
        printf("Peça apagada com sucesso\n");
    } else {
        printf("Peça não existe\n");
    }
}

void mostrarTodasPecas(Peca *pecas) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (pecas[i].ativo != FALSE)
            printf("Peça: %s Codigo: %d\n", pecas[i].descricao, pecas[i].codigo);
    }
}
