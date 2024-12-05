#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/veiculo.h"

// Função principal do menu de veículos
void menuVeiculo() {
    // Carregar dados de veículos, dependendo do tipo de arquivo
    Veiculo *veiculos = migraDadosVeiculo();
    if (getTipoArquivo() != MEM && veiculos == NULL) {
        veiculos = getVeiculos();
    }

    int opcao = -1;
    printf("==== MENU VEICULO ====\n");

    // Loop principal do menu
    while (opcao != 0) {
        // Apresenta as opções do menu e lê a escolha do usuário
        opcao = lerInt("Digite a opção desejada:\n"
                       "1- Cadastrar novo veículo\n"
                       "2- Ver veículos\n"
                       "3- Editar veículo\n"
                       "4- Excluir veículo\n"
                       "0- Sair\n");

        // Executa a ação conforme a opção escolhida
        switch (opcao) {
            case 1:
                novoVeiculo(&veiculos); // Função para cadastrar um novo veículo
                if (getTipoArquivo() != MEM) veiculos = getVeiculos(); // Atualiza os veículos, se não estiver em memória
                break;
            case 2:
                mostrarVeiculo(veiculos); // Função para exibir veículos
                break;
            case 3:
                editarVeiculo(veiculos); // Função para editar um veículo
                break;
            case 4:
                apagarVeiculo(veiculos); // Função para apagar um veículo
                break;
        }
    }

    // Libera a memória alocada para os veículos e define como NULL
    free(veiculos);
    veiculos = NULL;
}

// Função para cadastrar um novo veículo
void novoVeiculo(Veiculo **veiculos) {
    Veiculo *veiculo = malloc(sizeof(Veiculo));

    // Solicita informações sobre o veículo
    strcpy(veiculo->placa, lerString("Digite a placa do veículo: "));
    strcpy(veiculo->modelo, lerString("Digite o modelo do veículo: "));
    strcpy(veiculo->marca, lerString("Digite a marca do veículo: "));
    veiculo->anofabricacao = atoi(lerString("Digite o ano de fabricação do veículo: "));
    strcpy(veiculo->chassi, lerString("Digite o chassi do veículo: "));
    veiculo->ativo = 1; // Define o veículo como ativo

    // Tenta cadastrar o veículo
    if (createVeiculo(veiculos, veiculo) != FALSE) {
        printf("Veículo cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do veículo!\n");
    }

    printf("Tamanho do veículo: %d\n", getTamanhoVeiculos()); // Exibe a quantidade de veículos cadastrados

    free(veiculo); // Libera a memória alocada para o veículo após o cadastro
}

// Função para mostrar informações de veículos
void mostrarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado até o momento\n");
        return;
    }

    printf("\tVEÍCULOS:\n");
    mostrarTodosVeiculos(veiculos);

    // Solicita o código do veículo que o usuário deseja ver
    int codigo = lerInt("Digite o código do veículo que você deseja ver: ");
    int posicao = showVeiculo(veiculos, codigo);

    if (posicao != FALSE) {
        // Exibe as informações do veículo
        printf("Código: %d\n"
               "Placa: %s\n"
               "Modelo: %s\n"
               "Marca: %s\n"
               "Ano de Fabricação: %d\n"
               "Chassi: %s\n",
               veiculos[posicao].codigo,
               veiculos[posicao].placa,
               veiculos[posicao].modelo,
               veiculos[posicao].marca,
               veiculos[posicao].anofabricacao,
               veiculos[posicao].chassi
        );
    }
}

// Função para editar as informações de um veículo
void editarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado\n");
        return;
    }

    Veiculo *veiculo = malloc(sizeof(Veiculo));
    if (veiculo == NULL) {
        printf("Erro ao alocar memória para a edição do veículo\n");
        return;
    }

    printf("\tVEÍCULOS:\n");
    mostrarTodosVeiculos(veiculos);

    // Solicita o código do veículo que será editado
    veiculo->codigo = lerInt("Digite o código do veículo que você deseja editar: ");

    // Procura o veículo pelo código
    int posicao = showVeiculo(veiculos, veiculo->codigo);

    if (posicao == FALSE) {
        printf("Veículo não encontrado.\n");
        free(veiculo);
        return;
    }

    // Permite editar o campo `placa`
    printf("A placa do veículo é: %s\n", veiculos[posicao].placa);
    int opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(veiculo->placa, lerString("Digite a nova placa do veículo: "));
    } else {
        strcpy(veiculo->placa, veiculos[posicao].placa);
    }

    // Permite editar o campo `modelo`
    printf("O modelo do veículo é: %s\n", veiculos[posicao].modelo);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(veiculo->modelo, lerString("Digite o novo modelo do veículo: "));
    } else {
        strcpy(veiculo->modelo, veiculos[posicao].modelo);
    }

    // Permite editar o campo `marca`
    printf("A marca do veículo é: %s\n", veiculos[posicao].marca);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(veiculo->marca, lerString("Digite a nova marca do veículo: "));
    } else {
        strcpy(veiculo->marca, veiculos[posicao].marca);
    }

    // Permite editar o campo `anofabricacao`
    printf("O ano de fabricação do veículo é: %d\n", veiculos[posicao].anofabricacao);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        veiculo->anofabricacao = lerInt("Digite o novo ano de fabricação do veículo: ");
    } else {
        veiculo->anofabricacao = veiculos[posicao].anofabricacao;
    }

    // Permite editar o campo `chassi`
    printf("O chassi do veículo é: %s\n", veiculos[posicao].chassi);
    opcao = lerInt("Deseja editar? (1 - Sim, 0 - Não): ");
    if (opcao == TRUE) {
        strcpy(veiculo->chassi, lerString("Digite o novo chassi do veículo: "));
    } else {
        strcpy(veiculo->chassi, veiculos[posicao].chassi);
    }

    // Atualiza o veículo com as novas informações
    if (updateVeiculo(veiculos, veiculo) == FALSE) {
        printf("Erro na edição dos dados do veículo\n");
    } else {
        printf("Veículo editado com sucesso!\n");
    }

    free(veiculo); // Libera a memória alocada para o veículo
}

// Função para apagar um veículo
void apagarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado\n");
        return;
    }

    printf("\tVEÍCULOS:\n");
    mostrarTodosVeiculos(veiculos);
    int codigo = lerInt("Digite o código do veículo que você deseja apagar: ");
    if (deleteVeiculo(veiculos, codigo) == TRUE) {
        printf("Veículo apagado com sucesso\n");
    } else {
        printf("Veículo não existe\n");
    }
}

// Função para listar todos os veículos
void mostrarTodosVeiculos(Veiculo *veiculo) {
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (veiculo[i].ativo != FALSE) {
            printf("Placa: %s Codigo: %d\n", veiculo[i].placa, veiculo[i].codigo);
        }
    }
}
