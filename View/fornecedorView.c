#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

void menuFornecedor() {
    int opcao = -1;
    Fornecedor *fornecedores = readFornecedores();
    printf("==== MENU FORNECEDOR ====\n");
    while(opcao != 0) {
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar novo fornecedor\n"
            "2- Ver fornecedores\n"
            "3- Editar fornecedor\n"
            "4- Excluir fornecedor\n"
            "0- Sair\n");
        switch(opcao) {
            case 1:
                novoFornecedor(fornecedores);
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

void novoFornecedor(Fornecedor *fornecedores) {
    Fornecedor *fornecedor = malloc(sizeof(Fornecedor));
    strcpy(fornecedor->nome_fantasia, lerString("Digite o nome fantasia do fornecedor: "));
    strcpy(fornecedor->razao_social, lerString("Digite a razão social do fornecedor: "));
    fornecedor->incricao_estadual = lerInt("Digite a inscrição estadual do fornecedor: ");
    strcpy(fornecedor->cnpj, lerString("Digite o CNPJ do fornecedor: "));
    strcpy(fornecedor->endereco, lerString("Digite o endereço completo do fornecedor: "));
    strcpy(fornecedor->telefone, lerString("Digite o telefone do fornecedor: "));
    strcpy(fornecedor->email, lerString("Digite o email do fornecedor: "));

    if (createFornecedor(fornecedores, fornecedor) != FALSE)
        printf("Fornecedor cadastrado com sucesso!\n");
    else
        printf("Erro no cadastro do fornecedor!\n");

    free(fornecedor); // Libera a memória alocada
}

void mostrarFornecedor(Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) {
        printf("Nenhum fornecedor cadastrado até o momento\n");
        return;
    }

    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        printf("Fornecedor: %s Código: %d\n\n", fornecedores[i].nome_fantasia, fornecedores[i].codigo);
    }

    int codigo = lerInt("Digite o código do fornecedor que você deseja ver: ");
    int posicao = showFornecedor(fornecedores, codigo);

    if (posicao != FALSE) {
        printf("Código: %d\n"
               "Nome Fantasia: %s\n"
               "Razão Social: %s\n"
               "Inscrição Estadual: %d\n"
               "CNPJ: %s\n"
               "Endereço: %s\n"
               "Telefone: %s\n"
               "E-mail: %s\n",
               fornecedores[posicao].codigo,
               fornecedores[posicao].nome_fantasia,
               fornecedores[posicao].razao_social,
               fornecedores[posicao].incricao_estadual,
               fornecedores[posicao].cnpj,
               fornecedores[posicao].endereco,
               fornecedores[posicao].telefone,
               fornecedores[posicao].email);
    } else {
        printf("Fornecedor não encontrado, por favor digite um código existente.\n");
    }
}
void editarFornecedor(Fornecedor *fornecedores) {
    Fornecedor *fornecedor = malloc(sizeof(Fornecedor));
    fornecedor->codigo = lerInt("Digite o código do fornecedor que você deseja editar: ");
    strcpy(fornecedor->nome_fantasia, lerString("Digite o nome fantasia do fornecedor: "));
    strcpy(fornecedor->razao_social, lerString("Digite a razão social do fornecedor: "));
    fornecedor->incricao_estadual = lerInt("Digite a inscrição estadual do fornecedor: ");
    strcpy(fornecedor->cnpj, lerString("Digite o CNPJ do fornecedor: "));
    strcpy(fornecedor->endereco, lerString("Digite o endereço completo do fornecedor: "));
    strcpy(fornecedor->telefone, lerString("Digite o telefone do fornecedor: "));
    strcpy(fornecedor->email, lerString("Digite o email do fornecedor: "));

    if (updateFornecedor(fornecedores, fornecedor) == FALSE)
        printf("Erro na edição dos dados do fornecedor\n");
    else
        printf("Fornecedor editado com sucesso!\n");

    free(fornecedor); // Libera a memória alocada
}

void apagarFornecedor(Fornecedor *fornecedores) {
    int codigo = lerInt("Digite o código do fornecedor que você deseja apagar: ");
    if (deleteFornecedor(fornecedores, codigo) == TRUE)
        printf("Fornecedor apagado com sucesso\n");
    else
        printf("Fornecedor não existe\n");
}

