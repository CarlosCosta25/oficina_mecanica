#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/cliente.h"

void menuCliente() {
    Cliente *clientes = migraDadosCliente();
    if (getTipoArquivo() != 3) {
        clientes = readClientes();
    }
    int opcao = -1;
    printf("==== MENU CLIENTE ====\n");
    while (opcao != 0) {
        opcao = lerInt("Digite a opcao deseja:\n"
            "1- Cadastrar novo cliente\n"
            "2- Ver clientes\n"
            "3- Editar cliente\n"
            "4- Excluir cliente\n"
            "0- Sair\n");
        switch (opcao) {
            case 1:
                novoCliente(clientes);
                clientes = getClientes();
                opcao = -1;
                break;

            case 2:
                mostrarCliente(clientes);
                opcao = -1;
                break;
            case 3:
                editarCLiente(clientes);
                opcao = -1;
                break;
            case 4:
                apagarCliente(clientes);
                opcao = -1;
                break;
        }
    }
    free(clientes);
    clientes = NULL;
}

void novoCliente(Cliente *clientes) {
    Cliente *cliente = malloc(sizeof(Cliente));
    strcpy(cliente->nome, lerString("Digite o nome do cliente: "));
    strcpy(cliente->cpf_cnpj, lerString("Digite o CPF/CNPJ do cliente: "));
    strcpy(cliente->endereco, lerString("Digite o endereço completo do cliente: "));
    strcpy(cliente->telefone, lerString("Digite o telefone do cliente: "));
    strcpy(cliente->email, lerString("Digite o email do cliente: "));
    cliente->ativo = 1; // Define o cliente como ativo

    if (createCliente(clientes, cliente) != FALSE) {
        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do cliente!\n");
    }

    free(cliente); // Libera a memória do cliente após o cadastro
}


void mostrarCliente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado até o momento\n");
        return;
    }

    for (int i = 0; i < getTamanhoClientes(); i++) {
        printf("Cliente: %s Código: %d\n\n", clientes[i].nome, clientes[i].codigo);
    }

    int codigo = lerInt("Digite o código do cliente que você deseja ver: ");
    int posicao = showCliente(clientes, codigo);

    if (posicao != FALSE) {
        printf("Código: %d\n"
               "Nome: %s\n"
               "Endereço: %s\n"
               "CPF/CNPJ: %s\n"
               "Telefone: %s\n"
               "E-mail: %s\n"
               "Ativo: %s\n",
               clientes[posicao].codigo,
               clientes[posicao].nome,
               clientes[posicao].endereco,
               clientes[posicao].cpf_cnpj,
               clientes[posicao].telefone,
               clientes[posicao].email
        ); // Exibe se o cliente está ativo
    }
}

void editarCLiente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado\n");
        return;
    }

    Cliente *cliente = malloc(sizeof(Cliente));
    cliente->codigo = lerInt("Digite o código do cliente que você deseja editar: ");

    // Procurar o cliente
    int posicao = showCliente(clientes, cliente->codigo);

    if (posicao == FALSE) {
        printf("Cliente não encontrado.\n");
        free(cliente);
        return;
    }

    strcpy(clientes[posicao].nome, lerString("Digite o novo nome do cliente: "));
    strcpy(clientes[posicao].cpf_cnpj, lerString("Digite o CPF/CNPJ do cliente: "));
    strcpy(clientes[posicao].endereco, lerString("Digite o endereço completo do cliente: "));
    strcpy(clientes[posicao].telefone, lerString("Digite o telefone do cliente: "));
    strcpy(clientes[posicao].email, lerString("Digite o email do cliente: "));

    // O campo ativo permanece inalterado e não é necessário modificar
    // Se quiser, você pode adicionar código para editar o estado civil e data, caso sejam necessários.

    if (updateCliente(clientes, &clientes[posicao]) == FALSE) {
        printf("Erro na edição dos dados do cliente\n");
    } else {
        printf("Cliente editado com sucesso!\n");
    }

    free(cliente); // Libera a memória alocada
}

void apagarCliente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado\n");
        return;
    }

    int codigo = lerInt("Digite o código do cliente que você deseja apagar: ");
    if (deleteCliente(clientes, codigo) == TRUE) {
        printf("Cliente apagado com sucesso\n");
    } else {
        printf("Cliente não existe\n");
    }
}

