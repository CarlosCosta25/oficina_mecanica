#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

// Função principal para exibição e manipulação do menu de fornecedores
void menuFornecedor(Fornecedor **fornecedores) {
    // Verifica se os fornecedores precisam ser carregados do arquivo
    if (getTipoArquivo() != 3) {
        *fornecedores = readFornecedores(); // Carrega os fornecedores do armazenamento
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n========== MENU FORNECEDOR ==========\n");
        printf("1 - Cadastrar novo fornecedor\n");
        printf("2 - Visualizar fornecedores cadastrados\n");
        printf("3 - Editar informações de um fornecedor\n");
        printf("4 - Excluir fornecedor\n");
        printf("0 - Sair\n");

        opcao = lerInt("Escolha uma opção: ");

        switch (opcao) {
            case 1: // Cadastro de um novo fornecedor
                novoFornecedor(fornecedores);
                if (getTipoArquivo() != MEM) *fornecedores = getFornecedores();
                break;

            case 2: // Exibição de todos os fornecedores
                mostrarFornecedor(*fornecedores);
                break;

            case 3: // Edição de um fornecedor existente
                editarFornecedor(*fornecedores);
                break;

            case 4: // Exclusão de um fornecedor
                apagarFornecedor(*fornecedores);
                break;

            case 0: // Opção de sair do menu
                printf("Saindo do menu fornecedor...\n");
                break;

            default: // Opção inválida
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
        }
    }
}

// Função para cadastrar um novo fornecedor
void novoFornecedor(Fornecedor **fornecedores) {
    Fornecedor *fornecedor = malloc(sizeof(Fornecedor)); // Aloca memória para o novo fornecedor
    if (fornecedor == NULL) {
        printf("Erro ao alocar memória para o fornecedor.\n");
        return;
    }

    // Captura os dados do fornecedor
    strcpy(fornecedor->nome_fantasia, lerString("Digite o nome fantasia do fornecedor: "));
    strcpy(fornecedor->razao_social, lerString("Digite a razão social do fornecedor: "));
    fornecedor->incricao_estadual = lerInt("Digite a inscrição estadual do fornecedor: ");
    strcpy(fornecedor->cnpj, lerString("Digite o CNPJ do fornecedor: "));
    strcpy(fornecedor->endereco, lerString("Digite o endereço completo do fornecedor: "));
    strcpy(fornecedor->telefone, lerString("Digite o telefone do fornecedor: "));
    strcpy(fornecedor->email, lerString("Digite o email do fornecedor: "));
    fornecedor->ativo = 1; // Marca o fornecedor como ativo

    // Adiciona o fornecedor ao sistema
    if (createFornecedor(fornecedores, fornecedor) != FALSE) {
        printf("Fornecedor cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar o fornecedor.\n");
    }

    free(fornecedor); // Libera a memória do fornecedor temporário
}

// Função para mostrar os fornecedores cadastrados
void mostrarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    printf("\n========== LISTA DE FORNECEDORES ==========\n");
    mostrarTodosFornecedores(fornecedores); // Mostra todos os fornecedores ativos

    int codigo = lerInt("Digite o código do fornecedor que deseja visualizar: ");
    int posicao = showFornecedor(fornecedores, codigo);

    if (posicao != FALSE) {
        // Exibe os detalhes do fornecedor selecionado
        printf("\nFornecedor selecionado:\n");
        printf("Código: %d\n"
               "Nome Fantasia: %s\n"
               "Razão Social: %s\n"
               "Endereço: %s\n"
               "CNPJ: %s\n"
               "Telefone: %s\n"
               "E-mail: %s\n",
               fornecedores[posicao].codigo,
               fornecedores[posicao].nome_fantasia,
               fornecedores[posicao].razao_social,
               fornecedores[posicao].endereco,
               fornecedores[posicao].cnpj,
               fornecedores[posicao].telefone,
               fornecedores[posicao].email);
    } else {
        printf("Fornecedor não encontrado.\n");
    }
}

// Função para editar um fornecedor
void editarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado para editar.\n");
        return;
    }

    printf("\n========== EDITAR FORNECEDOR ==========\n");
    mostrarTodosFornecedores(fornecedores); // Mostra todos os fornecedores ativos

    int codigo = lerInt("Digite o código do fornecedor que deseja editar: ");
    int posicao = showFornecedor(fornecedores, codigo);

    if (posicao == FALSE) {
        printf("Fornecedor não encontrado.\n");
        return;
    }

    // Permite a edição dos campos um por um
    Fornecedor fornecedor = fornecedores[posicao]; // Copia os dados para edição local
    printf("Editando o fornecedor: %s\n", fornecedor.nome_fantasia);

    strcpy(fornecedor.nome_fantasia, lerString("Novo nome fantasia (pressione Enter para manter o atual): "));
    strcpy(fornecedor.razao_social, lerString("Nova razão social (pressione Enter para manter o atual): "));
    fornecedor.incricao_estadual = lerInt("Nova inscrição estadual (digite -1 para manter o atual): ");
    strcpy(fornecedor.cnpj, lerString("Novo CNPJ (pressione Enter para manter o atual): "));
    strcpy(fornecedor.endereco, lerString("Novo endereço (pressione Enter para manter o atual): "));
    strcpy(fornecedor.telefone, lerString("Novo telefone (pressione Enter para manter o atual): "));
    strcpy(fornecedor.email, lerString("Novo email (pressione Enter para manter o atual): "));

    if (updateFornecedor(fornecedores, &fornecedor) == FALSE) {
        printf("Erro ao atualizar o fornecedor.\n");
    } else {
        printf("Fornecedor atualizado com sucesso!\n");
    }
}

// Função para excluir um fornecedor
void apagarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado para excluir.\n");
        return;
    }

    printf("\n========== EXCLUIR FORNECEDOR ==========\n");
    mostrarTodosFornecedores(fornecedores);

    int codigo = lerInt("Digite o código do fornecedor que deseja excluir: ");
    if (deleteFornecedor(fornecedores, codigo) == TRUE) {
        printf("Fornecedor excluído com sucesso.\n");
    } else {
        printf("Erro: fornecedor não encontrado.\n");
    }
}

// Função para exibir todos os fornecedores ativos
void mostrarTodosFornecedores(Fornecedor *fornecedores) {
    printf("\nFornecedores cadastrados:\n");
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        if (fornecedores[i].ativo != FALSE) {
            printf("Código: %d - Nome Fantasia: %s\n", fornecedores[i].codigo, fornecedores[i].nome_fantasia);
        }
    }
}
