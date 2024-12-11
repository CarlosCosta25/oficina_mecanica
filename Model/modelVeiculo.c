#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h" // Biblioteca utilitária
#include "../bibliotecas/veiculo.h" // Estrutura e funções relacionadas a "Veiculo"

// Variável global para armazenar a quantidade de veículos
int qtdVeiculos = 0;

// Função para obter a quantidade atual de veículos
int getTamanhoVeiculos() {
    return qtdVeiculos;
}

// Função para incrementar a quantidade de veículos
void setTamanhoVeiculos() {
    qtdVeiculos++;
}

// Função para migrar dados de veículos entre os formatos de arquivo
Veiculo *migraDadosVeiculo() {
    Veiculo *veiculos = NULL;
    FILE *buffer;

    // Caso o formato de arquivo seja TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN); // Troca para formato BIN
            veiculos = getVeiculos(); // Lê os veículos
            setTipoArquivo(TXT); // Retorna para formato TXT

            setVeiculos(veiculos); // Escreve no TXT
            free(buffer);
            remove("../bd/veiculos.bin"); // Remove o arquivo BIN
            return NULL;
        }
        fclose(buffer);
        free(buffer);
    }

    // Caso o formato de arquivo seja BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT); // Troca para formato TXT
            veiculos = getVeiculos(); // Lê os veículos
            setTipoArquivo(BIN); // Retorna para formato BIN
            setVeiculos(veiculos); // Escreve no BIN
            remove("../bd/veiculos.txt"); // Remove o arquivo TXT
            return NULL;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }

    // Caso o formato de arquivo seja MEM
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT); // Troca para formato TXT
            veiculos = getVeiculos(); // Lê os veículos
            setTipoArquivo(MEM); // Retorna para formato MEM
            remove("../bd/veiculos.txt"); // Remove o arquivo TXT
            return veiculos;
        }
        fclose(buffer);
        free(buffer);

        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN); // Troca para formato BIN
            veiculos = getVeiculos(); // Lê os veículos
            setTipoArquivo(MEM); // Retorna para formato MEM
            remove("../bd/veiculos.bin"); // Remove o arquivo BIN
            return veiculos;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    return NULL;
}

// Função para gravar os veículos no arquivo especificado (TXT ou BIN)
void setVeiculos(Veiculo *veiculos) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "w"); // Abre o arquivo TXT
        if (buffer != NULL) {
            escrever_arquivo_txt_veiculo(buffer, veiculos); // Escreve no TXT
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "wb"); // Abre o arquivo BIN
        if (buffer != NULL) {
            escrever_arquivo_bin_veiculo(buffer, veiculos); // Escreve no BIN
            fclose(buffer);
        }
    }
}

// Função para ler os veículos do arquivo especificado (TXT ou BIN)
Veiculo *getVeiculos() {
    FILE *buffer;
    Veiculo *veiculos = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "r"); // Abre o arquivo TXT
        if (buffer == NULL) {
            return NULL;
        }
        veiculos = ler_arquivo_txt_veiculo(buffer); // Lê do TXT
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "rb"); // Abre o arquivo BIN
        if (buffer == NULL) {
            return NULL;
        }
        veiculos = ler_arquivo_bin_veiculo(buffer); // Lê do BIN
    }
    if (getTipoArquivo() == MEM) {
        return NULL; // Retorna NULL se o formato for MEM
    }
    return veiculos;
}

// Função para ler veículos de um arquivo TXT
Veiculo *ler_arquivo_txt_veiculo(FILE *buffer) {
    int numVeiculos = 0;
    Veiculo *veiculos = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            veiculos = malloc(sizeof(Veiculo) * (numVeiculos + 1));
            isPrimeiro = FALSE;
        }
        if (equals("<registro>\n", Linha) == FALSE && equals("</registro>\n", Linha) == FALSE) {
            if (isPrimeiro == FALSE) veiculos = realloc(veiculos, (numVeiculos + 1) * sizeof(Veiculo));
            switch (i) {
                case 0:
                    veiculos[numVeiculos].codigo = atoi(removeTags(Linha));
                i++;
                break;
                case 1:
                    strcpy(veiculos[numVeiculos].placa, removeTags(Linha));
                i++;
                break;
                case 2:
                    strcpy(veiculos[numVeiculos].modelo, removeTags(Linha));
                i++;
                break;
                case 3:
                    strcpy(veiculos[numVeiculos].marca, removeTags(Linha));
                i++;
                break;
                case 4:
                    veiculos[numVeiculos].anofabricacao = atoi(removeTags(Linha));
                i++;
                break;
                case 5:
                    strcpy(veiculos[numVeiculos].chassi, removeTags(Linha));
                i++;
                break;
                case 6:
                    veiculos[numVeiculos].ativo = atoi(removeTags(Linha));
                i = 0; // Reinicia para ler o próximo veiculo
                numVeiculos++;
                veiculos = realloc(veiculos, (numVeiculos + 1) * sizeof(Veiculo));
                break;
               }
            }
    }
    qtdVeiculos = numVeiculos;
    return veiculos;
}

// Função para escrever veículos em um arquivo TXT
void escrever_arquivo_txt_veiculo(FILE *buffer, Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) setTamanhoVeiculos(); // Verifica se há veículos cadastrados

    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        int escrevendo = fprintf(buffer,
                                 "<registro>\n"
                                 "<codigo>%d</codigo>\n"
                                 "<placa>%s</placa>\n"
                                 "<modelo>%s</modelo>\n"
                                 "<marca>%s</marca>\n"
                                 "<anofabricacao>%d</anofabricacao>\n"
                                 "<chassi>%s</chassi>\n"
                                 "<ativo>%d</ativo>\n"
                                 "</registro>\n",
                                 veiculos[i].codigo,
                                 veiculos[i].placa,
                                 veiculos[i].modelo,
                                 veiculos[i].marca,
                                 veiculos[i].anofabricacao,
                                 veiculos[i].chassi,
                                 veiculos[i].ativo
        );
        if (escrevendo < 0) {
            return;
        }
    }
}

// Função para ler veículos de um arquivo BIN
Veiculo *ler_arquivo_bin_veiculo(FILE *buffer) {
    Veiculo *veiculos = malloc(sizeof(Veiculo) * (getTamanhoVeiculos() + 1));
    int i = 0;
    while (fread(&veiculos[i], sizeof(Veiculo), 1, buffer)) {
        i++;
        setTamanhoVeiculos();
        veiculos = realloc(veiculos, (getTamanhoVeiculos() + 1) * sizeof(Veiculo));
    }
    return veiculos;
}

// Função para escrever veículos em um arquivo BIN
void *escrever_arquivo_bin_veiculo(FILE *buffer, Veiculo *veiculos) {
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (fwrite(&veiculos[i], sizeof(Veiculo), 1, buffer)) {
            // Gravação bem-sucedida
        }
    }
}
