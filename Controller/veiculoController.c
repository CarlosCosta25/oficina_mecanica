#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/veiculo.h"
#include "../bibliotecas/utils.h"
// Função para ler todos os veículos cadastrados
Veiculo* readVeiculos() {
    Veiculo *veiculos = NULL;
    veiculos = getVeiculos(); // Obtém a lista de veículos de um arquivo ou memória
    return veiculos;          // Retorna o ponteiro para a lista de veículos
}

// Função para criar um novo veículo
int createVeiculo(Veiculo **veiculos, Veiculo *veiculo) {
    int tamanhoAtual = getTamanhoVeiculos(); // Obtém o tamanho atual da lista de veículos

    // Realoca a memória para incluir o novo veículo
    Veiculo *novoVeiculos = realloc(*veiculos, (tamanhoAtual + 1) * sizeof(Veiculo));
    if (novoVeiculos == NULL) {
        printf("Erro ao alocar memória para Veículos.\n");
        return FALSE; // Retorna FALSE indicando falha
    }

    *veiculos = novoVeiculos; // Atualiza o ponteiro da lista de veículos
    int index = tamanhoAtual; // Define o índice do novo veículo como o último da lista

    // Preenche os dados do novo veículo no array
    (*veiculos)[index].codigo = buscaNovoIDVeiculo(*veiculos); // Gera um novo ID único
    strcpy((*veiculos)[index].placa, veiculo->placa);          // Copia a placa do veículo
    strcpy((*veiculos)[index].modelo, veiculo->modelo);        // Copia o modelo do veículo
    strcpy((*veiculos)[index].marca, veiculo->marca);          // Copia a marca do veículo
    (*veiculos)[index].anofabricacao = veiculo->anofabricacao; // Copia o ano de fabricação
    strcpy((*veiculos)[index].chassi, veiculo->chassi);        // Copia o chassi do veículo
    (*veiculos)[index].ativo = 1;                              // Marca o veículo como ativo

    setTamanhoVeiculos(); // Incrementa o tamanho da lista de veículos

    // Salva os veículos no arquivo se o tipo de armazenamento não for memória
    if (getTipoArquivo() != MEM) setVeiculos(*veiculos);

    return TRUE; // Retorna TRUE indicando sucesso
}

// Função para localizar um veículo pelo código
int showVeiculo(Veiculo *veiculos, int codigo) {
    if (veiculos == NULL) return FALSE; // Retorna FALSE se a lista de veículos for nula

    int posicao = 0;
    int tamanho = getTamanhoVeiculos(); // Obtém o tamanho atual da lista de veículos

    // Procura o veículo com o código especificado
    while (posicao < tamanho && veiculos[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o veículo foi encontrado e se está ativo
    if (posicao == tamanho || veiculos[posicao].ativo == FALSE)
        return FALSE;

    return posicao; // Retorna a posição do veículo encontrado
}

// Função para atualizar os dados de um veículo existente
int updateVeiculo(Veiculo *veiculos, Veiculo *veiculo) {
    int posicao = showVeiculo(veiculos, veiculo->codigo); // Localiza o veículo pelo código

    if (posicao == FALSE) return FALSE; // Retorna FALSE se o veículo não for encontrado

    // Atualiza os campos do veículo
    veiculos[posicao].codigo = veiculo->codigo;
    strcpy(veiculos[posicao].placa, veiculo->placa);
    strcpy(veiculos[posicao].modelo, veiculo->modelo);
    strcpy(veiculos[posicao].marca, veiculo->marca);
    veiculos[posicao].anofabricacao = veiculo->anofabricacao;
    strcpy(veiculos[posicao].chassi, veiculo->chassi);
    veiculos[posicao].ativo = veiculo->ativo;

    // Salva os veículos no arquivo se o tipo de armazenamento não for memória
    if (getTipoArquivo() != MEM) setVeiculos(veiculos);

    return TRUE; // Retorna TRUE indicando sucesso
}

// Função para excluir (ou desativar) um veículo
int deleteVeiculo(Veiculo* veiculos, int codigo) {
    int posicao = showVeiculo(veiculos, codigo); // Localiza o veículo pelo código

    if (posicao == FALSE) return FALSE; // Retorna FALSE se o veículo não for encontrado

    veiculos[posicao].ativo = FALSE; // Marca o veículo como inativo

    // Salva os veículos no arquivo se o tipo de armazenamento não for memória
    if (getTipoArquivo() != MEM) setVeiculos(veiculos);

    return TRUE; // Retorna TRUE indicando sucesso
}

// Função para gerar um novo ID exclusivo para um novo veículo
int buscaNovoIDVeiculo(Veiculo *veiculos) {
    int maior = 1;

    // Retorna 1 se não houver veículos cadastrados
    if (getTamanhoVeiculos() == 0) return maior;

    // Percorre a lista de veículos para encontrar o maior ID existente
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (maior <= veiculos[i].codigo) {
            maior = veiculos[i].codigo + 1; // Define o próximo ID como o maior + 1
        }
    }

    return maior; // Retorna o novo ID gerado
}