#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

int qtdPecas = 0;

int getTamanhoPecas() {
    return qtdPecas;
}

void setTamanhoPecas() {
    qtdPecas++;
}

Peca *migraDadosPeca() {
    Peca *pecas = NULL;
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para bin
            pecas = getPecas();
            setTipoArquivo(TXT); // volta para o arquivo txt

            setPecas(pecas); // escreve no txt
            remove("../bd/pecas.bin");
            return NULL;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            pecas = getPecas();
            setTipoArquivo(BIN);
            setPecas(pecas);
            remove("../bd/pecas.txt");
            return NULL;
        }
    }
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/pecas.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT); // muda o tipo de arquivo para TXT
            pecas = getPecas();
            setTipoArquivo(MEM);
            remove("../bd/pecas.txt");
            return pecas;
        }

        buffer = fopen("../bd/pecas.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para BIN
            pecas = getPecas();
            setTipoArquivo(MEM);
            remove("../bd/pecas.bin");
            return pecas;
        }
    }
    return NULL;
}

void setPecas(Peca *pecas) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.txt", "w"); // Abre o arquivo para escrita de texto
        if (buffer != NULL) {
            escrever_arquivo_txt_peca(buffer, pecas);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.bin", "wb"); // Abre o arquivo para escrita binária
        if (buffer != NULL) {
            escrever_arquivo_bin_peca(buffer, pecas);
            fclose(buffer);
        }
    }
}

Peca *getPecas() {
    FILE *buffer;
    Peca *pecas = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo pecas.txt!\n");
            return NULL;
        }
        pecas = ler_arquivo_txt_peca(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo pecas.bin!\n");
            return NULL;
        }
        pecas = ler_arquivo_bin_peca(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return pecas;
}

Peca *ler_arquivo_txt_peca(FILE *buffer) {
    int numPecas = 0;
    Peca *pecas = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            pecas = malloc(sizeof(Peca) * (numPecas + 1));
            isPrimeiro = FALSE;
        } else {
            pecas = realloc(pecas, (numPecas + 1) * sizeof(Peca));
        }
        if (equals("<registro>\n", Linha) == FALSE && equals("</registro>\n", Linha) == FALSE) {
            switch (i) {
                case 0:
                    pecas[numPecas].codigo = atoi(removeTags(Linha));
                    i++;
                    break;
                case 1:
                    strcpy(pecas[numPecas].descricao, removeTags(Linha));
                    i++;
                    break;
                case 2:
                    strcpy(pecas[numPecas].fabricante, removeTags(Linha));
                    i++;
                    break;
                case 3:
                    pecas[numPecas].fornecedor = atoi(removeTags(Linha));
                    i++;
                    break;
                case 4:
                    pecas[numPecas].preco_custo = atof(removeTags(Linha));
                    i++;
                    break;
                case 5:
                    pecas[numPecas].preco_venda = atof(removeTags(Linha));
                    i++;
                    break;
                case 6:
                    pecas[numPecas].estoque = atoi(removeTags(Linha));
                    i++;
                    break;
                case 7:
                    pecas[numPecas].estoque_min = atoi(removeTags(Linha));
                    i++;
                    break;
                case 8:
                    pecas[numPecas].ativo = atoi(removeTags(Linha));
                    i = 0; // Reinicia para ler a próxima peça
                    numPecas++;
                    pecas = realloc(pecas, (numPecas + 1) * sizeof(Peca));
                    break;
            }
        }
    }
    qtdPecas = numPecas;
    return pecas;
}

void escrever_arquivo_txt_peca(FILE *buffer, Peca *pecas) {
    if (getTamanhoPecas() == 0) setTamanhoPecas(); // caso não tenha nenhuma peça cadastrada
    printf("getTamanhoP: %d no model", getTamanhoPecas());
    for (int i = 0; i < getTamanhoPecas(); i++) {
        int escrevendo = fprintf(buffer,
                                 "<registro>\n"
                                 "<codigo>%d</codigo>\n"
                                 "<descricao>%s</descricao>\n"
                                 "<fabricante>%s</fabricante>\n"
                                 "<fornecedor>%d</fornecedor>\n"
                                 "<preco_custo>%.2f</preco_custo>\n"
                                 "<preco_venda>%.2f</preco_venda>\n"
                                 "<estoque>%d</estoque>\n"
                                 "<estoque_min>%d</estoque_min>\n"
                                 "<ativo>%d</ativo>\n"
                                 "</registro>\n",
                                 pecas[i].codigo,
                                 pecas[i].descricao,
                                 pecas[i].fabricante,
                                 pecas[i].fornecedor,
                                 pecas[i].preco_custo,
                                 pecas[i].preco_venda,
                                 pecas[i].estoque,
                                 pecas[i].estoque_min,
                                 pecas[i].ativo
        );
        if (escrevendo < 0) {
            return;
        }
    }
}

Peca *ler_arquivo_bin_peca(FILE *buffer) {
    qtdPecas = 0;
    int tam = getTamanhoPecas();
    int isPrimeiro = TRUE;

    Peca *pecas = malloc(sizeof(Peca) * (tam + 1));
    if (pecas == NULL) printf("Erro ao alocar a memoria\n");
    int i = 0;
    while (fread(&pecas[i], sizeof(Peca), 1, buffer)) {
        if (pecas == NULL) printf("Erro ao realocar a memoria\n");
        i++;
        setTamanhoPecas();
        pecas = realloc(pecas, (getTamanhoPecas() + 1) * sizeof(Peca));
    }
    return pecas;
}

void escrever_arquivo_bin_peca(FILE *buffer, Peca *pecas) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        if (fwrite(&pecas[i], sizeof(Peca), 1, buffer)) {
        }
    }
}
