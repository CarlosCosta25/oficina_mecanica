#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

// Variável global para armazenar a quantidade de fornecedores
int qtdFornecedores = 0;

// Função para obter a quantidade atual de fornecedores
int getTamanhoFornecedores() {
    return qtdFornecedores;
}

// Função para incrementar a quantidade de fornecedores
void setTamanhoFornecedores() {
    qtdFornecedores++;
}

/**
 * Função para migrar dados de fornecedores entre diferentes formatos de armazenamento (TXT, BIN ou MEM).
 * Retorna um ponteiro para os dados migrados ou NULL se não for necessário migrar.
 */
Fornecedor *migraDadosFornecedor() {
    Fornecedor *fornecedores = NULL;
    FILE *buffer;

    // Caso o tipo de arquivo seja TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            fornecedores = getFornecedores();
            setTipoArquivo(TXT);
            setFornecedores(fornecedores);
            remove("../bd/fornecedores.bin");
            return NULL;
        }
    }

    // Caso o tipo de arquivo seja BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/fornecedores.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            fornecedores = getFornecedores();
            setTipoArquivo(BIN);
            setFornecedores(fornecedores);
            remove("../bd/fornecedores.txt");
            return NULL;
        }
    }
    if (getTipoArquivo() == MEM) {
        // Caso o tipo de armazenamento seja MEM
        buffer = fopen("../bd/fornecedores.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            fornecedores = getFornecedores();
            setTipoArquivo(MEM);
            remove("../bd/fornecedores.txt");
            return fornecedores;
        }

        buffer = fopen("../bd/fornecedores.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            fornecedores = getFornecedores();
            setTipoArquivo(MEM);
            remove("../bd/fornecedores.bin");
            return fornecedores;
        }
    }
    return NULL;
}

/**
 * Salva os dados de fornecedores no formato especificado (TXT ou BIN).
 */
void setFornecedores(Fornecedor *fornecedores) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.txt", "w"); // Abre para escrita no TXT
        if (buffer != NULL) {
            escrever_arquivo_txt_fornecedor(buffer, fornecedores);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/fornecedores.bin", "wb"); // Abre para escrita no BIN
        if (buffer != NULL) {
            escrever_arquivo_bin_fornecedor(buffer, fornecedores);
            fclose(buffer);
        }
    }
}

/**
 * Lê os dados de fornecedores do formato especificado (TXT ou BIN).
 * Retorna um ponteiro para o array de fornecedores.
 */
Fornecedor *getFornecedores() {
    FILE *buffer;
    Fornecedor *fornecedores = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.txt", "r");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo fornecedores.txt!\n");
            return NULL;
        }
        fornecedores = ler_arquivo_txt_fornecedor(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/fornecedores.bin", "rb");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo fornecedores.bin!\n");
            return NULL;
        }
        fornecedores = ler_arquivo_bin_fornecedor(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL; // Não há manipulação de dados diretamente na memória
    }
    return fornecedores;
}

/**
 * Lê os fornecedores de um arquivo TXT e retorna um array dinâmico de `Fornecedor`.
 */
Fornecedor *ler_arquivo_txt_fornecedor(FILE *buffer) {
    int numFornecedores = 0;
    Fornecedor *fornecedores = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    // Processa cada linha do arquivo
    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro) {
            fornecedores = malloc(sizeof(Fornecedor));
            isPrimeiro = FALSE;
        } else {
            fornecedores = realloc(fornecedores, (numFornecedores + 1) * sizeof(Fornecedor));
        }

        // Lógica para extrair e atribuir dados baseados na estrutura
        if (!equals("<registro>\n", Linha) && !equals("</registro>\n", Linha)) {
            switch (i) {
                case 0: fornecedores[numFornecedores].codigo = atoi(removeTags(Linha)); i++; break;
                case 1: strcpy(fornecedores[numFornecedores].nome_fantasia, removeTags(Linha)); i++; break;
                case 2: strcpy(fornecedores[numFornecedores].razao_social, removeTags(Linha)); i++; break;
                case 3: fornecedores[numFornecedores].incricao_estadual = atoi(removeTags(Linha)); i++; break;
                case 4: strcpy(fornecedores[numFornecedores].cnpj, removeTags(Linha)); i++; break;
                case 5: strcpy(fornecedores[numFornecedores].endereco, removeTags(Linha)); i++; break;
                case 6: strcpy(fornecedores[numFornecedores].telefone, removeTags(Linha)); i++; break;
                case 7: strcpy(fornecedores[numFornecedores].email, removeTags(Linha)); i++; break;
                case 8:
                    fornecedores[numFornecedores].ativo = atoi(removeTags(Linha));
                    i = 0;
                    numFornecedores++;
                    break;
            }
        }
    }
    qtdFornecedores = numFornecedores;
    return fornecedores;
}

// Escreve fornecedores em um arquivo de texto
void escrever_arquivo_txt_fornecedor(FILE *buffer, Fornecedor *fornecedores) {
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        fprintf(buffer,
                "<registro>\n"
                "<codigo>%d</codigo>\n"
                "<nome_fantasia>%s</nome_fantasia>\n"
                "<razao_social>%s</razao_social>\n"
                "<incricao_estadual>%d</incricao_estadual>\n"
                "<cnpj>%s</cnpj>\n"
                "<endereco>%s</endereco>\n"
                "<telefone>%s</telefone>\n"
                "<email>%s</email>\n"
                "<ativo>%d</ativo>\n"
                "</registro>\n",
                fornecedores[i].codigo,
                fornecedores[i].nome_fantasia,
                fornecedores[i].razao_social,
                fornecedores[i].incricao_estadual,
                fornecedores[i].cnpj,
                fornecedores[i].endereco,
                fornecedores[i].telefone,
                fornecedores[i].email,
                fornecedores[i].ativo);
    }
}

// Lê fornecedores de um arquivo binário
Fornecedor *ler_arquivo_bin_fornecedor(FILE *buffer) {
    Fornecedor *fornecedores = malloc(sizeof(Fornecedor));
    int i = 0;

    while (fread(&fornecedores[i], sizeof(Fornecedor), 1, buffer)) {
        i++;
        fornecedores = realloc(fornecedores, (i + 1) * sizeof(Fornecedor));
    }
    qtdFornecedores = i;
    return fornecedores;
}

// Escreve fornecedores em um arquivo binário
void escrever_arquivo_bin_fornecedor(FILE *buffer, Fornecedor *fornecedores) {
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        fwrite(&fornecedores[i], sizeof(Fornecedor), 1, buffer);
    }
}
