#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/servico.h"
#include "../bibliotecas/utils.h"

// Variável global para armazenar a quantidade de serviços
int qtdServicos = 0;

// Função para obter o número total de serviços cadastrados
int getTamanhoServicos() {
    return qtdServicos;
}

// Função para incrementar a quantidade de serviços cadastrados
void setTamanhoServicos() {
    qtdServicos++;
}

// Função para migrar os dados entre diferentes formatos de arquivo (TXT, BIN, MEM)
Servico *migraDadosServicos() {
    Servico *servicos = NULL;
    FILE *buffer;

    // Verifica se o tipo de arquivo atual é TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);  // Altera o tipo para BIN
            servicos = getServicos();
            setTipoArquivo(TXT);  // Restaura o tipo para TXT
            setServicos(servicos);  // Escreve no TXT
            remove("../bd/servicos.bin");  // Remove o arquivo binário
            return NULL;
        }
    }

    // Verifica se o tipo de arquivo atual é BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);  // Altera o tipo para TXT
            servicos = getServicos();
            setTipoArquivo(BIN);  // Restaura o tipo para BIN
            setServicos(servicos);  // Escreve no BIN
            remove("../bd/servicos.txt");  // Remove o arquivo TXT
            return NULL;
        }
    }

    // Verifica se o tipo de arquivo atual é MEM
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/servicos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);  // Altera para TXT
            servicos = getServicos();
            setTipoArquivo(MEM);  // Restaura para MEM
            remove("../bd/servicos.txt");  // Remove o TXT
            return servicos;
        }

        buffer = fopen("../bd/servicos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);  // Altera para BIN
            servicos = getServicos();
            setTipoArquivo(MEM);  // Restaura para MEM
            remove("../bd/servicos.bin");  // Remove o BIN
            return servicos;
        }
    }
    return NULL;
}

// Função para salvar os serviços no arquivo correspondente ao tipo atual
void setServicos(Servico *servicos) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.txt", "w");  // Abre arquivo TXT
        if (buffer != NULL) {
            escrever_arquivo_txt_servico(buffer, servicos);
            fclose(buffer);
            return;
        }
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.bin", "wb");  // Abre arquivo BIN
        if (buffer != NULL) {
            escrever_arquivo_bin_servico(buffer, servicos);
            fclose(buffer);
        }
    }
}

// Função para carregar os serviços do arquivo correspondente ao tipo atual
Servico *getServicos() {
    FILE *buffer;
    Servico *servicos = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/servicos.txt", "r");  // Abre arquivo TXT
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo servicos.txt!\n");
            return NULL;
        }
        servicos = ler_arquivo_txt_servico(buffer);
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/servicos.bin", "rb");  // Abre arquivo BIN
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

// Função para ler os serviços de um arquivo TXT
Servico *ler_arquivo_txt_servico(FILE *buffer) {
    int numServicos = 0;
    Servico *servicos = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro) {
            servicos = malloc(sizeof(Servico));
            isPrimeiro = FALSE;
        } else {
            servicos = realloc(servicos, (numServicos + 1) * sizeof(Servico));
        }

        if (!equals("<registro>\n", Linha) && !equals("</registro>\n", Linha)) {
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
                    i = 0;
                    numServicos++;
                    break;
            }
        }
    }

    qtdServicos = numServicos;  // Atualiza o número de serviços
    return servicos;
}

// Função para salvar serviços em um arquivo TXT
void escrever_arquivo_txt_servico(FILE *buffer, Servico *servicos) {
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
            servicos[i].ativo);

        if (escrevendo < 0) {
            printf("Erro ao escrever no arquivo.\n");
            return;
        }
    }
}

// Função para ler serviços de um arquivo BIN
Servico *ler_arquivo_bin_servico(FILE *buffer) {
    int i = 0;
    Servico *servicos = malloc(sizeof(Servico));

    while (fread(&servicos[i], sizeof(Servico), 1, buffer)) {
        i++;
        servicos = realloc(servicos, (i + 1) * sizeof(Servico));
    }

    qtdServicos = i;  // Atualiza a quantidade de serviços
    return servicos;
}

// Função para salvar serviços em um arquivo BIN
void escrever_arquivo_bin_servico(FILE *buffer, Servico *servicos) {
    for (int i = 0; i < getTamanhoServicos(); i++) {
        if (fwrite(&servicos[i], sizeof(Servico), 1, buffer) != 1) {
            printf("Erro ao escrever no arquivo binário\n");
            break;
        }
    }
}
