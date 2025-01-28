// estoqueModel.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/estoque.h"
#include "../bibliotecas/oficina.h"
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

static int qtdEstoque = 0;

void setTamanhoEstoque() {
    qtdEstoque++;
}

int getTamanhoEstoque() {
    return qtdEstoque;
}

CompraPeca* migraDadosEstoque() {
    CompraPeca* estoque = NULL;
    FILE* buffer;

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
    } else if (getTipoArquivo() == BIN) {
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

    return getEstoque();
}

void setEstoque(CompraPeca* estoque) {
    FILE* buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/estoque.txt", "w");
        if (buffer != NULL) {
            escreverArquivoTxtEstoque(buffer, estoque);
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

CompraPeca* getEstoque() {
    FILE* buffer;
    CompraPeca* estoque = NULL;

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

CompraPeca* lerArquivoTxtEstoque(FILE* buffer) {
    CompraPeca* estoque = NULL;
    char linha[200];
    int numEstoque = 0;
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
            case 7: estoque[numEstoque].codTransacao = atoi(removeTags(linha)); 
                   numEstoque++; 
                   i = -1; 
                   break;
        }
        i++;
    }

    qtdEstoque = numEstoque;
    return estoque;
}

void escreverArquivoTxtEstoque(FILE* buffer, CompraPeca* estoque) {
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

CompraPeca* lerArquivoBinEstoque(FILE* buffer) {
    fseek(buffer, 0, SEEK_END);
    int numEstoque = ftell(buffer) / sizeof(CompraPeca);
    fseek(buffer, 0, SEEK_SET);

    CompraPeca* estoque = malloc(numEstoque * sizeof(CompraPeca));
    fread(estoque, sizeof(CompraPeca), numEstoque, buffer);
    qtdEstoque = numEstoque;

    return estoque;
}

void escreverArquivoBinEstoque(FILE* buffer, CompraPeca* estoque) {
    fwrite(estoque, sizeof(CompraPeca), getTamanhoEstoque(), buffer);
}
// Atualiza o estoque de uma peça
void atualizarEstoque(Peca *peca, int quantidade, float precoCusto, float frete, float imposto, Oficina *oficina) {
    // Atualiza o estoque com a nova quantidade adquirida
    peca->estoque += quantidade;

    // Atualiza o preço de custo da peça
    peca->preco_custo = precoCusto;

    // Calcula o preço de venda com base na margem de lucro da oficina
    float margemLucro = oficina->porcentagem_lucro / 100.0; // Converte porcentagem para decimal
    peca->preco_venda = (precoCusto + frete + imposto) * (1 + margemLucro);

    printf("Estoque atualizado: %s\n", peca->descricao);
    printf("Novo estoque: %d | Preço de Venda: R$%.2f\n", peca->estoque, peca->preco_venda);
}
int buscarPecaPorNome(Peca *pecas, const char *nome) {
    for (int i = 0; i < getTamanhoEstoque(); i++) {
        if (strcmp(pecas[i].descricao, nome) == 0) {
            return i; // Retorna o índice ou código da peça
        }
    }
    return -1; // Retorna -1 se a peça não for encontrada
}