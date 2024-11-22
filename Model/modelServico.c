#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/servico.h"
#include "../bibliotecas/utils.h"

int qtdServicos = 0;

int getTamanhoServicos() {
    return qtdServicos;
}

void setTamanhoServicos() {
    qtdServicos++;
}

Servico * migraDadosServicos() {
    Servico *servicos = NULL;
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para bin
            servicos = getServicos();
            setTipoArquivo(TXT); // volta para o arquivo txt

            setServicos(servicos); // escreve no txt
            remove("../bd/servicos.bin");
            return NULL;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            servicos = getServicos();
            setTipoArquivo(BIN);
            setServicos(servicos);
            remove("../bd/servicos.txt");
            return NULL;
        }
    }
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/servicos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT); // muda o tipo de arquivo para TXT
            servicos = getServicos();
            setTipoArquivo(MEM);
            remove("../bd/servicos.txt");
            return servicos;
        }

        buffer = fopen("../bd/servicos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para BIN
            servicos = getServicos();
            setTipoArquivo(MEM);
            remove("../bd/servicos.bin");
            return servicos;
        }
    }
    return NULL;
}

void setServicos(Servico *servicos) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.txt", "w"); // Abre o arquivo para escrita de texto
        if (buffer != NULL) {
            escrever_arquivo_txt_servico(buffer, servicos);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.bin", "wb"); // Abre o arquivo para escrita binária
        if (buffer != NULL) {
            escrever_arquivo_bin_servico(buffer, servicos);
            fclose(buffer);
        }
    }
}
Servico *getServicos() {
    FILE *buffer;
    Servico *servicos = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo servicos.txt!\n");
            return NULL;
        }
        servicos = ler_arquivo_txt_servico(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo servicos.bin!\n");
            return NULL;
        }
        servicos = ler_arquivo_bin_servico(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return servicos;
}

Servico *ler_arquivo_txt_servico(FILE *buffer) {
    int numServicos = 0;
    Servico *servicos = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            servicos = malloc(sizeof(Servico) * (numServicos + 1));
            isPrimeiro = FALSE;
        } else {
            servicos = realloc(servicos, (numServicos + 1) * sizeof(Servico));
        }
        if (equals("<registro>\n", Linha) == FALSE && equals("</registro>\n", Linha) == FALSE) {
            switch (i) {
                case 0:
                    servicos[numServicos].codigo = atoi(removeTags(Linha));
                i++;
                break;
                case 1:
                    strcpy(servicos[numServicos].descricao, removeTags(Linha));
                i++;
                break;
                case 2:
                    servicos[numServicos].preco = atof(removeTags(Linha));
                i++;
                break;
                case 3:
                    servicos[numServicos].comicao = atof(removeTags(Linha));
                i++;
                break;
                case 4:
                    servicos[numServicos].ativo = atoi(removeTags(Linha));
                i = 0; // Reinicia para ler o próximo serviço
                numServicos++;
                servicos = realloc(servicos, (numServicos + 1) * sizeof(Servico));
                break;
            }
        }
    }
    qtdServicos = numServicos; // Atualiza a quantidade de serviços
    return servicos;
}

void escrever_arquivo_txt_servico(FILE *buffer, Servico *servicos) {
    if (getTamanhoServicos() == 0) setTamanhoServicos(); // caso não tenha nenhum serviço cadastrado

    for (int i = 0; i < getTamanhoServicos(); i++) {
        int escrevendo = fprintf(buffer,
                                 "<registro>\n"
                                 "<codigo>%d</codigo>\n"
                                 "<descricao>%s</descricao>\n"
                                 "<preco>%.2f</preco>\n"
                                 "<comicao>%.2f</comicao>\n"
                                 "<ativo>%d</ativo>\n"
                                 "</registro>\n",
                                 servicos[i].codigo,
                                 servicos[i].descricao,
                                 servicos[i].preco,
                                 servicos[i].comicao,
                                 servicos[i].ativo
        );
        if (escrevendo < 0) {
            printf("Erro ao escrever no arquivo.\n");
            return;
        }
    }
}
Servico *ler_arquivo_bin_servico(FILE *buffer) {
    qtdServicos = 0;
    int tam = getTamanhoServicos();
    int isPrimeiro = TRUE;

    Servico *servicos = malloc(sizeof(Servico) * (tam + 1));
    if (servicos == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    int i = 0;
    while (fread(&servicos[i], sizeof(Servico), 1, buffer)) {
        if (servicos == NULL) {
            printf("Erro ao realocar memória\n");
            return NULL;
        }
        i++;
        setTamanhoServicos();
        servicos = realloc(servicos, (getTamanhoServicos() + 1) * sizeof(Servico));
        if (servicos == NULL) {
            printf("Erro ao realocar memória\n");
            return NULL;
        }
    }
    return servicos;
}

void escrever_arquivo_bin_servico(FILE *buffer, Servico *servicos) {
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (fwrite(&servicos[i], sizeof(Servico), 1, buffer) != 1) {
            printf("Erro ao escrever no arquivo binário\n");
            break;
        }
    }
}

