#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/oficina.h"

// Variável global para verificar se a oficina está registrada
int oficina = FALSE;

// Função que verifica se há uma oficina registrada
int hasOficina() {
    return oficina;
}

// Função para registrar uma oficina
void addOficina() {
    oficina = TRUE;
}

// Função para remover o registro da oficina
int removeOficina() {
    oficina = FALSE;
    return FALSE;
}

// Função que migra dados da oficina entre diferentes formatos de arquivo (TXT, BIN, MEM)
Oficina *migraDadosOficina() {
    Oficina *oficina = NULL;
    FILE *buffer;

    // Se o formato atual for TXT, converte os dados do binário para texto
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/oficina.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            oficina = getOficina();
            setTipoArquivo(TXT);
            setOficina(oficina);
            remove("../bd/oficina.bin");
            return NULL;
        }
    }
    // Se o formato atual for BIN, converte os dados de texto para binário
    else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/oficina.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            oficina = getOficina();
            setTipoArquivo(BIN);
            setOficina(oficina);
            remove("../bd/oficina.txt");
            return NULL;
        }
    }
    // Se os dados estão na memória (MEM), verifica os formatos disponíveis para migração
    else if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/oficina.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            oficina = getOficina();
            setTipoArquivo(MEM);
            remove("../bd/oficina.txt");
            addOficina();
            return oficina;
        }

        buffer = fopen("../bd/oficina.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            oficina = getOficina();
            setTipoArquivo(MEM);
            remove("../bd/oficina.bin");
            addOficina();
            return oficina;
        }
    }

    buffer = NULL;
    free(buffer);
    return NULL;
}

// Função para salvar os dados da oficina no formato atual
void setOficina(Oficina *oficina) {
    FILE *buffer;
    // Salva no formato texto
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/oficina.txt", "w");
        if (buffer != NULL) {
            escrever_arquivo_txt_oficina(buffer, oficina);
            fclose(buffer);
            return;
        }
    }
    // Salva no formato binário
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/oficina.bin", "wb");
        if (buffer != NULL) {
            escrever_arquivo_bin_oficina(buffer, oficina);
            fclose(buffer);
        }
    }
}

// Função para carregar os dados da oficina do arquivo
Oficina *getOficina() {
    FILE *buffer;
    Oficina *oficina = NULL;

    // Carrega do formato texto
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/oficina.txt", "r");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo oficina.txt!\n");
            free(oficina);
            return NULL;
        }
        oficina = ler_arquivo_txt_oficina(buffer);
    }
    // Carrega do formato binário
    else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/oficina.bin", "rb");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo oficina.bin!\n");
            free(oficina);
            return NULL;
        }
        oficina = ler_arquivo_bin_oficina(buffer);
    }
    // Dados na memória, retorna NULL
    else if (getTipoArquivo() == MEM) {
        return NULL;
    }

    fclose(buffer);
    buffer = NULL;
    return oficina;
}

// Função para ler os dados da oficina a partir de um arquivo texto
Oficina *ler_arquivo_txt_oficina(FILE *buffer) {
    int i = 0;
    int isPrimeiro = TRUE;
    Oficina *oficina = NULL;
    char linha[200];

    while (fgets(linha, sizeof(linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            oficina = malloc(sizeof(Oficina));
            if (oficina == NULL) {
                printf("Erro ao alocar memória para oficina\n");
                return NULL;
            }
            isPrimeiro = FALSE;
        }
        if (equals("<registro>\n", linha) == FALSE && equals("</registro>\n", linha) == FALSE) {
            switch (i) {
                case 0:
                    strcpy(oficina->nome, removeTags(linha));
                    i++;
                    break;
                case 1:
                    strcpy(oficina->cpf_cnpj, removeTags(linha));
                    i++;
                    break;
                case 2:
                    strcpy(oficina->endereco, removeTags(linha));
                    i++;
                    break;
                case 3:
                    strcpy(oficina->telefone, removeTags(linha));
                    i++;
                    break;
                case 4:
                    strcpy(oficina->email, removeTags(linha));
                    i++;
                    break;
                case 5:
                    oficina->porcentagem_lucro = atof(removeTags(linha));
                    addOficina();
                    i = 0;
                    break;
            }
        }
    }

    return oficina;
}

// Função para salvar os dados da oficina em um arquivo texto
void escrever_arquivo_txt_oficina(FILE *buffer, Oficina *oficina) {
    fprintf(buffer,
            "<registro>\n"
            "<nome>%s</nome>\n"
            "<cpf_cnpj>%s</cpf_cnpj>\n"
            "<endereco>%s</endereco>\n"
            "<telefone>%s</telefone>\n"
            "<email>%s</email>\n"
            "<porcentagem_lucro>%.2f</porcentagem_lucro>\n"
            "</registro>\n",
            oficina->nome,
            oficina->cpf_cnpj,
            oficina->endereco,
            oficina->telefone,
            oficina->email,
            oficina->porcentagem_lucro);
    addOficina();
}

// Função para carregar os dados da oficina a partir de um arquivo binário
Oficina *ler_arquivo_bin_oficina(FILE *buffer) {
    Oficina *oficina = malloc(sizeof(Oficina));
    if (oficina == NULL) {
        printf("Erro ao alocar memória para oficina\n");
        return NULL;
    }

    if (fread(oficina, sizeof(Oficina), 1, buffer) != 1) {
        free(oficina);
        return NULL;
    }

    return oficina;
}

// Função para salvar os dados da oficina em um arquivo binário
void escrever_arquivo_bin_oficina(FILE *buffer, Oficina *oficina) {
    fwrite(oficina, sizeof(Oficina), 1, buffer);
    addOficina();
}

// Função para deletar arquivos de dados da oficina
void delete_arq_oficina() {
    if (getTipoArquivo() == TXT) {
        remove("../bd/oficina.txt");
        fopen("../bd/oficina.txt", "w");
    }
    if (getTipoArquivo() == BIN) {
        remove("../bd/oficina.bin");
        fopen("../bd/oficina.bin", "bw");
    }
}
