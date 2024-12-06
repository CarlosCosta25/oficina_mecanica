#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/veiculo.h"
#include "../bibliotecas/utils.h"

Veiculo* readVeiculos() {
    Veiculo * veiculos = NULL;
    veiculos = getVeiculos();
        return veiculos;
    }

int createVeiculo(Veiculo **veiculos, Veiculo *veiculo) {
    int tamanhoAtual = getTamanhoVeiculos();

    // Realoca a memória para acomodar um novo veiculo
    //Veiculo *novoVeiculos = realloc(*veiculos, (tamanhoAtual + 1) * sizeof(Veiculo));
    Veiculo *novoVeiculos = realloc(*veiculos, (tamanhoAtual + 1) * sizeof(Veiculo));
    if (novoVeiculos == NULL) {
        printf("Erro ao alocar memória para Veículos.\n");
        return FALSE; // Retorna false indicando falha
    }

    *veiculos = novoVeiculos; // Atualiza o ponteiro de veiculos com o novo endereço
    int index = tamanhoAtual; // Novo índice é o tamanho atual

    // Preenche os dados do novo veículo no array
    (*veiculos)[index].codigo = buscaNovoIDVeiculo(*veiculos);
    strcpy((*veiculos)[index].placa, veiculo->placa);
    strcpy((*veiculos)[index].modelo, veiculo->modelo);
    strcpy((*veiculos)[index].marca, veiculo->marca);
    (*veiculos)[index].anofabricacao = veiculo->anofabricacao; //Conferir essa linha
    strcpy((*veiculos)[index].chassi, veiculo->chassi);
    (*veiculos)[index].ativo = 1; // Veiculo ativo ao ser criado

    setTamanhoVeiculos(); // Atualiza o tamanho dos veiculos

    // Salva veiculos se o tipo de arquivo não for memória
    if (getTipoArquivo() != MEM) setVeiculos(*veiculos);

    return TRUE;
}

int showVeiculo(Veiculo *veiculos, int codigo) {
    if (veiculos == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoVeiculos();

    // Procura o veiculo com o código especificado dentro do limite do array
    while (posicao < tamanho && veiculos[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o veiculo foi encontrado e se está ativo
    if (posicao == tamanho || veiculos[posicao].ativo == FALSE)
        return FALSE;

    return posicao;
}
int updateVeiculo(Veiculo *veiculos, Veiculo *veiculo) {

    int posicao = showVeiculo(veiculos, veiculo->codigo);

    if (posicao == FALSE) return FALSE;

    // Atualiza os campos necessários
    veiculos[posicao].codigo = veiculo->codigo;
    strcpy(veiculos[posicao].placa, veiculo->placa);
    strcpy(veiculos[posicao].modelo, veiculo->modelo);
    strcpy(veiculos[posicao].marca, veiculo->marca);
    veiculos[posicao].anofabricacao = veiculo->anofabricacao;
    strcpy(veiculos[posicao].chassi, veiculo->chassi);
    veiculos[posicao].ativo = veiculo->ativo; // Atualiza o campo ativo

    if (getTipoArquivo() != MEM) setVeiculos(veiculos);
    return TRUE;
}

int deleteVeiculo(Veiculo* veiculos, int codigo) {
    int posicao = showVeiculo(veiculos, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o veiculo existe e está ativo

    veiculos[posicao].ativo = FALSE; // Marca o veiculo como inativo
    if (getTipoArquivo() != MEM) setVeiculos(veiculos);
    return TRUE;
}

int buscaNovoIDVeiculo(Veiculo * veiculos) {
    int maior = 1;
    if(getTamanhoVeiculos() == 0 ) return maior;
    for(int i = 0; i < getTamanhoVeiculos(); i++) {
        if(maior <= veiculos[i].codigo) {
            maior = veiculos[i].codigo+1;
        }
    }
        return maior;
}
