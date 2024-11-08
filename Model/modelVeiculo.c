#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/veiculo.h"

int qtdVeiculos = 0;

// Função para cadastrar veiculo no arquivo
int getTamanhoVeiculos() {
    return qtdVeiculos;
}

void setTamanhoVeiculos() {
    qtdVeiculos++;
}

Veiculo *migraDadosVeiculo() {
    Veiculo *veiculos = NULL;
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        // se o usuario deseja gravar os dados no txt
        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para bin
            veiculos = getVeiculos();
            setTipoArquivo(TXT);// volta para o arquivo txt

            setVeiculos(veiculos);// escreve no txt
            free(buffer);
            remove("../bd/veiculos.bin");
            return NULL;
        }
        fclose(buffer);
        free(buffer);
    }
    if (getTipoArquivo() == BIN) {
        //se o usuario deseja gravar em binario
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT);
            veiculos = getVeiculos();
            setTipoArquivo(BIN);
            setVeiculos(veiculos);
            remove("../bd/veiculos.txt");
            return NULL;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            //se antes ele tiver gravado os dados em txt
            setTipoArquivo(TXT); // muda o tipo de arquivo para
            veiculos = getVeiculos();
            setTipoArquivo(MEM);
            remove("../bd/veiculos.txt");
            return veiculos;
        }
        fclose(buffer);
        free(buffer);

        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            //se antes ele tiver gravado os dados em binario
            setTipoArquivo(BIN); // muda o tipo de arquivo para
            veiculos = getVeiculos();
            setTipoArquivo(MEM);
            remove("../bd/veiculos.bin");
            return veiculos;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    return NULL;
}
void setVeiculos(Veiculo *veiculos) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "w"); // Abre o arquivo corretamente
        if (buffer != NULL) {
            escrever_arquivo_txt_veiculo(buffer, veiculos);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "wb"); // Abre o arquivo corretamente
        if (buffer != NULL) {
            escrever_arquivo_bin_veiculo(buffer, veiculos);
            fclose(buffer);
        }
    }
}

Veiculo *getVeiculos() {
    FILE *buffer;
    Veiculo *veiculos = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo veículos.txt!\n");
            return NULL;
        }
        veiculos = ler_arquivo_txt_veiculo(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo veículos.bin!\n");
            return NULL;
        }
        veiculos = ler_arquivo_bin_veiculo(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return veiculos;
}
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
        if (equals("<registro>\n", Linha) == FALSE
            && equals("</registro>\n", Linha) == FALSE) {
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

void escrever_arquivo_txt_veiculo(FILE *buffer, Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) setTamanhoVeiculos(); // se acaso não tiver nenhum veiculo cadastrado

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

void *escrever_arquivo_bin_veiculo(FILE *buffer, Veiculo *veiculos) {
    printf("O tamanho do vetor e: %d\n", getTamanhoVeiculos());
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (fwrite(&veiculos[i], sizeof(Veiculo), 1, buffer)) {
            printf("escreveu!\n");
        }
    }
}
