#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/cliente.h"

void menuCliente(Cliente **clientes) {
    if (getTipoArquivo() != 3) {
        *clientes = readClientes();
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("==== MENU CLIENTE ====\n");
        opcao = lerInt("Digite a opcao deseja:\n"
            "1- Cadastrar novo cliente\n"
            "2- Ver clientes\n"
            "3- Editar cliente\n"
            "4- Excluir cliente\n"
            "0- Sair\n");
        switch (opcao) {
            case 1:
                novoCliente(clientes);
                if (getTipoArquivo() != MEM) *clientes = getClientes();
                opcao = -1;
                break;

            case 2:
                mostrarCliente(*clientes);
                opcao = -1;
                break;
            case 3:
                editarCLiente(*clientes);
                opcao = -1;
                break;
            case 4:
                apagarCliente(*clientes);
                opcao = -1;
                break;
        }
    }
    //free(clientes);
    //clientes = NULL;
}

void novoCliente(Cliente **clientes) {
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
    printf("Tamnho do cliente %d\n", getTamanhoClientes());

    free(cliente); // Libera a memória do cliente após o cadastro
}


void mostrarCliente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado até o momento\n");
        return;
    }
    printf("\tCLIENTES:\n");
    mostrarTodosClientes(clientes);

    int codigo = lerInt("Digite o código do cliente que você deseja ver: ");
    int posicao = showCliente(clientes, codigo);

    if (posicao != FALSE) {
        printf("Código: %d\n"
               "Nome: %s\n"
               "Endereço: %s\n"
               "CPF/CNPJ: %s\n"
               "Telefone: %s\n"
               "E-mail: %s\n",
               clientes[posicao].codigo,
               clientes[posicao].nome,
               clientes[posicao].endereco,
               clientes[posicao].cpf_cnpj,
               clientes[posicao].telefone,
               clientes[posicao].email
        ); // Exibe se o cliente está ativo
    } else {
        printf("Cliente não encontrado!\n");
    }
}

void editarCLiente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado\n");
        return;
    }

    Cliente *cliente = malloc(sizeof(Cliente));
    printf("\tCLIENTES:\n");
    mostrarTodosClientes(clientes);
    cliente->codigo = lerInt("Digite o código do cliente que você deseja editar: ");

    // Procurar o cliente
    int posicao = showCliente(clientes, cliente->codigo);

    if (posicao == FALSE) {
        printf("Cliente não encontrado.\n");
        free(cliente);
        return;
    }

    strcpy(cliente->nome, lerString("Digite o novo nome do cliente: "));
    strcpy(cliente->cpf_cnpj, lerString("Digite o CPF/CNPJ do cliente: "));
    strcpy(cliente->endereco, lerString("Digite o endereço completo do cliente: "));
    strcpy(cliente->telefone, lerString("Digite o telefone do cliente: "));
    strcpy(cliente->email, lerString("Digite o email do cliente: "));

    // O campo ativo permanece inalterado e não é necessário modificar
    // Se quiser, você pode adicionar código para editar o estado civil e data, caso sejam necessários.

    if (updateCliente(clientes, cliente) == FALSE) {
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
    printf("\tCLIENTES:\n");
    mostrarTodosClientes(clientes);
    int codigo = lerInt("Digite o código do cliente que você deseja apagar: ");
    if (deleteCliente(clientes, codigo) == TRUE) {
        printf("Cliente apagado com sucesso\n");
    } else {
        printf("Cliente não existe\n");
    }
}

void mostrarTodosClientes(Cliente *clientes) {
    for (int i = 0; i < getTamanhoClientes(); i++) {
        if (clientes[i].ativo != FALSE)
            printf("Cliente: %s Codigo: %d\n", clientes[i].nome, clientes[i].codigo);
    }
}
