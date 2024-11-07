#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/funcionario.h"

int qtdFuncionarios = 0;

// Função para cadastrar Funcionario no arquivo
int getTamanhoFuncionarios() {
    return qtdFuncionarios;
}

void setTamanhoFuncionarios() {
    qtdFuncionarios++;
}

Funcionario *migraDadosFuncionario() {
    Funcionario *funcionarios = NULL;
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        // se o usuario deseja gravar os dados no txt
        buffer = fopen("../bd/funcionarios.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(BIN); // muda o tipo de arquivo para bin
            funcionarios = getFuncionarios();
            setTipoArquivo(TXT);// volta para o arquivo txt

            setFuncionarios(funcionarios);// escreve no txt
            free(buffer);
            remove("../bd/funcionarios.bin");
            return NULL;
        }
        fclose(buffer);
        free(buffer);
    }
    if (getTipoArquivo() == BIN) {
        //se o usuario deseja gravar em binario
        buffer = fopen("../bd/funcionarios.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            setTipoArquivo(TXT);
            funcionarios = getFuncionarios();
            setTipoArquivo(BIN);
            setFuncionarios(funcionarios);
            remove("../bd/funcionarios.txt");
            return NULL;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/funcionarios.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            //se antes ele tiver gravado os dados em txt
            setTipoArquivo(TXT); // muda o tipo de arquivo para
            funcionarios = getFuncionarios();
            setTipoArquivo(MEM);
            remove("../bd/funcionarios.txt");
            return funcionarios;
        }
        fclose(buffer);
        free(buffer);

        buffer = fopen("../bd/funcionarios.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            free(buffer);
            //se antes ele tiver gravado os dados em binario
            setTipoArquivo(BIN); // muda o tipo de arquivo para
            funcionarios = getFuncionarios();
            setTipoArquivo(MEM);
            remove("../bd/funcionarios.bin");
            return funcionarios;
        }
        fclose(buffer);
        free(buffer);
        return NULL;
    }
    return NULL;
}
void setFuncionarios(Funcionario *funcionarios) {
    FILE *buffer;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/funcionarios.txt", "w"); // Abre o arquivo corretamente
        if (buffer != NULL) {
            escrever_arquivo_txt_funcionario(buffer, funcionarios);
            fclose(buffer);
            return;
        }
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/funcionarios.bin", "wb"); // Abre o arquivo corretamente
        if (buffer != NULL) {
            escrever_arquivo_bin_funcionario(buffer, funcionarios);
            fclose(buffer);
        }
    }
}

Funcionario *getFuncionarios() {
    FILE *buffer;
    Funcionario *funcionarios = NULL;
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/funcionarios.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo funcionário.txt!\n");
            return NULL;
        }
        funcionarios = ler_arquivo_txt_funcionario(buffer);
    }
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/funcionarios.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            printf("Erro na abertura do arquivo funcionários.bin!\n");
            return NULL;
        }
        funcionarios = ler_arquivo_bin_funcionario(buffer);
    }
    if (getTipoArquivo() == MEM) {
        return NULL;
    }
    return funcionarios;
}
Funcionario *ler_arquivo_txt_funcionario(FILE *buffer) {
    int numFuncionarios = 0;
    Funcionario *funcionarios = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro == TRUE) {
            funcionarios = malloc(sizeof(Funcionario) * (numFuncionarios + 1));
            isPrimeiro = FALSE;
        }
        if (equals("<registro>\n", Linha) == FALSE
            && equals("</registro>\n", Linha) == FALSE) {
            if (isPrimeiro == FALSE) funcionarios = realloc(funcionarios, (numFuncionarios + 1) * sizeof(Funcionario));
            switch (i) {
                case 0:
                    funcionarios[numFuncionarios].codigo = atoi(removeTags(Linha));
                i++;
                break;
                case 1:
                    strcpy(funcionarios[numFuncionarios].nome, removeTags(Linha));
                i++;
                break;
                case 2:
                    strcpy(funcionarios[numFuncionarios].cpf, removeTags(Linha));
                i++;
                break;
                case 3:
                    strcpy(funcionarios[numFuncionarios].endereco, removeTags(Linha));
                i++;
                break;
                case 4:
                    strcpy(funcionarios[numFuncionarios].telefone, removeTags(Linha));
                i++;
                break;
                case 5:
                    strcpy(funcionarios[numFuncionarios].cargo, removeTags(Linha));
                i++;
                break;
                case 6:
                    funcionarios[numFuncionarios].salario = atof(removeTags(Linha));
                i++;
                break;
                case 7:
                    funcionarios[numFuncionarios].ativo = atoi(removeTags(Linha));
                i = 0; // Reinicia para ler o próximo funcionario
                numFuncionarios++;
                funcionarios = realloc(funcionarios, (numFuncionarios + 1) * sizeof(Funcionario));
                break;
               }
            }
    }
    qtdFuncionarios = numFuncionarios;
    return funcionarios;
}

void escrever_arquivo_txt_funcionario(FILE *buffer, Funcionario *funcionarios) {
    if (getTamanhoFuncionarios() == 0) setTamanhoFuncionarios(); // se acaso não tiver nenhum Funcionario cadastrado

    for (int i = 0; i < getTamanhoFuncionarios(); i++) {
        int escrevendo = fprintf(buffer,
                                 "<registro>\n"
                                 "<codigo>%d</codigo>\n"
                                 "<nome>%s</nome>\n"
                                 "<cpf>%s</cpf>\n"
                                 "<endereco>%s</endereco>\n"
                                 "<telefone>%s</telefone>\n"
                                 "<cargo>%s</cargo>\n"
                                 "<salario>%f</salario>\n"
                                 "<ativo>%d</ativo>\n"
                                 "</registro>\n",
                                 funcionarios[i].codigo,
                                 funcionarios[i].nome,
                                 funcionarios[i].cpf,
                                 funcionarios[i].endereco,
                                 funcionarios[i].telefone,
                                 funcionarios[i].cargo,
                                 funcionarios[i].salario,
                                 funcionarios[i].ativo
        );
        if (escrevendo < 0) {
            return;
        }
    }
}

Funcionario *ler_arquivo_bin_funcionario(FILE *buffer) {
    Funcionario *funcionarios = malloc(sizeof(Funcionario) * (getTamanhoFuncionarios() + 1));
    int i = 0;
    while (fread(&funcionarios[i], sizeof(Funcionario), 1, buffer)) {
        i++;
        setTamanhoFuncionarios();
        funcionarios = realloc(funcionarios, (getTamanhoFuncionarios() + 1) * sizeof(Funcionario));
    }
    return funcionarios;
}

void *escrever_arquivo_bin_funcionario(FILE *buffer, Funcionario *funcionarios) {
    printf("O tamanho do vetor e: %d\n", getTamanhoFuncionarios());
    for (int i = 0; i < getTamanhoFuncionarios(); i++) {
        if (fwrite(&funcionarios[i], sizeof(Funcionario), 1, buffer)) {
            printf("escreveu!\n");
        }
    }
}
