#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/servico.h"

void menuServicos(Servico **servicos) {
    if (getTipoArquivo() != 3) {
        *servicos = readServicos(); // Carrega os serviços
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("==== MENU SERVIÇOS ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar novo serviço\n"
            "2- Ver serviço\n"
            "3- Editar serviço\n"
            "4- Excluir serviço\n"
            "0- Sair\n");
        switch (opcao) {
            case 1:
                novoServico(servicos);  // Função para cadastrar um novo serviço
            if (getTipoArquivo() != MEM) *servicos = readServicos(); // Atualiza os serviços se não estiver em memória
            opcao = -1;
            break;

            case 2:
                mostrarServico(*servicos); // Função para exibir um serviço
            opcao = -1;
            break;
            case 3:
                editarServico(*servicos);  // Função para editar um serviço
            opcao = -1;
            break;
            case 4:
                apagarServico(*servicos);  // Função para excluir um serviço
            opcao = -1;
            break;
        }
    }
}

void novoServico(Servico **servicos) {
    Servico *servico = malloc(sizeof(Servico));
    if (servico == NULL) {
        printf("Erro ao alocar memória para o novo serviço!\n");
        return;
    }

    // Solicita a descrição e preço do serviço
    strcpy(servico->descricao, lerString("Digite a descrição do serviço: "));
    servico->preco = lerFloat("Digite o preço do serviço: ");
    servico->comicao = lerFloat("Digite a comissão sobre o serviço: ");

    // Tenta cadastrar o serviço
    if (createServico(servicos, servico) != FALSE) {
        printf("Serviço cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do serviço!\n");
    }

    printf("Tamanho dos serviços: %d\n", getTamanhoServicos());

    free(servico); // Libera a memória do serviço após o cadastro
}
void mostrarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado até o momento\n");
        return;
    }

    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);

    int codigo = lerInt("Digite o código do serviço que você deseja ver: ");
    int posicao = showServico(servicos, codigo); // Assume que showServico foi implementada

    if (posicao != FALSE) {
        printf("Código: %d\n"
               "Descrição: %s\n"
               "Preço: %.2f\n"
               "Comissão: %.2f\n",
               servicos[posicao].codigo,
               servicos[posicao].descricao,
               servicos[posicao].preco,
               servicos[posicao].comicao
        ); // Exibe as informações do serviço
    } else {
        printf("Serviço não encontrado!\n");
    }
}
void editarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado\n");
        return;
    }

    Servico *servico = malloc(sizeof(Servico));
    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);
    if (servico == NULL) {
        printf("Erro ao alocar memória para a edição do serviço\n");
        return;
    }

    servico->codigo = lerInt("Digite o código do serviço que você deseja editar: ");

    // Procurar o serviço
    int posicao = showServico(servicos, servico->codigo);

    if (posicao == FALSE) {
        printf("Serviço não encontrado.\n");
        free(servico);
        return;
    }

    // Edição do campo `descricao`
    printf("A descrição do serviço é: %s\n", servicos[posicao].descricao);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(servico->descricao, lerString("Digite a nova descrição do serviço: "));
    } else {
        strcpy(servico->descricao, servicos[posicao].descricao);
    }

    // Edição do campo `preco`
    printf("O preço do serviço é: %.2f\n", servicos[posicao].preco);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        servico->preco = lerFloat("Digite o novo preço do serviço: ");
    } else {
        servico->preco = servicos[posicao].preco;
    }

    // Edição do campo `comicao`
    printf("A comissão do serviço é: %.2f\n", servicos[posicao].comicao);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        servico->comicao = lerFloat("Digite a nova comissão do serviço: ");
    } else {
        servico->comicao = servicos[posicao].comicao;
    }

    if (updateServico(servicos, servico) == FALSE) {
        printf("Erro na edição dos dados do serviço\n");
    } else {
        printf("Serviço editado com sucesso!\n");
    }

    free(servico); // Libera a memória alocada
}

void apagarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado\n");
        return;
    }
    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);
    int codigo = lerInt("Digite o código do serviço que você deseja apagar: ");
    if (deleteServico(servicos, codigo) == TRUE) {
        // Presumindo que deleteServico foi implementada
        printf("Serviço apagado com sucesso\n");
    } else {
        printf("Serviço não existe\n");
    }
}

void mostrarTodosServicos(Servico *servicos) {
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (servicos[i].ativo != FALSE)
            printf("Serviço: %s Codigo: %d\n", servicos[i].descricao, servicos[i].codigo);
    }
}
