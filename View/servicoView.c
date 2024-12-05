#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/servico.h"

// Função principal do menu de serviços
void menuServicos(Servico **servicos) {
    if (getTipoArquivo() != 3) {
        *servicos = readServicos(); // Carrega os serviços do arquivo
    }
    int opcao = -1;
    while (opcao != 0) {  // Loop até o usuário optar por sair
        printf("==== MENU SERVIÇOS ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar novo serviço\n"
            "2- Ver serviço\n"
            "3- Editar serviço\n"
            "4- Excluir serviço\n"
            "0- Sair\n");

        // Verifica qual opção o usuário escolheu e executa a ação correspondente
        switch (opcao) {
            case 1:
                novoServico(servicos);  // Chama a função para cadastrar um novo serviço
                if (getTipoArquivo() != MEM) *servicos = readServicos();  // Atualiza se não estiver em memória
                break;

            case 2:
                mostrarServico(*servicos);  // Chama a função para exibir um serviço
                break;

            case 3:
                editarServico(*servicos);  // Chama a função para editar um serviço
                break;

            case 4:
                apagarServico(*servicos);  // Chama a função para excluir um serviço
                break;
        }
    }
}

// Função para cadastrar um novo serviço
void novoServico(Servico **servicos) {
    Servico *servico = malloc(sizeof(Servico));  // Aloca memória para um novo serviço
    if (servico == NULL) {
        printf("Erro ao alocar memória para o novo serviço!\n");
        return;
    }

    // Solicita ao usuário os dados do serviço
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

    free(servico);  // Libera a memória após o cadastro
}

// Função para mostrar os dados de um serviço específico
void mostrarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado até o momento\n");
        return;
    }

    // Exibe todos os serviços cadastrados
    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);

    int codigo = lerInt("Digite o código do serviço que você deseja ver: ");
    int posicao = showServico(servicos, codigo);  // Procura o serviço pelo código

    if (posicao != FALSE) {
        // Exibe as informações do serviço encontrado
        printf("Código: %d\n"
               "Descrição: %s\n"
               "Preço: %.2f\n"
               "Comissão: %.2f\n",
               servicos[posicao].codigo,
               servicos[posicao].descricao,
               servicos[posicao].preco,
               servicos[posicao].comicao);
    } else {
        printf("Serviço não encontrado!\n");
    }
}

// Função para editar um serviço
void editarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado\n");
        return;
    }

    Servico *servico = malloc(sizeof(Servico));  // Aloca memória para um serviço temporário
    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);

    if (servico == NULL) {
        printf("Erro ao alocar memória para a edição do serviço\n");
        return;
    }

    servico->codigo = lerInt("Digite o código do serviço que você deseja editar: ");
    int posicao = showServico(servicos, servico->codigo);  // Busca o serviço

    if (posicao == FALSE) {
        printf("Serviço não encontrado.\n");
        free(servico);
        return;
    }

    // Permite que o usuário edite a descrição, preço e comissão do serviço
    // Para cada campo, o usuário é questionado se deseja editar ou manter o valor atual
    printf("A descrição do serviço é: %s\n", servicos[posicao].descricao);
    if (lerInt("Deseja editar? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(servico->descricao, lerString("Digite a nova descrição do serviço: "));
    } else {
        strcpy(servico->descricao, servicos[posicao].descricao);
    }

    printf("O preço do serviço é: %.2f\n", servicos[posicao].preco);
    if (lerInt("Deseja editar? (1 - Sim, 0 - Não): ") == TRUE) {
        servico->preco = lerFloat("Digite o novo preço do serviço: ");
    } else {
        servico->preco = servicos[posicao].preco;
    }

    printf("A comissão do serviço é: %.2f\n", servicos[posicao].comicao);
    if (lerInt("Deseja editar? (1 - Sim, 0 - Não): ") == TRUE) {
        servico->comicao = lerFloat("Digite a nova comissão do serviço: ");
    } else {
        servico->comicao = servicos[posicao].comicao;
    }

    // Atualiza os dados do serviço no sistema
    if (updateServico(servicos, servico) == FALSE) {
        printf("Erro na edição dos dados do serviço\n");
    } else {
        printf("Serviço editado com sucesso!\n");
    }

    free(servico);  // Libera a memória após a edição
}

// Função para excluir um serviço
void apagarServico(Servico *servicos) {
    if (getTamanhoServicos() == 0) {
        printf("Nenhum serviço cadastrado\n");
        return;
    }
    printf("\tSERVIÇOS:\n");
    mostrarTodosServicos(servicos);
    int codigo = lerInt("Digite o código do serviço que você deseja apagar: ");
    if (deleteServico(servicos, codigo) == TRUE) {
        printf("Serviço apagado com sucesso\n");
    } else {
        printf("Serviço não existe\n");
    }
}

// Função para exibir todos os serviços cadastrados
void mostrarTodosServicos(Servico *servicos) {
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (servicos[i].ativo != FALSE)  // Exibe apenas os serviços ativos
            printf("Serviço: %s Codigo: %d\n", servicos[i].descricao, servicos[i].codigo);
    }
}
