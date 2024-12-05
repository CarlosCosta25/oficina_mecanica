#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/veiculo.h"
#include "../bibliotecas/utils.h"

// Função para obter a lista de veículos do sistema
Veiculo* readVeiculos() {
    Veiculo *veiculos = NULL; // Inicializa o ponteiro para veículos como NULL
    veiculos = getVeiculos(); // Obtém os veículos armazenados
    return veiculos; // Retorna o ponteiro para o array de veículos
}

// Função para criar um novo veículo e adicioná-lo ao array de veículos
int createVeiculo(Veiculo **veiculos, Veiculo *veiculo) {
    int tamanhoAtual = getTamanhoVeiculos(); // Obtém o tamanho atual do array de veículos

    // Realoca memória para incluir um novo veículo
    Veiculo *novoVeiculos = realloc(*veiculos, (tamanhoAtual + 1) * sizeof(Veiculo));
    if (novoVeiculos == NULL) { // Verifica se a realocação falhou
        printf("Erro ao alocar memória para Veículos.\n");
        return FALSE; // Retorna falha
    }

    *veiculos = novoVeiculos; // Atualiza o ponteiro do array de veículos
    int index = tamanhoAtual; // Define o índice para o novo veículo

    // Preenche os campos do novo veículo
    (*veiculos)[index].codigo = buscaNovoIDVeiculo(*veiculos); // Gera um novo ID único
    strcpy((*veiculos)[index].placa, veiculo->placa);          // Copia a placa
    strcpy((*veiculos)[index].modelo, veiculo->modelo);        // Copia o modelo
    strcpy((*veiculos)[index].marca, veiculo->marca);          // Copia a marca
    (*veiculos)[index].anofabricacao = veiculo->anofabricacao; // Define o ano de fabricação
    strcpy((*veiculos)[index].chassi, veiculo->chassi);        // Copia o número do chassi
    (*veiculos)[index].ativo = 1;                              // Marca o veículo como ativo

    setTamanhoVeiculos(); // Atualiza o tamanho do array de veículos

    // Salva os veículos no armazenamento persistente, se necessário
    if (getTipoArquivo() != MEM) setVeiculos(*veiculos);

    return TRUE; // Retorna sucesso
}

// Função para buscar o índice de um veículo pelo código
int showVeiculo(Veiculo *veiculos, int codigo) {
    if (veiculos == NULL) return FALSE; // Verifica se a lista de veículos é nula

    int posicao = 0;
    int tamanho = getTamanhoVeiculos(); // Obtém o tamanho do array de veículos

    // Busca o veículo pelo código
    while (posicao < tamanho && veiculos[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o veículo foi encontrado e está ativo
    if (posicao == tamanho || veiculos[posicao].ativo == FALSE)
        return FALSE; // Retorna falha se não encontrado ou está inativo

    return posicao; // Retorna o índice do veículo
}

// Função para atualizar os dados de um veículo existente
int updateVeiculo(Veiculo *veiculos, Veiculo *veiculo) {
    int posicao = showVeiculo(veiculos, veiculo->codigo); // Busca o índice do veículo pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se o veículo não foi encontrado

    // Atualiza os campos do veículo
    veiculos[posicao].codigo = veiculo->codigo;
    strcpy(veiculos[posicao].placa, veiculo->placa);
    strcpy(veiculos[posicao].modelo, veiculo->modelo);
    strcpy(veiculos[posicao].marca, veiculo->marca);
    veiculos[posicao].anofabricacao = veiculo->anofabricacao;
    strcpy(veiculos[posicao].chassi, veiculo->chassi);
    veiculos[posicao].ativo = veiculo->ativo; // Atualiza o status ativo/inativo

    // Salva as alterações no armazenamento persistente, se necessário
    if (getTipoArquivo() != MEM) setVeiculos(veiculos);

    return TRUE; // Retorna sucesso
}

// Função para marcar um veículo como inativo
int deleteVeiculo(Veiculo* veiculos, int codigo) {
    int posicao = showVeiculo(veiculos, codigo); // Busca o índice do veículo pelo código

    if (posicao == FALSE) return FALSE; // Retorna falha se o veículo não foi encontrado

    veiculos[posicao].ativo = FALSE; // Marca o veículo como inativo

    // Salva as alterações no armazenamento persistente, se necessário
    if (getTipoArquivo() != MEM) setVeiculos(veiculos);

    return TRUE; // Retorna sucesso
}

// Função para gerar um novo ID único para veículos
int buscaNovoIDVeiculo(Veiculo *veiculos) {
    int maior = 1; // Inicia o maior ID como 1
    if (getTamanhoVeiculos() == 0) return maior; // Retorna 1 se não há veículos cadastrados

    // Itera pela lista de veículos para encontrar o maior ID
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (maior <= veiculos[i].codigo) {
            maior = veiculos[i].codigo + 1; // Atualiza o maior ID
        }
    }

    return maior; // Retorna o novo ID único
}
