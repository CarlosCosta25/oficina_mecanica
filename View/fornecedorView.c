#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

void menuFornecedor(Fornecedor **fornecedores) {

    if (getTipoArquivo() != 3) {
        *fornecedores = readFornecedores();
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("==== MENU FORNECEDOR ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
                       "1- Cadastrar novo fornecedor\n"
                       "2- Ver fornecedores\n"
                       "3- Editar fornecedor\n"
                       "4- Excluir fornecedor\n"
                       "0- Sair\n");
        switch (opcao) {
            case 1:
                novoFornecedor(fornecedores);
            if (getTipoArquivo() != MEM) *fornecedores = getFornecedores();
            opcao = -1;
            break;

            case 2:
                mostrarFornecedor(*fornecedores);
            opcao = -1;
            break;
            case 3:
                editarFornecedor(*fornecedores);
            opcao = -1;
            break;
            case 4:
                apagarFornecedor(*fornecedores);
            opcao = -1;
            break;
        }
    }
    //principal_fornecedores = fornecedores;
    //free(fornecedores);
    //fornecedores = NULL;
}


void novoFornecedor(Fornecedor **fornecedores) {
    Fornecedor *fornecedor = malloc(sizeof(Fornecedor));
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

    free(fornecedor); // Libera a memória do fornecedor após o cadastro
}


void mostrarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado até o momento\n");
        return;
    }

    printf("\tFORNECEDORES:\n");
    mostrarTodosFornecedores(fornecedores);

    int codigo = lerInt("Digite o código do fornecedor que você deseja ver: ");
    int posicao = showFornecedor(fornecedores, codigo); // Assume que showFornecedor foi implementado

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
               fornecedores[posicao].email
        ); // Exibe as informações do fornecedor
    } else {
        printf("Fornecedor não encontrado!\n");
    }
}

void editarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado\n");
        return;
    }

    Fornecedor *fornecedor = malloc(sizeof(Fornecedor));
    if (fornecedor == NULL) {
        printf("Erro ao alocar memória para a edição do fornecedor\n");
        return;
    }

    printf("\tFORNECEDORES:\n");
    mostrarTodosFornecedores(fornecedores);

    fornecedor->codigo = lerInt("Digite o código do fornecedor que você deseja editar: ");

    // Procurar o fornecedor
    int posicao = showFornecedor(fornecedores, fornecedor->codigo);

    if (posicao == FALSE) {
        printf("Fornecedor não encontrado.\n");
        free(fornecedor);
        return;
    }

    // Edição do campo `nome_fantasia`
    printf("O nome fantasia do fornecedor é: %s\n", fornecedores[posicao].nome_fantasia);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->nome_fantasia, lerString("Digite o novo nome fantasia do fornecedor: "));
    } else {
        strcpy(fornecedor->nome_fantasia, fornecedores[posicao].nome_fantasia);
    }

    // Edição do campo `razao_social`
    printf("A razão social do fornecedor é: %s\n", fornecedores[posicao].razao_social);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->razao_social, lerString("Digite a nova razão social do fornecedor: "));
    } else {
        strcpy(fornecedor->razao_social, fornecedores[posicao].razao_social);
    }

    // Edição do campo `incricao_estadual`
    printf("A inscrição estadual do fornecedor é: %d\n", fornecedores[posicao].incricao_estadual);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        fornecedor->incricao_estadual = lerInt("Digite a nova inscrição estadual do fornecedor: ");
    } else {
        fornecedor->incricao_estadual = fornecedores[posicao].incricao_estadual;
    }

    // Edição do campo `cnpj`
    printf("O CNPJ do fornecedor é: %s\n", fornecedores[posicao].cnpj);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->cnpj, lerString("Digite o novo CNPJ do fornecedor: "));
    } else {
        strcpy(fornecedor->cnpj, fornecedores[posicao].cnpj);
    }

    // Edição do campo `endereco`
    printf("O endereço do fornecedor é: %s\n", fornecedores[posicao].endereco);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->endereco, lerString("Digite o novo endereço completo do fornecedor: "));
    } else {
        strcpy(fornecedor->endereco, fornecedores[posicao].endereco);
    }

    // Edição do campo `telefone`
    printf("O telefone do fornecedor é: %s\n", fornecedores[posicao].telefone);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->telefone, lerString("Digite o novo telefone do fornecedor: "));
    } else {
        strcpy(fornecedor->telefone, fornecedores[posicao].telefone);
    }

    // Edição do campo `email`
    printf("O email do fornecedor é: %s\n", fornecedores[posicao].email);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(fornecedor->email, lerString("Digite o novo email do fornecedor: "));
    } else {
        strcpy(fornecedor->email, fornecedores[posicao].email);
    }

    if (updateFornecedor(fornecedores, fornecedor) == FALSE) {
        printf("Erro na edição dos dados do fornecedor\n");
    } else {
        printf("Fornecedor editado com sucesso!\n");
    }

    free(fornecedor); // Libera a memória alocada
}

void apagarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado\n");
        return;
    }
    printf("\tFORNECEDORES:\n");
    mostrarTodosFornecedores(fornecedores);

    int codigo = lerInt("Digite o código do fornecedor que você deseja apagar: ");
    if (deleteFornecedor(fornecedores, codigo) == TRUE) { // Presumindo que deleteFornecedor foi implementado
        printf("Fornecedor apagado com sucesso\n");
    } else {
        printf("Fornecedor não existe\n");
    }
}
void mostrarTodosFornecedores(Fornecedor * fornecedores) {
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        if(fornecedores[i].ativo != FALSE)
        printf("Fornecedor: %s Codigo: %d\n",fornecedores[i].nome_fantasia,fornecedores[i].codigo);
    }
}


