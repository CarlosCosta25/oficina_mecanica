#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/funcionario.h"

int qtdFuncionarios = 0; // Variável global para armazenar a quantidade de funcionários registrados

// Retorna a quantidade atual de funcionários
int getTamanhoFuncionarios() {
    return qtdFuncionarios;
}

// Incrementa o contador global de funcionários
void setTamanhoFuncionarios() {
    qtdFuncionarios++;
}

// Realiza a migração de dados entre diferentes tipos de arquivos ou para memória
Funcionario *migraDadosFuncionario() {
    Funcionario *funcionarios = NULL;
    FILE *buffer;

    // Verifica se o formato de arquivo é TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/funcionarios.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // Altera o tipo de arquivo para BIN
            funcionarios = getFuncionarios(); // Lê os dados em formato BIN
            setTipoArquivo(TXT); // Retorna ao formato TXT
            setFuncionarios(funcionarios); // Grava os dados no TXT
            remove("../bd/funcionarios.bin"); // Remove o arquivo BIN
            return NULL;
        }
    }
    // Verifica se o formato de arquivo é BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/funcionarios.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            funcionarios = getFuncionarios(); // Lê os dados em formato TXT
            setTipoArquivo(BIN); // Retorna ao formato BIN
            setFuncionarios(funcionarios); // Grava os dados no BIN
            remove("../bd/funcionarios.txt"); // Remove o arquivo TXT
            return NULL;
        }
    }
    // Verifica se os dados estão em memória
    if (getTipoArquivo() == MEM) {
        // Tenta migrar dados do TXT
        buffer = fopen("../bd/funcionarios.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            funcionarios = getFuncionarios();
            setTipoArquivo(MEM);
            remove("../bd/funcionarios.txt");
            return funcionarios;
        }
        // Tenta migrar dados do BIN
        buffer = fopen("../bd/funcionarios.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            funcionarios = getFuncionarios();
            setTipoArquivo(MEM);
            remove("../bd/funcionarios.bin");
            return funcionarios;
        }
    }
    return NULL;
}

// Grava os funcionários em arquivo (TXT ou BIN)
void setFuncionarios(Funcionario *funcionarios) {
    FILE *buffer;

    // Gravação em TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/funcionarios.txt", "w");
        if (buffer != NULL) {
            escrever_arquivo_txt_funcionario(buffer, funcionarios);
            fclose(buffer);
        }
    }
    // Gravação em BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/funcionarios.bin", "wb");
        if (buffer != NULL) {
            escrever_arquivo_bin_funcionario(buffer, funcionarios);
            fclose(buffer);
        }
    }
}

// Lê os funcionários de um arquivo (TXT ou BIN)
Funcionario *getFuncionarios() {
    FILE *buffer;
    Funcionario *funcionarios = NULL;

    // Leitura do TXT
    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/funcionarios.txt", "r");
        if (buffer != NULL) {
            funcionarios = ler_arquivo_txt_funcionario(buffer);
            fclose(buffer);
        }
    }
    // Leitura do BIN
    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/funcionarios.bin", "rb");
        if (buffer != NULL) {
            funcionarios = ler_arquivo_bin_funcionario(buffer);
            fclose(buffer);
        }
    }
    // Dados em memória retornam NULL
    return funcionarios;
}

// Lê os dados de um arquivo TXT e retorna um array de funcionários
Funcionario *ler_arquivo_txt_funcionario(FILE *buffer) {
    int numFuncionarios = 0;
    Funcionario *funcionarios = NULL;
    char Linha[100];
    int i = 0;
    int isPrimeiro = TRUE;

    // Lê cada linha do arquivo
    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro) {
            funcionarios = malloc(sizeof(Funcionario));
            isPrimeiro = FALSE;
        } else {
            funcionarios = realloc(funcionarios, (numFuncionarios + 1) * sizeof(Funcionario));
        }
        // Popula o funcionário com base na ordem dos campos
        switch (i) {
            case 0: funcionarios[numFuncionarios].codigo = atoi(removeTags(Linha)); break;
            case 1: strcpy(funcionarios[numFuncionarios].nome, removeTags(Linha)); break;
            case 2: strcpy(funcionarios[numFuncionarios].cpf, removeTags(Linha)); break;
            case 3: strcpy(funcionarios[numFuncionarios].endereco, removeTags(Linha)); break;
            case 4: strcpy(funcionarios[numFuncionarios].telefone, removeTags(Linha)); break;
            case 5: strcpy(funcionarios[numFuncionarios].cargo, removeTags(Linha)); break;
            case 6: funcionarios[numFuncionarios].salario = atof(removeTags(Linha)); break;
            case 7: funcionarios[numFuncionarios].ativo = atoi(removeTags(Linha));
                    i = -1; numFuncionarios++; break;
        }
        i++;
    }
    qtdFuncionarios = numFuncionarios;
    return funcionarios;
}

// Grava os dados de funcionários no formato TXT
void escrever_arquivo_txt_funcionario(FILE *buffer, Funcionario *funcionarios) {
    for (int i = 0; i < getTamanhoFuncionarios(); i++) {
        fprintf(buffer,
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
                funcionarios[i].ativo);
    }
}

// Lê os dados de um arquivo BIN e retorna um array de funcionários
Funcionario *ler_arquivo_bin_funcionario(FILE *buffer) {
    Funcionario *funcionarios = malloc(sizeof(Funcionario));
    int i = 0;
    while (fread(&funcionarios[i], sizeof(Funcionario), 1, buffer)) {
        i++;
        funcionarios = realloc(funcionarios, (i + 1) * sizeof(Funcionario));
        setTamanhoFuncionarios();
    }
    return funcionarios;
}

// Grava os dados de funcionários no formato BIN
void *escrever_arquivo_bin_funcionario(FILE *buffer, Funcionario *funcionarios) {
    for (int i = 0; i < getTamanhoFuncionarios(); i++) {
        fwrite(&funcionarios[i], sizeof(Funcionario), 1, buffer);
    }
}
