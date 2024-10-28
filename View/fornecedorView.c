#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

void menuFornecedor() {
    Fornecedor *fornecedores = migraDadosFornecedor();
    if (getTipoArquivo() != 3) {
        fornecedores = readFornecedores();
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
                novoFornecedor(&fornecedores);
            if (getTipoArquivo() != MEM) fornecedores = getFornecedores();
            opcao = -1;
            break;

            case 2:
                mostrarFornecedor(fornecedores);
            opcao = -1;
            break;
            case 3:
                editarFornecedor(fornecedores);
            opcao = -1;
            break;
            case 4:
                apagarFornecedor(fornecedores);
            opcao = -1;
            break;
        }
    }
    free(fornecedores);
    fornecedores = NULL;
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

    for (int i = 0; i < getTamanhoFornecedores(); i++) {
    if(fornecedores[i].ativo != FALSE)
        printf("Fornecedor: %s Código: %d\n\n", fornecedores[i].nome_fantasia, fornecedores[i].codigo);
    }

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
    fornecedor->codigo = lerInt("Digite o código do fornecedor que você deseja editar: ");

    // Procurar o fornecedor
    int posicao = showFornecedor(fornecedores, fornecedor->codigo); // Assume que showFornecedor foi implementado

    if (posicao == FALSE) {
        printf("Fornecedor não encontrado.\n");
        free(fornecedor);
        return;
    }

    strcpy(fornecedores[posicao].nome_fantasia, lerString("Digite o novo nome fantasia do fornecedor: "));
    strcpy(fornecedores[posicao].razao_social, lerString("Digite a nova razão social do fornecedor: "));
    fornecedores[posicao].incricao_estadual = lerInt("Digite a nova inscrição estadual do fornecedor: ");
    strcpy(fornecedores[posicao].cnpj, lerString("Digite o novo CNPJ do fornecedor: "));
    strcpy(fornecedores[posicao].endereco, lerString("Digite o novo endereço completo do fornecedor: "));
    strcpy(fornecedores[posicao].telefone, lerString("Digite o novo telefone do fornecedor: "));
    strcpy(fornecedores[posicao].email, lerString("Digite o novo email do fornecedor: "));

    // O campo ativo permanece inalterado e não é necessário modificar

    if (updateFornecedor(fornecedores, &fornecedores[posicao]) == FALSE) { // Assume que updateFornecedor foi implementado
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

    int codigo = lerInt("Digite o código do fornecedor que você deseja apagar: ");
    if (deleteFornecedor(fornecedores, codigo) == TRUE) { // Presumindo que deleteFornecedor foi implementado
        printf("Fornecedor apagado com sucesso\n");
    } else {
        printf("Fornecedor não existe\n");
    }
}


