#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/oficina.h"

int oficina = FALSE;

int hasOficina() {
    return oficina;
}

void addOficina() {
    oficina = TRUE;
}
int removeOficina() {
    oficina = FALSE;
    return FALSE;
}

Oficina *migraDadosOficina() {
    Oficina *oficina = NULL;
    FILE *buffer;

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
    } else if (getTipoArquivo() == BIN) {
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
    } else if (getTipoArquivo() == MEM) {
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
void setOficina(Oficina *oficina) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/oficina.txt", "w"); // Abre o arquivo para escrita de texto
        if (buffer != NULL) {
            escrever_arquivo_txt_oficina(buffer, oficina);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/oficina.bin", "wb"); // Abre o arquivo para escrita binária
        if (buffer != NULL) {
            escrever_arquivo_bin_oficina(buffer, oficina);
            fclose(buffer);
        }
    }
}


Oficina *getOficina() {
    FILE *buffer;
    Oficina *oficina = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/oficina.txt", "r");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo oficina.txt!\n");
            free(oficina);
            return NULL;
        }
        oficina = ler_arquivo_txt_oficina(buffer);
    } else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/oficina.bin", "rb");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo oficina.bin!\n");
            free(oficina);
            return NULL;
        }
        oficina = ler_arquivo_bin_oficina(buffer);
    } else if (getTipoArquivo() == MEM) {
        return NULL;
    }

    fclose(buffer);
    buffer = NULL;
    return oficina;
}

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

void escrever_arquivo_bin_oficina(FILE *buffer, Oficina *oficina) {
    fwrite(oficina, sizeof(Oficina), 1, buffer);
    addOficina();
}
void delete_arq_oficina() {
    if(getTipoArquivo() == TXT) {
        remove("../bd/oficina.txt");
        fopen("../bd/oficina.txt", "w");

    }
    if(getTipoArquivo() == BIN) {
        remove("../bd/oficina.bin");
        fopen("../bd/oficina.bin", "bw");
    }
}

