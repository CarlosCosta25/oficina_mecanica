#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/fornecedor.h"
#include "../bibliotecas/utils.h"

int qtdFornecedores = 0;
// Função para cadastrar cliente no arquivo
int getTamanhoFornecedores() {
    return qtdFornecedores;
}

void setTamanhoFornecedores() {
    qtdFornecedores++;
}

void setFornecedores(Fornecedor *fornecedores) {
    FILE *buffer;
    buffer = fopen("../bd/fornecedores.txt", "w"); // Abre o arquivo corretamente
    if (buffer == NULL) {
        printf("Erro na abertura do arquivo fornecedores.txt!\n");
        return;
    }
    if (getTamanhoFornecedores() == 0) setTamanhoFornecedores(); // se acaso não tiver nenhum fornecedor cadastrado

    // Loop sobre o número de fornecedores
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
            printf("Erro na escrita do arquivo fornecedores.txt\n");
            fclose(buffer);
            return;
        }
    }
    fclose(buffer);
}

Fornecedor *getFornecedores() {
    FILE *buffer = fopen("../bd/fornecedores.txt", "r");
    if (buffer == NULL) {
        printf("Erro na abertura do arquivo fornecedores.txt!\n");
        return NULL;
    }
    int numFornecedores = 0;
    Fornecedor *fornecedores = malloc(sizeof(Fornecedor) * (numFornecedores + 1));
    char Linha[100];
    int i = 0;
    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
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
                    setTamanhoFornecedores();
                    fornecedores = realloc(fornecedores, (numFornecedores + 1) * sizeof(Fornecedor));
                    break;
            }
        }
    }

    fclose(buffer);
    return fornecedores;
}
