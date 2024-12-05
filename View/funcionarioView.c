#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/funcionario.h"

// Função que exibe o menu de opções para o usuário e realiza as ações com base na escolha
void menuFuncionario() {
    Funcionario *funcionarios = migraDadosFuncionario();  // Tenta migrar os dados do arquivo para a memória
    if (getTipoArquivo() != MEM && funcionarios == NULL) {
        funcionarios = getFuncionarios();  // Se a migração falhar, carrega os dados de memória
    }

    int opcao = -1;
    // Exibe o menu de opções para o usuário
    printf("==== MENU FUNCIONÁRIO ====\n");
    while (opcao != 0) {
        // Solicita a escolha do usuário
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar novo funcionário\n"
            "2- Ver funcionários\n"
            "3- Editar funcionário\n"
            "4- Excluir funcionário\n"
            "0- Sair\n");

        switch (opcao) {
            case 1:
                novoFuncionario(&funcionarios);  // Cadastra um novo funcionário
                if (getTipoArquivo() != MEM) funcionarios = getFuncionarios();  // Atualiza a lista de funcionários
                break;
            case 2:
                mostrarFuncionario(funcionarios);  // Exibe os funcionários cadastrados
                break;
            case 3:
                editarFuncionario(funcionarios);  // Edita os dados de um funcionário
                break;
            case 4:
                apagarFuncionario(funcionarios);  // Exclui um funcionário
                break;
            case 0:
                printf("Saindo...\n");  // Mensagem de saída
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");  // Mensagem de erro para opções inválidas
        }
    }
    free(funcionarios);  // Libera a memória alocada para os funcionários
    funcionarios = NULL;
}

// Função para cadastrar um novo funcionário
void novoFuncionario(Funcionario **funcionarios) {
    Funcionario *funcionario = malloc(sizeof(Funcionario));  // Aloca memória para um novo funcionário
    // Solicita os dados do novo funcionário
    strcpy(funcionario->nome, lerString("Digite o nome completo do funcionário: "));
    strcpy(funcionario->cpf, lerString("Digite o cpf do funcionário: "));
    strcpy(funcionario->endereco, lerString("Digite o endereço do funcionário: "));
    strcpy(funcionario->telefone, lerString("Digite o telefone do funcionário: "));
    strcpy(funcionario->cargo, lerString("Digite o cargo do funcionário: "));
    funcionario->salario = atoi(lerString("Digite o salário do funcionário: "));
    funcionario->ativo = 1;  // Define o funcionário como ativo

    // Tenta cadastrar o novo funcionário
    if (createFuncionario(funcionarios, funcionario) != FALSE) {
        printf("Funcionário cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do funcionário!\n");
    }

    printf("Tamanho do funcionário: %d\n", getTamanhoFuncionarios());  // Exibe a quantidade de funcionários cadastrados

    free(funcionario);  // Libera a memória alocada para o funcionário após o cadastro
}

// Função para exibir os funcionários cadastrados
void mostrarFuncionario(Funcionario *funcionarios) {
    if (getTamanhoFuncionarios() == 0) {  // Verifica se há funcionários cadastrados
        printf("Nenhum funcionário cadastrado até o momento.\n");
        return;
    }

    printf("\tFUNCIONÁRIOS:\n");
    mostrarTodosFuncionarios(funcionarios);  // Exibe todos os funcionários cadastrados

    int codigo = lerInt("Digite o código do funcionário que você deseja ver: ");
    int posicao = showFuncionario(funcionarios, codigo);  // Busca o funcionário pelo código

    if (posicao != FALSE) {
        // Exibe os detalhes do funcionário
        printf("Código: %d\n"
               "Nome Completo: %s\n"
               "CPF: %s\n"
               "Endereço: %s\n"
               "Telefone: %s\n"
               "Cargo: %s\n"
               "Salário: %.2f\n",
               funcionarios[posicao].codigo,
               funcionarios[posicao].nome,
               funcionarios[posicao].cpf,
               funcionarios[posicao].endereco,
               funcionarios[posicao].telefone,
               funcionarios[posicao].cargo,
               funcionarios[posicao].salario
        );
    }
}

// Função para editar os dados de um funcionário
void editarFuncionario(Funcionario *funcionarios) {
    if (getTamanhoFuncionarios() == 0) {  // Verifica se há funcionários cadastrados
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    Funcionario *funcionario = malloc(sizeof(Funcionario));  // Aloca memória para armazenar as modificações
    if (funcionario == NULL) {
        printf("Erro ao alocar memória para a edição do funcionário.\n");
        return;
    }

    printf("\tFUNCIONÁRIOS:\n");
    mostrarTodosFuncionarios(funcionarios);  // Exibe a lista de funcionários

    funcionario->codigo = lerInt("Digite o código do funcionário que você deseja editar: ");
    int posicao = showFuncionario(funcionarios, funcionario->codigo);  // Encontra o funcionário pela posição

    if (posicao == FALSE) {  // Se o funcionário não for encontrado, exibe mensagem de erro
        printf("Funcionário não encontrado.\n");
        free(funcionario);
        return;
    }

    // Exibe os dados atuais do funcionário e pergunta se o usuário deseja editar cada campo
    printf("O nome do funcionário é: %s\n", funcionarios[posicao].nome);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(funcionario->nome, lerString("Digite o novo nome do funcionário: "));
    } else {
        strcpy(funcionario->nome, funcionarios[posicao].nome);
    }

    printf("O CPF do funcionário é: %s\n", funcionarios[posicao].cpf);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(funcionario->cpf, lerString("Digite o novo CPF do funcionário: "));
    } else {
        strcpy(funcionario->cpf, funcionarios[posicao].cpf);
    }

    // Repete o mesmo processo para os outros campos do funcionário (endereço, telefone, cargo e salário)
    printf("O endereço do funcionário é: %s\n", funcionarios[posicao].endereco);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(funcionario->endereco, lerString("Digite o novo endereço do funcionário: "));
    } else {
        strcpy(funcionario->endereco, funcionarios[posicao].endereco);
    }

    printf("O telefone do funcionário é: %s\n", funcionarios[posicao].telefone);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(funcionario->telefone, lerString("Digite o novo telefone do funcionário: "));
    } else {
        strcpy(funcionario->telefone, funcionarios[posicao].telefone);
    }

    printf("O cargo do funcionário é: %s\n", funcionarios[posicao].cargo);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(funcionario->cargo, lerString("Digite o novo cargo do funcionário: "));
    } else {
        strcpy(funcionario->cargo, funcionarios[posicao].cargo);
    }

    printf("O salário do funcionário é: %.2f\n", funcionarios[posicao].salario);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        funcionario->salario = lerFloat("Digite o novo salário do funcionário: ");
    } else {
        funcionario->salario = funcionarios[posicao].salario;
    }

    // Atualiza os dados do funcionário no sistema
    if (updateFuncionario(funcionarios, funcionario) == FALSE) {
        printf("Erro na edição dos dados do funcionário.\n");
    } else {
        printf("Funcionário editado com sucesso!\n");
    }

    free(funcionario);  // Libera a memória do funcionário após a edição
}

// Função para apagar um funcionário do sistema
void apagarFuncionario(Funcionario *funcionarios) {
    if (getTamanhoFuncionarios() == 0) {  // Verifica se há funcionários cadastrados
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    printf("\tFUNCIONÁRIOS:\n");
    mostrarTodosFuncionarios(funcionarios);  // Exibe a lista de funcionários

    int codigo = lerInt("Digite o código do funcionário que você deseja apagar: ");
    if (deleteFuncionario(funcionarios, codigo) == TRUE) {  // Exclui o funcionário
        printf("Funcionário apagado com sucesso.\n");
    } else {
        printf("Funcionário não encontrado.\n");
    }
}

// Função para exibir todos os funcionários cadastrados
void mostrarTodosFuncionarios(Funcionario *funcionarios) {
    for (int i = 0; i < getTamanhoFuncionarios(); i++) {
        if (funcionarios[i].ativo != FALSE)  // Exibe apenas funcionários ativos
            printf("Funcionário: %s | Código: %d\n", funcionarios[i].nome, funcionarios[i].codigo);
    }
}
