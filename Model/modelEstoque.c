#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/utils.h"

int qtdEstoque = 0;

// Atualiza o tamanho do estoque
void setTamanhoEstoque() {
    qtdEstoque++;
}

// Retorna o tamanho atual do estoque
int getTamanhoEstoque() {
    return qtdEstoque;
}

// Migra dados do estoque entre formatos diferentes (TXT, BIN, MEM)
CompraPeca *migraDadosEstoque() {
    CompraPeca *estoque = NULL;
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/estoque.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            estoque = getEstoque();
            setTipoArquivo(TXT);
            setEstoque(estoque);
            free(estoque);
            remove("../bd/estoque.bin");
        }
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/estoque.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            estoque = getEstoque();
            setTipoArquivo(BIN);
            setEstoque(estoque);
            free(estoque);
            remove("../bd/estoque.txt");
        }
    }

    return estoque;
}

// Salva os dados do estoque no formato atual
void setEstoque(CompraPeca *estoque) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/estoque.txt", "w");
        if (buffer != NULL) {
            //escreverArquivoTxtEstoque(buffer, estoque);
            fclose(buffer);
        }
    } else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/estoque.bin", "wb");
        if (buffer != NULL) {
            escreverArquivoBinEstoque(buffer, estoque);
            fclose(buffer);
        }
    }
}

// Retorna os dados do estoque
CompraPeca *getEstoque() {
    FILE *buffer;
    CompraPeca *estoque = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/estoque.txt", "r");
        if (buffer != NULL) {
            estoque = lerArquivoTxtEstoque(buffer);
            fclose(buffer);
        }
    } else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/estoque.bin", "rb");
        if (buffer != NULL) {
            estoque = lerArquivoBinEstoque(buffer);
            fclose(buffer);
        }
    }

    return estoque;
}

// Lê o estoque de um arquivo TXT
CompraPeca *lerArquivoTxtEstoque(FILE *buffer) {
    int numEstoque = 0;
    CompraPeca *estoque = NULL;
    char linha[200];
    int i = 0;
    int isPrimeiro = 1;

    while (fgets(linha, sizeof(linha), buffer)) {
        if (isPrimeiro) {
            estoque = malloc(sizeof(CompraPeca));
            isPrimeiro = 0;
        } else {
            estoque = realloc(estoque, (numEstoque + 1) * sizeof(CompraPeca));
        }

        if (linha[0] != '<' || linha[1] == '/') continue;

        switch (i) {
            case 0: estoque[numEstoque].codigo = atoi(removeTags(linha)); break;
            case 1: estoque[numEstoque].codPeca = atoi(removeTags(linha)); break;
            case 2: estoque[numEstoque].qtdPecas = atoi(removeTags(linha)); break;
            case 3: estoque[numEstoque].codFornecedor = atoi(removeTags(linha)); break;
            case 4: estoque[numEstoque].valorImposto = atof(removeTags(linha)); break;
            case 5: estoque[numEstoque].valorFrete = atof(removeTags(linha)); break;
            case 6: estoque[numEstoque].valorTotalPeca = atof(removeTags(linha)); break;
            case 7: estoque[numEstoque].codTransacao = atoi(removeTags(linha)); numEstoque++; i = -1; break;
        }
        i++;
    }

    qtdEstoque = numEstoque;
    return estoque;
}

// Escreve o estoque em um arquivo TXT
void escreverArquivoTxtEstoque(FILE *buffer, CompraPeca *estoque) {
    for (int i = 0; i < getTamanhoEstoque(); i++) {
        fprintf(buffer,
            "<registro>\n"
            "<codigo>%d</codigo>\n"
            "<codPeca>%d</codPeca>\n"
            "<qtdPecas>%d</qtdPecas>\n"
            "<codFornecedor>%d</codFornecedor>\n"
            "<valorImposto>%.2f</valorImposto>\n"
            "<valorFrete>%.2f</valorFrete>\n"
            "<valorTotalPeca>%.2f</valorTotalPeca>\n"
            "<codTransacao>%d</codTransacao>\n"
            "</registro>\n",
            estoque[i].codigo,
            estoque[i].codPeca,
            estoque[i].qtdPecas,
            estoque[i].codFornecedor,
            estoque[i].valorImposto,
            estoque[i].valorFrete,
            estoque[i].valorTotalPeca,
            estoque[i].codTransacao
        );
    }
}

// Lê o estoque de um arquivo BIN
CompraPeca *lerArquivoBinEstoque(FILE *buffer) {
    fseek(buffer, 0, SEEK_END);
    int numEstoque = ftell(buffer) / sizeof(CompraPeca);
    fseek(buffer, 0, SEEK_SET);

    CompraPeca *estoque = malloc(numEstoque * sizeof(CompraPeca));
    fread(estoque, sizeof(CompraPeca), numEstoque, buffer);
    qtdEstoque = numEstoque;

    return estoque;
}

// Escreve o estoque em um arquivo BIN
void escreverArquivoBinEstoque(FILE *buffer, CompraPeca *estoque) {
    fwrite(estoque, sizeof(CompraPeca), getTamanhoEstoque(), buffer);
}
