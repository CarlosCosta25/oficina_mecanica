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

Fornecedor *migraDadosFornecedor() {
    Fornecedor *fornecedores = NULL;
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para bin
            fornecedores = getFornecedores();
            setTipoArquivo(TXT); // volta para o arquivo txt

            setFornecedores(fornecedores); // escreve no txt
            remove("../bd/fornecedores.bin");
            return NULL;
        }
    }
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
        buffer = fopen("../bd/fornecedores.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT); // muda o tipo de arquivo para TXT
            fornecedores = getFornecedores();
            setTipoArquivo(MEM);
            remove("../bd/fornecedores.txt");
            return fornecedores;
        }

        buffer = fopen("../bd/fornecedores.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para BIN
            fornecedores = getFornecedores();
            setTipoArquivo(MEM);
            remove("../bd/fornecedores.bin");
            return fornecedores;
        }
    }
    return NULL;
}

void setFornecedores(Fornecedor *fornecedores) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.txt", "w"); // Abre o arquivo para escrita de texto
        if (buffer != NULL) {
            escrever_arquivo_txt_fornecedor(buffer, fornecedores);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/fornecedores.bin", "wb"); // Abre o arquivo para escrita binária
        if (buffer != NULL) {
            escrever_arquivo_bin_fornecedor(buffer, fornecedores);
            fclose(buffer);
        }
    }
}

Fornecedor *getFornecedores() {
    FILE *buffer;
    Fornecedor *fornecedores = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/fornecedores.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo fornecedores.txt!\n");
            return NULL;
        }
        fornecedores = ler_arquivo_txt_fornecedor(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/fornecedores.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo fornecedores.bin!\n");
            return NULL;
        }
        fornecedores = ler_arquivo_bin_fornecedor(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return fornecedores;
}

Fornecedor *ler_arquivo_txt_fornecedor(FILE *buffer) {
    int numFornecedores = 0;
    Fornecedor *fornecedores = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            fornecedores = malloc(sizeof(Fornecedor) * (numFornecedores + 1));
            isPrimeiro = FALSE;
        } else if (isPrimeiro == FALSE) {
            fornecedores = realloc(fornecedores, (numFornecedores + 1) * sizeof(Fornecedor));
        }
        if (equals("<registro>\n", Linha) == FALSE && equals("</registro>\n", Linha) == FALSE) {
            switch (i) {
                case 0:
                    fornecedores[numFornecedores].codigo = atoi(removeTags(Linha));
                    i++;
                    break;
                case 1:
                    strcpy(fornecedores[numFornecedores].nome_fantasia, removeTags(Linha));
                    i++;
                    break;
                case 2:
                    strcpy(fornecedores[numFornecedores].razao_social, removeTags(Linha));
                    i++;
                    break;
                case 3:
                    fornecedores[numFornecedores].incricao_estadual = atoi(removeTags(Linha));
                    i++;
                    break;
                case 4:
                    strcpy(fornecedores[numFornecedores].cnpj, removeTags(Linha));
                    i++;
                    break;
                case 5:
                    strcpy(fornecedores[numFornecedores].endereco, removeTags(Linha));
                    i++;
                    break;
                case 6:
                    strcpy(fornecedores[numFornecedores].telefone, removeTags(Linha));
                    i++;
                    break;
                case 7:
                    strcpy(fornecedores[numFornecedores].email, removeTags(Linha));
                    i++;
                    break;
                case 8:
                    fornecedores[numFornecedores].ativo = atoi(removeTags(Linha));
                    i = 0; // Reinicia para ler o próximo fornecedor
                    numFornecedores++;
                    fornecedores = realloc(fornecedores, (numFornecedores + 1) * sizeof(Fornecedor));
                    break;
            }
        }
    }
    qtdFornecedores = numFornecedores;
    return fornecedores;
}

void escrever_arquivo_txt_fornecedor(FILE *buffer, Fornecedor *fornecedores) {
    if (getTamanhoFornecedores() == 0) setTamanhoFornecedores(); // caso não tenha nenhum fornecedor cadastrado
    printf("getTamanhoF: %d no model",getTamanhoFornecedores());
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        int escrevendo = fprintf(buffer,
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
                                 fornecedores[i].ativo
        );
        if (escrevendo < 0) {
            return;
        }
    }
}

Fornecedor *ler_arquivo_bin_fornecedor(FILE *buffer) {
    int tam = getTamanhoFornecedores();
    int isPrimeiro = TRUE;
    Fornecedor *fornecedores = NULL; //= malloc(sizeof(Fornecedor) * (tam + 1));
    int i = 0;
    while (fread(&fornecedores[i], sizeof(Fornecedor), 1, buffer)) {
        if (isPrimeiro == TRUE) {
            fornecedores = malloc(sizeof(Fornecedor) * (tam + 1));
            isPrimeiro = FALSE;
        } else if (isPrimeiro == FALSE) {
            fornecedores = realloc(fornecedores, (tam + 1) * sizeof(Fornecedor));
        }
        i++;
        setTamanhoFornecedores();
        //fornecedores = realloc(fornecedores, (tam + 1) * sizeof(Fornecedor));
    }
    return fornecedores;
}

void escrever_arquivo_bin_fornecedor(FILE *buffer, Fornecedor *fornecedores) {
    for (int i = 0; i < getTamanhoFornecedores(); i++) {
        if (fwrite(&fornecedores[i], sizeof(Fornecedor), 1, buffer)) {
        }
    }
}
