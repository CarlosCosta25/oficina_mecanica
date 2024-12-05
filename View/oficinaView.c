#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/oficina.h"
#include "../bibliotecas/utils.h"

// Função que exibe o menu de opções da oficina e realiza as ações com base na escolha do usuário.
void menuOficina(Oficina **oficina) {
    if (getTipoArquivo() != MEM) {  // Verifica se os dados não estão em memória e tenta ler do arquivo.
        *oficina = readOficina();
    }

    int opcao = -1;  // Inicializa a variável de opção com um valor inválido.
    while (opcao != 0) {  // Loop até o usuário escolher a opção de sair.
        printf("==== MENU OFICINA ====\n");
        // Exibe o menu e recebe a escolha do usuário.
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar nova oficina\n"
            "2- Ver oficina\n"
            "3- Editar oficina\n"
            "4- Excluir oficina\n"
            "0- Sair\n");

        // Realiza a ação baseada na escolha do usuário.
        switch (opcao) {
            case 1:
                novaOficina(*oficina);  // Cadastra uma nova oficina
                if (getTipoArquivo() != MEM) *oficina = readOficina();  // Atualiza os dados após cadastro
                break;
            case 2:
                mostrarOficina(*oficina);  // Exibe os dados da oficina
                break;
            case 3:
                editarOficina(*oficina);  // Edita os dados da oficina
                break;
            case 4:
                apagarOficina(oficina);  // Exclui a oficina
                break;
            case 0:
                printf("Saindo...\n");  // Mensagem de saída
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");  // Caso o usuário escolha uma opção inválida
        }
    }
}

// Função para cadastrar uma nova oficina.
void novaOficina(Oficina *oficina) {
    Oficina *novaOficina = malloc(sizeof(Oficina));  // Aloca memória para a nova oficina
    if (novaOficina == NULL) {  // Verifica se a alocação falhou
        printf("Erro ao alocar memória para a nova oficina!\n");
        return;
    }

    // Solicita os dados da nova oficina
    strcpy(novaOficina->nome, lerString("Digite o nome da oficina: "));
    strcpy(novaOficina->cpf_cnpj, lerString("Digite o CPF ou CNPJ da oficina: "));
    strcpy(novaOficina->endereco, lerString("Digite o endereço completo da oficina: "));
    strcpy(novaOficina->telefone, lerString("Digite o telefone da oficina: "));
    strcpy(novaOficina->email, lerString("Digite o email da oficina: "));
    novaOficina->porcentagem_lucro = lerFloat("Digite a porcentagem de lucro da oficina: ");

    // Tenta cadastrar a nova oficina e exibe uma mensagem de sucesso ou erro
    if (createOficina(&oficina, novaOficina) != FALSE) {
        printf("Oficina cadastrada com sucesso!\n");
    } else {
        printf("Erro no cadastro da oficina!\n");
    }

    free(novaOficina);  // Libera a memória alocada após o cadastro
}

// Função para exibir os dados da oficina cadastrada.
void mostrarOficina(Oficina *oficina) {
    if (hasOficina() != FALSE) {  // Verifica se há uma oficina cadastrada
        // Exibe os dados da oficina
        printf("Nome: %s\n"
               "CPF/CNPJ: %s\n"
               "Endereço: %s\n"
               "Telefone: %s\n"
               "Email: %s\n"
               "Porcentagem de Lucro: %.2f\n",
               oficina->nome,
               oficina->cpf_cnpj,
               oficina->endereco,
               oficina->telefone,
               oficina->email,
               oficina->porcentagem_lucro
        );
    } else {
        printf("Dados da oficina não cadastrados\n");  // Caso não haja oficina cadastrada
    }
}

// Função para editar os dados de uma oficina existente.
void editarOficina(Oficina *oficina) {
    if (oficina == NULL) {  // Verifica se a oficina não foi cadastrada
        printf("Nenhuma oficina cadastrada\n");
        return;
    }

    Oficina *novaOficina = malloc(sizeof(Oficina));  // Aloca memória para armazenar os dados modificados
    if (novaOficina == NULL) {  // Verifica se houve erro na alocação de memória
        printf("Erro ao alocar memória para a edição da oficina\n");
        return;
    }

    // Solicita e exibe os dados da oficina, perguntando ao usuário se deseja editar cada campo.
    printf("O nome da Oficina é: %s\n", oficina->nome);
    if (lerInt("Deseja editar? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(novaOficina->nome, lerString("Digite o novo nome da oficina: "));
    } else {
        strcpy(novaOficina->nome, oficina->nome);
    }

    printf("O CPF/CNPJ atual da Oficina é: %s\n", oficina->cpf_cnpj);
    if (lerInt("Deseja editar o CPF/CNPJ da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(novaOficina->cpf_cnpj, lerString("Digite o novo CPF/CNPJ da oficina: "));
    } else {
        strcpy(novaOficina->cpf_cnpj, oficina->cpf_cnpj);
    }

    // Repete o mesmo processo para os outros campos (endereço, telefone, email e porcentagem de lucro)
    printf("O endereço atual da Oficina é: %s\n", oficina->endereco);
    if (lerInt("Deseja editar o endereço da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(novaOficina->endereco, lerString("Digite o novo endereço da oficina: "));
    } else {
        strcpy(novaOficina->endereco, oficina->endereco);
    }

    printf("O telefone atual da Oficina é: %s\n", oficina->telefone);
    if (lerInt("Deseja editar o telefone da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(novaOficina->telefone, lerString("Digite o novo telefone da oficina: "));
    } else {
        strcpy(novaOficina->telefone, oficina->telefone);
    }

    printf("O email atual da Oficina é: %s\n", oficina->email);
    if (lerInt("Deseja editar o email da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(novaOficina->email, lerString("Digite o novo email da oficina: "));
    } else {
        strcpy(novaOficina->email, oficina->email);
    }

    printf("A porcentagem atual da Oficina é: %.2f\n", oficina->porcentagem_lucro);
    if (lerInt("Deseja editar a porcentagem de lucro da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        novaOficina->porcentagem_lucro = lerFloat("Digite a nova porcentagem de lucro da oficina: ");
    } else {
        novaOficina->porcentagem_lucro = oficina->porcentagem_lucro;
    }

    // Tenta atualizar a oficina com os novos dados e exibe uma mensagem de sucesso ou erro.
    if (updateOficina(&oficina, novaOficina)) {
        printf("Erro na edição dos dados da oficina!\n");
    } else {
        printf("Dados da oficina editados com sucesso!\n");
        *oficina = *novaOficina;  // Atualiza os dados da oficina original
    }

    free(novaOficina);  // Libera a memória da nova oficina após a edição
}

// Função para excluir a oficina do sistema.
void apagarOficina(Oficina **oficina) {
    *oficina = deleteOficina();  // Exclui a oficina e atualiza o ponteiro para NULL
    if (*oficina != NULL) {
        printf("Erro ao deletar dados da oficina!\n");
    } else {
        printf("Dados apagados com sucesso!\n");
    }
}
