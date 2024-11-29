#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/cliente.h"

// Variável global para rastrear o número de clientes cadastrados
int qtdClientes = 0;

// Função para retornar o tamanho atual do vetor de clientes
int getTamanhoClientes() {
    return qtdClientes;
}

// Incrementa o contador global de clientes
void setTamanhoClientes() {
    qtdClientes++;
}

/**
 * Função para migrar dados de clientes entre diferentes formatos de armazenamento (TXT, BIN ou MEM).
 * Retorna um ponteiro para os dados migrados ou NULL se não for necessário migrar.
 */
Cliente *migraDadosCliente() {
    Cliente *clientes = NULL;
    FILE *buffer;

    // Caso o tipo de arquivo seja TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/clientes.bin", "rb"); // Tenta abrir o arquivo BIN
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN);      // Muda o tipo para BIN
            clientes = getClientes(); // Lê os clientes do BIN
            setTipoArquivo(TXT);      // Volta para TXT
            setClientes(clientes);    // Escreve os clientes no TXT
            remove("../bd/clientes.bin"); // Remove o BIN
            return NULL;
        }
        fclose(buffer);
        free(buffer);
    }

    // Caso o tipo de arquivo seja BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/clientes.txt", "r"); // Tenta abrir o arquivo TXT
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT);      // Muda para TXT
            clientes = getClientes(); // Lê os clientes do TXT
            setTipoArquivo(BIN);      // Volta para BIN
            setClientes(clientes);    // Escreve os clientes no BIN
            remove("../bd/clientes.txt"); // Remove o TXT
            return NULL;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }

    // Caso o tipo de armazenamento seja MEM
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/clientes.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT); // Muda para TXT
            clientes = getClientes();
            setTipoArquivo(MEM); // Volta para MEM
            remove("../bd/clientes.txt");
            return clientes;
        }

        buffer = fopen("../bd/clientes.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN); // Muda para BIN
            clientes = getClientes();
            setTipoArquivo(MEM); // Volta para MEM
            remove("../bd/clientes.bin");
            return clientes;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
}

/**
 * Salva os dados de clientes no formato especificado (TXT ou BIN).
 */
void setClientes(Cliente *clientes) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/clientes.txt", "w"); // Abre para escrita no TXT
        if (buffer != NULL) {
            escrever_arquivo_txt_cliente(buffer, clientes);
            fclose(buffer);
            return;
        }
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/clientes.bin", "wb"); // Abre para escrita no BIN
        if (buffer != NULL) {
            escrever_arquivo_bin_cliente(buffer, clientes);
            fclose(buffer);
        }
    }
}

/**
 * Lê os dados de clientes do formato especificado (TXT ou BIN).
 * Retorna um ponteiro para o array de clientes.
 */
Cliente *getClientes() {
    FILE *buffer;
    Cliente *clientes = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/clientes.txt", "r");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo clientes.txt!\n");
            return NULL;
        }
        clientes = ler_arquivo_txt_cliente(buffer);
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/clientes.bin", "rb");
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo clientes.bin!\n");
            return NULL;
        }
        clientes = ler_arquivo_bin_cliente(buffer);
    }

    if (getTipoArquivo() == MEM) {
        return NULL; // Não há manipulação de dados diretamente na memória
    }

    return clientes;
}

/**
 * Lê os clientes de um arquivo TXT e retorna um array dinâmico de `Cliente`.
 */
Cliente *ler_arquivo_txt_cliente(FILE *buffer) {
    int numClientes = 0;
    Cliente *clientes = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        // Realoca o array de clientes conforme necessário
        if (isPrimeiro == TRUE) {
            clientes = malloc(sizeof(Cliente));
            isPrimeiro = FALSE;
        } else {
            clientes = realloc(clientes, (numClientes + 1) * sizeof(Cliente));
        }

        // Preenche os dados do cliente a partir do arquivo
        if (!equals("<registro>\n", Linha) && !equals("</registro>\n", Linha)) {
            switch (i) {
                case 0:
                    clientes[numClientes].codigo = atoi(removeTags(Linha));
                    i++;
                    break;
                case 1:
                    strcpy(clientes[numClientes].nome, removeTags(Linha));
                    i++;
                    break;
                case 2:
                    strcpy(clientes[numClientes].cpf_cnpj, removeTags(Linha));
                    i++;
                    break;
                case 3:
                    strcpy(clientes[numClientes].endereco, removeTags(Linha));
                    i++;
                    break;
                case 4:
                    strcpy(clientes[numClientes].telefone, removeTags(Linha));
                    i++;
                    break;
                case 5:
                    strcpy(clientes[numClientes].email, removeTags(Linha));
                    i++;
                    break;
                case 6:
                    clientes[numClientes].ativo = atoi(removeTags(Linha));
                    i = 0;
                    numClientes++;
                    break;
            }
        }
    }

    qtdClientes = numClientes; // Atualiza a quantidade de clientes
    return clientes;
}

/**
 * Escreve os dados de clientes em um arquivo TXT.
 */
void escrever_arquivo_txt_cliente(FILE *buffer, Cliente *clientes) {
    for (int i = 0; i < getTamanhoClientes(); i++) {
        fprintf(buffer,
                "<registro>\n"
                "<codigo>%d</codigo>\n"
                "<nome>%s</nome>\n"
                "<cpf_cnpj>%s</cpf_cnpj>\n"
                "<endereco>%s</endereco>\n"
                "<telefone>%s</telefone>\n"
                "<email>%s</email>\n"
                "<ativo>%d</ativo>\n"
                "</registro>\n",
                clientes[i].codigo, clientes[i].nome, clientes[i].cpf_cnpj,
                clientes[i].endereco, clientes[i].telefone, clientes[i].email,
                clientes[i].ativo);
    }
}

/**
 * Lê os clientes de um arquivo BIN e retorna um array dinâmico de `Cliente`.
 */
Cliente *ler_arquivo_bin_cliente(FILE *buffer) {
    Cliente *clientes = malloc(sizeof(Cliente));
    int i = 0;

    while (fread(&clientes[i], sizeof(Cliente), 1, buffer)) {
        i++;
        setTamanhoClientes();
        clientes = realloc(clientes, (getTamanhoClientes() + 1) * sizeof(Cliente));
    }

    return clientes;
}

/**
 * Escreve os dados de clientes em um arquivo BIN.
 */
void *escrever_arquivo_bin_cliente(FILE *buffer, Cliente *clientes) {
    for (int i = 0; i < getTamanhoClientes(); i++) {
        fwrite(&clientes[i], sizeof(Cliente), 1, buffer);
    }
}

