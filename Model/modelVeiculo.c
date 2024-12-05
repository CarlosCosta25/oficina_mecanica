#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"  // Funções utilitárias, como removeTags e equals
#include "../bibliotecas/veiculo.h"  // Definições de estrutura Veiculo

int qtdVeiculos = 0;  // Variável global para manter o controle da quantidade de veículos

// Função para obter a quantidade atual de veículos
int getTamanhoVeiculos() {
    return qtdVeiculos;
}

// Função para incrementar o número de veículos
void setTamanhoVeiculos() {
    qtdVeiculos++;
}

// Função para migrar dados entre os diferentes tipos de armazenamento (TXT, BIN, MEM)
Veiculo *migraDadosVeiculo() {
    Veiculo *veiculos = NULL;
    FILE *buffer;
    // Se o tipo de arquivo for TXT, migra para binário
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN);  // Muda para BIN
            veiculos = getVeiculos();  // Obtém os veículos
            setTipoArquivo(TXT);  // Volta para TXT
            setVeiculos(veiculos);  // Salva os veículos no formato TXT
            free(buffer);
            remove("../bd/veiculos.bin");  // Remove o arquivo binário
            return NULL;
        }
        fclose(buffer);
        free(buffer);
    }
    // Se o tipo de arquivo for BIN, migra para TXT
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT);  // Muda para TXT
            veiculos = getVeiculos();  // Obtém os veículos
            setTipoArquivo(BIN);  // Muda para BIN
            setVeiculos(veiculos);  // Salva os veículos no formato BIN
            remove("../bd/veiculos.txt");  // Remove o arquivo TXT
            return NULL;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    // Se o tipo de arquivo for MEM, verifica e migra os dados para a memória
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/veiculos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT);  // Muda para TXT
            veiculos = getVeiculos();  // Obtém os veículos
            setTipoArquivo(MEM);  // Muda para MEM
            remove("../bd/veiculos.txt");  // Remove o arquivo TXT
            return veiculos;
        }
        fclose(buffer);
        free(buffer);

        buffer = fopen("../bd/veiculos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN);  // Muda para BIN
            veiculos = getVeiculos();  // Obtém os veículos
            setTipoArquivo(MEM);  // Muda para MEM
            remove("../bd/veiculos.bin");  // Remove o arquivo BIN
            return veiculos;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    return NULL;
}

// Função para definir os veículos no arquivo
void setVeiculos(Veiculo *veiculos) {
    FILE *buffer;
    // Se o tipo de arquivo for TXT, salva os veículos no formato TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "w");  // Abre o arquivo TXT para escrita
        if (buffer != NULL) {
            escrever_arquivo_txt_veiculo(buffer, veiculos);  // Escreve os veículos no arquivo TXT
            fclose(buffer);
            return;
        }
    }
    // Se o tipo de arquivo for BIN, salva os veículos no formato BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "wb");  // Abre o arquivo BIN para escrita
        if (buffer != NULL) {
            escrever_arquivo_bin_veiculo(buffer, veiculos);  // Escreve os veículos no arquivo BIN
            fclose(buffer);
        }
    }
}

// Função para obter os veículos armazenados no arquivo
Veiculo *getVeiculos() {
    FILE *buffer;
    Veiculo *veiculos = NULL;
    // Se o tipo de arquivo for TXT, lê os veículos do formato TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/veiculos.txt", "r");  // Abre o arquivo TXT para leitura
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo veículos.txt!\n");
            return NULL;
        }
        veiculos = ler_arquivo_txt_veiculo(buffer);  // Lê os veículos do arquivo TXT
    }
    // Se o tipo de arquivo for BIN, lê os veículos do formato BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/veiculos.bin", "rb");  // Abre o arquivo BIN para leitura
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo veículos.bin!\n");
            return NULL;
        }
        veiculos = ler_arquivo_bin_veiculo(buffer);  // Lê os veículos do arquivo BIN
    }
    // Se o tipo de arquivo for MEM, retorna NULL (dados são em memória)
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return veiculos;
}

// Função para ler os veículos do arquivo TXT
Veiculo *ler_arquivo_txt_veiculo(FILE *buffer) {
    int numVeiculos = 0;
    Veiculo *veiculos = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    // Lê cada linha do arquivo TXT e converte para a estrutura Veiculo
    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            veiculos = malloc(sizeof(Veiculo) * (numVeiculos + 1));  // Aloca espaço para o primeiro veículo
            isPrimeiro = FALSE;
        }
        // Processa cada linha para preencher os campos da estrutura Veiculo
        if (equals("<registro>\n", Linha) == FALSE && equals("</registro>\n", Linha) == FALSE) {
            if (isPrimeiro == FALSE) veiculos = realloc(veiculos, (numVeiculos + 1) * sizeof(Veiculo));  // Realoca memória conforme necessário
            switch (i) {
                case 0:
                    veiculos[numVeiculos].codigo = atoi(removeTags(Linha));  // Converte o código
                    i++;
                    break;
                case 1:
                    strcpy(veiculos[numVeiculos].placa, removeTags(Linha));  // Copia a placa
                    i++;
                    break;
                case 2:
                    strcpy(veiculos[numVeiculos].modelo, removeTags(Linha));  // Copia o modelo
                    i++;
                    break;
                case 3:
                    strcpy(veiculos[numVeiculos].marca, removeTags(Linha));  // Copia a marca
                    i++;
                    break;
                case 4:
                    veiculos[numVeiculos].anofabricacao = atoi(removeTags(Linha));  // Converte o ano de fabricação
                    i++;
                    break;
                case 5:
                    strcpy(veiculos[numVeiculos].chassi, removeTags(Linha));  // Copia o número do chassi
                    i++;
                    break;
                case 6:
                    veiculos[numVeiculos].ativo = atoi(removeTags(Linha));  // Define se o veículo está ativo
                    i = 0;  // Reinicia o contador
                    numVeiculos++;  // Incrementa o contador de veículos
                    veiculos = realloc(veiculos, (numVeiculos + 1) * sizeof(Veiculo));  // Realoca memória
                    break;
            }
        }
    }
    qtdVeiculos = numVeiculos;  // Atualiza a quantidade de veículos
    return veiculos;
}

// Função para escrever os veículos no arquivo TXT
void escrever_arquivo_txt_veiculo(FILE *buffer, Veiculo *veiculos) {
    if (getTamanhoVeiculos() == 0) setTamanhoVeiculos();  // Garante que pelo menos um veículo esteja registrado

    // Escreve todos os veículos no arquivo TXT
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

// Função para ler os veículos do arquivo BIN
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

// Função para escrever os veículos no arquivo BIN
void *escrever_arquivo_bin_veiculo(FILE *buffer, Veiculo *veiculos) {
    printf("O tamanho do vetor é: %d\n", getTamanhoVeiculos());
    // Escreve todos os veículos no arquivo BIN
    for (int i = 0; i < getTamanhoVeiculos(); i++) {
        if (fwrite(&veiculos[i], sizeof(Veiculo), 1, buffer)) {
            printf("Escreveu com sucesso!\n");
        }
    }
}
