#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/cliente.h"

// Função que gerencia o menu principal para operações com clientes
void menuCliente(Cliente **clientes) {
    // Se o tipo de armazenamento não for memória, lê os clientes do armazenamento
    if (getTipoArquivo() != 3) {
        *clientes = readClientes();
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n==== MENU CLIENTE ====\n");
        printf("1 - Cadastrar novo cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Editar cliente\n");
        printf("4 - Excluir cliente\n");
        printf("0 - Sair\n");

        opcao = lerInt("Escolha uma opção: ");

        switch (opcao) {
            case 1: // Cadastrar novo cliente
                novoCliente(clientes);
                if (getTipoArquivo() != MEM) *clientes = getClientes();
                break;
            case 2: // Listar clientes
                mostrarCliente(*clientes);
                break;
            case 3: // Editar cliente
                editarCLiente(*clientes);
                break;
            case 4: // Excluir cliente
                apagarCliente(*clientes);
                break;
            case 0: // Sair
                printf("Saindo do menu cliente...\n");
                break;
            default: // Opção inválida
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

// Função para cadastrar um novo cliente
void novoCliente(Cliente **clientes) {
    Cliente *cliente = malloc(sizeof(Cliente)); // Aloca memória para um novo cliente

    // Coleta os dados do cliente do usuário
    strcpy(cliente->nome, lerString("Digite o nome do cliente: "));
    strcpy(cliente->cpf_cnpj, lerString("Digite o CPF/CNPJ do cliente: "));
    strcpy(cliente->endereco, lerString("Digite o endereço completo do cliente: "));
    strcpy(cliente->telefone, lerString("Digite o telefone do cliente: "));
    strcpy(cliente->email, lerString("Digite o email do cliente: "));
    cliente->ativo = 1; // Define o cliente como ativo

    // Salva o cliente e verifica sucesso
    if (createCliente(clientes, cliente) != FALSE) {
        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do cliente!\n");
    }

    printf("Total de clientes cadastrados: %d\n", getTamanhoClientes());

    free(cliente); // Libera a memória alocada
}

// Função para listar e exibir detalhes de um cliente
void mostrarCliente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado até o momento.\n");
        return;
    }

    printf("\n=== LISTA DE CLIENTES ===\n");
    mostrarTodosClientes(clientes);

    int codigo = lerInt("Digite o código do cliente que você deseja ver: ");
    int posicao = showCliente(clientes, codigo);

    if (posicao != FALSE) {
        // Exibe os detalhes do cliente encontrado
        printf("\nDetalhes do Cliente:\n"
               "Código: %d\n"
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
               clientes[posicao].email);
    } else {
        printf("Cliente não encontrado!\n");
    }
}

// Função para editar os dados de um cliente
void editarCLiente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente *cliente = malloc(sizeof(Cliente)); // Aloca memória para a edição
    if (cliente == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("\n=== LISTA DE CLIENTES ===\n");
    mostrarTodosClientes(clientes);

    cliente->codigo = lerInt("Digite o código do cliente que você deseja editar: ");
    int posicao = showCliente(clientes, cliente->codigo); // Busca o cliente pelo código

    if (posicao == FALSE) {
        printf("Cliente não encontrado.\n");
        free(cliente);
        return;
    }

    // Edição de cada campo com confirmação
    editarCampo("nome", clientes[posicao].nome, cliente->nome);
    editarCampo("CPF/CNPJ", clientes[posicao].cpf_cnpj, cliente->cpf_cnpj);
    editarCampo("endereço", clientes[posicao].endereco, cliente->endereco);
    editarCampo("telefone", clientes[posicao].telefone, cliente->telefone);
    editarCampo("email", clientes[posicao].email, cliente->email);

    if (updateCliente(clientes, cliente) == FALSE) {
        printf("Erro na edição dos dados do cliente.\n");
    } else {
        printf("Cliente editado com sucesso!\n");
    }

    free(cliente); // Libera memória alocada
}

// Função auxiliar para editar um campo
void editarCampo(const char *campo, const char *valorAtual, char *novoValor) {
    printf("O %s atual é: %s\n", campo, valorAtual);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(novoValor, lerString("Digite o novo valor: "));
    } else {
        strcpy(novoValor, valorAtual);
    }
}

// Função para excluir um cliente
void apagarCliente(Cliente *clientes) {
    if (getTamanhoClientes() == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\n=== LISTA DE CLIENTES ===\n");
    mostrarTodosClientes(clientes);

    int codigo = lerInt("Digite o código do cliente que você deseja apagar: ");
    if (deleteCliente(clientes, codigo) == TRUE) {
        printf("Cliente apagado com sucesso.\n");
    } else {
        printf("Cliente não encontrado.\n");
    }
}

// Função para exibir todos os clientes
void mostrarTodosClientes(Cliente *clientes) {
    printf("\nLista de Clientes Ativos:\n");
    for (int i = 0; i < getTamanhoClientes(); i++) {
        if (clientes[i].ativo != FALSE) {
            printf("Cliente: %s | Código: %d\n", clientes[i].nome, clientes[i].codigo);
        }
    }
}
