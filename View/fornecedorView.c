#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

// Menu para gerenciar fornecedores
void menuFornecedor(Fornecedor **fornecedores) {
    // Carrega fornecedores do arquivo se não estiver usando a opção de memória
    if (getTipoArquivo() != 3) {
        *fornecedores = readFornecedores();
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\t==== MENU FORNECEDOR ====\n");
        opcao = lerInt("DIGITE A OPÇÃO DESEJADA:\n"
                       "\t\t\t1- CADASTRAR NOVO FORNECEDOR\n"
                       "\t\t\t2- VER FORNECEDORES\n"
                       "\t\t\t3- EDITAR FORNECEDOR\n"
                       "\t\t\t4- EXCLUIR FORNECEDOR\n"
                       "\t\t\t0- SAIR\n"
                       "=>");

        switch (opcao) {
            case 1:
                novoFornecedor(fornecedores); // Cadastra novo fornecedor
                if (getTipoArquivo() != MEM) *fornecedores = getFornecedores();
                opcao = -1;
                break;

            case 2:
                mostrarFornecedor(*fornecedores); // Mostra os fornecedores
                opcao = -1;
                break;

            case 3:
                editarFornecedor(*fornecedores); // Edita fornecedor existente
                opcao = -1;
                break;

            case 4:
                apagarFornecedor(*fornecedores); // Apaga fornecedor
                opcao = -1;
                break;
        }
    }
}

// Função para cadastrar novo fornecedor
void novoFornecedor(Fornecedor **fornecedores) {
    Fornecedor *fornecedor = malloc(sizeof(Fornecedor)); // Aloca memória para novo fornecedor
    strcpy(fornecedor->nome_fantasia, lerString("Digite o nome fantasia do fornecedor: "));
    strcpy(fornecedor->razao_social, lerString("Digite a razão social do fornecedor: "));
    fornecedor->incricao_estadual = lerInt("Digite a inscrição estadual do fornecedor: ");
    strcpy(fornecedor->cnpj, lerString("Digite o CNPJ do fornecedor: "));
    strcpy(fornecedor->endereco, lerString("Digite o endereço completo do fornecedor: "));
    strcpy(fornecedor->telefone, lerString("Digite o telefone do fornecedor: "));
    strcpy(fornecedor->email, lerString("Digite o email do fornecedor: "));
    fornecedor->ativo = 1; // Define o fornecedor como ativo

    if (createFornecedor(fornecedores, fornecedor) != FALSE) {
        printf("Fornecedor cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do fornecedor!\n");
    }

    printf("Tamanho dos fornecedores: %d\n", getTamanhoFornecedores());
    free(fornecedor); // Libera a memória alocada
}

// Função para exibir informações de fornecedores
void mostrarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado até o momento\n");
        return;
    }

    printf("\tFORNECEDORES:\n");
    mostrarTodosFornecedores(fornecedores); // Mostra todos os fornecedores

    int codigo = lerInt("Digite o código do fornecedor que você deseja ver: ");
    int posicao = showFornecedor(fornecedores, codigo); // Retorna a posição do fornecedor

    if (posicao != FALSE) {
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
        printf("Fornecedor não encontrado!\n");
    }
}

// Função para editar fornecedores
void editarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado\n");
        return;
    }

    Fornecedor *fornecedor = malloc(sizeof(Fornecedor));
    if (fornecedor == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }

    mostrarTodosFornecedores(fornecedores);
    fornecedor->codigo = lerInt("Digite o código do fornecedor que você deseja editar: ");
    int posicao = showFornecedor(fornecedores, fornecedor->codigo);

    if (posicao == FALSE) {
        printf("Fornecedor não encontrado.\n");
        free(fornecedor);
        return;
    }

    printf("O nome fantasia do fornecedor é: %s\n", fornecedores[posicao].nome_fantasia);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    strcpy(fornecedor->nome_fantasia, opcao ? lerString("Digite o novo nome fantasia: ") : fornecedores[posicao].nome_fantasia);

    // Edição dos demais campos segue o mesmo padrão

    if (updateFornecedor(fornecedores, fornecedor) == FALSE) {
        printf("Erro na edição dos dados do fornecedor\n");
    } else {
        printf("Fornecedor editado com sucesso!\n");
    }

    free(fornecedor);
}

// Função para apagar fornecedores
void apagarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado\n");
        return;
    }
    mostrarTodosFornecedores(fornecedores);
    int codigo = lerInt("Digite o código do fornecedor que você deseja apagar: ");
    if (deleteFornecedor(fornecedores, codigo) == TRUE) {
        printf("Fornecedor apagado com sucesso\n");
    } else {
        printf("Fornecedor não existe\n");
    }
}

// Função para listar todos os fornecedores ativos
void mostrarTodosFornecedores(Fornecedor *fornecedores) {
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        if (fornecedores[i].ativo != FALSE)
            printf("Fornecedor: %s | Código: %d\n", fornecedores[i].nome_fantasia, fornecedores[i].codigo);
    }
}
