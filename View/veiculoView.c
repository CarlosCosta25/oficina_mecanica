#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/veiculo.h"

void menuVeiculo() {
    Veiculo *veiculos = migraDadosVeiculo();
    if (getTipoArquivo() != MEM && veiculos == NULL) {
        veiculos = getVeiculos();
    }

    int opcao = -1;
    printf("==== MENU VEICULO ====\n");
    while (opcao != 0) {
        opcao = lerInt("Digite a opção desejada:\n"
                       "1- Cadastrar novo veículo\n"
                       "2- Ver veículos\n"
                       "3- Editar veículo\n"
                       "4- Excluir veículo\n"
                       "0- Sair\n");
        switch (opcao) {
            case 1:
                novoVeiculo(&veiculos);
            if (getTipoArquivo() != MEM) veiculos = getVeiculos();
            break;
            case 2:
                mostrarVeiculo(veiculos);
            break;
            case 3:
                editarVeiculo(veiculos);
            break;
            case 4:
                apagarVeiculo(veiculos);
            break;
        }
    }
    free(veiculos);
    veiculos = NULL;
}


void novoVeiculo(Veiculo **veiculos) {
    Veiculo *veiculo = malloc(sizeof(Veiculo));
    strcpy(veiculo->placa, lerString("Digite a placa do veículo: "));
    strcpy(veiculo->modelo, lerString("Digite o modelo do veículo: "));
    strcpy(veiculo->marca, lerString("Digite a marca do veículo: "));
    veiculo->anofabricacao = atoi(lerString("Digite o ano de fabricação do veículo: "));
    strcpy(veiculo->chassi, lerString("Digite o chassi do veículo: "));
    veiculo->ativo = 1; // Define o veiculo como ativo

    if (createVeiculo(veiculos, veiculo) != FALSE) {
        printf("Veículo cadastrado com sucesso!\n");
    } else {
        printf("Erro no cadastro do veículo!\n");
    }
    printf("Tamnho do veículo %d\n",getTamanhoVeiculos());

    free(veiculo); // Libera a memória do veículo após o cadastro
}

void mostrarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado até o momento\n");
        return;
    }

    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        printf("Veículo: %s Código: %d\n\n", veiculos[i].placa, veiculos[i].codigo);
    }

    int codigo = lerInt("Digite o código do veículo que você deseja ver: ");
    int posicao = showVeiculo(veiculos, codigo);

    if (posicao != FALSE) {
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
        ); // Exibe se o veiculo está ativo
    }
}

void editarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado\n");
        return;
    }

    Veiculo *veiculo = malloc(sizeof(Veiculo));
    veiculo->codigo = lerInt("Digite o código do veículo que você deseja editar: ");

    // Procurar o veículo
    int posicao = showVeiculo(veiculos, veiculo->codigo);

    if (posicao == FALSE) {
        printf("Veículo não encontrado.\n");
        free(veiculo);
        return;
    }

    strcpy(veiculos[posicao].placa, lerString("Digite a nova placa do veículo: "));
    strcpy(veiculos[posicao].modelo, lerString("Digite o modelo do veículo: "));
    strcpy(veiculos[posicao].marca, lerString("Digite a marca do veículo: "));
    veiculos[posicao].anofabricacao = atoi(lerString("Digite o ano de fabricação do veículo: "));
    strcpy(veiculos[posicao].chassi, lerString("Digite o chassi do veículo: "));

    // O campo ativo permanece inalterado e não é necessário modificar

    if (updateVeiculo(veiculos, &veiculos[posicao]) == FALSE) {
        printf("Erro na edição dos dados do veículo\n");
    } else {
        printf("Veículo editado com sucesso!\n");
    }

    free(veiculo); // Libera a memória alocada
}

void apagarVeiculo(Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) {
        printf("Nenhum veículo cadastrado\n");
        return;
    }

    int codigo = lerInt("Digite o código do veículo que você deseja apagar: ");
    if (deleteVeiculo(veiculos, codigo) == TRUE) {
        printf("Veículo apagado com sucesso\n");
    } else {
        printf("Veículo não existe\n");
    }
}

