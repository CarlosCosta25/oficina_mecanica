#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/peca.h"
#include "../bibliotecas/utils.h"

int qtdPecas = 0; // Variável global para controlar a quantidade de peças registradas

// Retorna o tamanho atual do array de peças
int getTamanhoPecas() {
    return qtdPecas;
}

// Incrementa a quantidade de peças
void setTamanhoPecas() {
    qtdPecas++;
}

// Função para migrar os dados das peças entre diferentes formatos (TXT, BIN, MEM)
Peca *migraDadosPeca() {
    Peca *pecas = NULL;
    FILE *buffer;

    // Verifica se o formato atual é TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.bin", "rb"); // Verifica se o arquivo binário existe
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // Altera para formato BIN
            pecas = getPecas(); // Lê os dados
            setTipoArquivo(TXT); // Retorna para TXT
            setPecas(pecas); // Escreve no formato TXT
            remove("../bd/pecas.bin"); // Remove o arquivo binário
            return NULL;
        }
    }

    // Verifica se o formato atual é BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.txt", "r"); // Verifica se o arquivo TXT existe
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

    // Verifica se o formato atual é MEM (dados em memória)
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/pecas.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            pecas = getPecas();
            setTipoArquivo(MEM);
            remove("../bd/pecas.txt");
            return pecas;
        }

        buffer = fopen("../bd/pecas.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            pecas = getPecas();
            setTipoArquivo(MEM);
            remove("../bd/pecas.bin");
            return pecas;
        }
    }

    return NULL;
}

// Função para salvar os dados de peças no formato atual (TXT ou BIN)
void setPecas(Peca *pecas) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.txt", "w");
        if (buffer != NULL) {
            escrever_arquivo_txt_peca(buffer, pecas);
            fclose(buffer);
            return;
        }
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.bin", "wb");
        if (buffer != NULL) {
            escrever_arquivo_bin_peca(buffer, pecas);
            fclose(buffer);
        }
    }
}

// Função para obter os dados de peças no formato atual
Peca *getPecas() {
    FILE *buffer;
    Peca *pecas = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/pecas.txt", "r");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo pecas.txt!\n");
            return NULL;
        }
        pecas = ler_arquivo_txt_peca(buffer);
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/pecas.bin", "rb");
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

// Função para ler dados de peças de um arquivo TXT
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
                    i = 0;
                    numPecas++;
                    pecas = realloc(pecas, (numPecas + 1) * sizeof(Peca));
                    break;
            }
        }
    }

    qtdPecas = numPecas;
    return pecas;
}

// Função para escrever dados de peças em um arquivo TXT
void escrever_arquivo_txt_peca(FILE *buffer, Peca *pecas) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        fprintf(buffer,
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
                pecas[i].ativo);
    }
}

// Função para ler dados de peças de um arquivo BIN
Peca *ler_arquivo_bin_peca(FILE *buffer) {
    qtdPecas = 0;
    int tam = getTamanhoPecas();
    Peca *pecas = malloc(sizeof(Peca) * (tam + 1));

    if (pecas == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    int i = 0;
    while (fread(&pecas[i], sizeof(Peca), 1, buffer)) {
        i++;
        setTamanhoPecas();
        pecas = realloc(pecas, (getTamanhoPecas() + 1) * sizeof(Peca));
    }

    return pecas;
}

// Função para escrever dados de peças em um arquivo BIN
void escrever_arquivo_bin_peca(FILE *buffer, Peca *pecas) {
    for (int i = 0; i < getTamanhoPecas(); i++) {
        fwrite(&pecas[i], sizeof(Peca), 1, buffer);
    }
}
