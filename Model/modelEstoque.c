#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"

// Variável global para armazenar o tamanho do estoque
static int tamanhoEstoque = 0;
static CompraPeca *estoque = NULL;

void setTamanhoEstoque(int tamanho) {
    tamanhoEstoque = tamanho;
}

int getTamanhoEstoque() {
    return tamanhoEstoque;
}

CompraPeca *migraDadosEstoque() {
    // Implementação para migrar dados do estoque (se necessário)
    return estoque;
}

void setEstoque(CompraPeca *novoEstoque) {
    estoque = novoEstoque;
}

CompraPeca *getEstoque() {
    return estoque;
}

CompraPeca *lerArquivoTxtEstoque(FILE *buffer) {
    // Implementar leitura de arquivo TXT
    // Exemplo básico de leitura
    if (!buffer) return NULL;

    CompraPeca *estoque = (CompraPeca *)malloc(sizeof(CompraPeca) * tamanhoEstoque);

    for (int i = 0; i < tamanhoEstoque; i++) {
        fscanf(buffer, "%d %d %d %d %f %f %f %d %d",
            &estoque[i].codigo, &estoque[i].codPeca, &estoque[i].qtdPecas,
            &estoque[i].codFornecedor, &estoque[i].valorImposto, &estoque[i].valorFrete,
            &estoque[i].valorTotalPeca, &estoque[i].codTransacao, &estoque[i].datatransacao);
    }
    return estoque;
}

void escreverArquivoTxtEstoque(FILE *buffer, CompraPeca *estoque) {
    // Implementar escrita de arquivo TXT
    if (!buffer || !estoque) return;

    for (int i = 0; i < tamanhoEstoque; i++) {
        fprintf(buffer, "%d %d %d %d %f %f %f %d %d\n",
            estoque[i].codigo, estoque[i].codPeca, estoque[i].qtdPecas,
            estoque[i].codFornecedor, estoque[i].valorImposto, estoque[i].valorFrete,
            estoque[i].valorTotalPeca, estoque[i].codTransacao, estoque[i].datatransacao);
    }
}

CompraPeca *lerArquivoBinEstoque(FILE *buffer) {
    // Implementar leitura de arquivo BIN
    if (!buffer) return NULL;

    CompraPeca *estoque = (CompraPeca *)malloc(sizeof(CompraPeca) * tamanhoEstoque);
    fread(estoque, sizeof(CompraPeca), tamanhoEstoque, buffer);
    return estoque;
}

void escreverArquivoBinEstoque(FILE *buffer, CompraPeca *estoque) {
    // Implementar escrita de arquivo BIN
    if (!buffer || !estoque) return;

    fwrite(estoque, sizeof(CompraPeca), tamanhoEstoque, buffer);
}
