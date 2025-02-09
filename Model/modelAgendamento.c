#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
#include "../bibliotecas/utils.h"
#include "../bibliotecas/modulo2.h"

int qtdAgendamentos = 0;

// Função para obter a quantidade de agendamentos
int getTamanhoAgendamentos() {
    return qtdAgendamentos;
}

// Função para incrementar a quantidade de agendamentos
void setTamanhoAgendamentos() {
    qtdAgendamentos++;
}


// Função para migrar dados de agendamentos de TXT para BIN ou MEM
Agendamento *migraDadosAgendamento() {
    Agendamento *agendamentos = NULL;
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/agendamentos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN); // Muda o tipo de arquivo para binário
            agendamentos = getAgendamentos();
            if (agendamentos != NULL) {
                setTipoArquivo(TXT); // Volta para o arquivo TXT
                setAgendamentos(agendamentos); // Escreve no arquivo TXT
            }
            remove("../bd/agendamentos.bin");
            return NULL;
        }
    }

    if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/agendamentos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            agendamentos = getAgendamentos();
            if (agendamentos != NULL) {
                setTipoArquivo(BIN);
                setAgendamentos(agendamentos);
            }
            remove("../bd/agendamentos.txt");
            return NULL;
        }
    }

    if (getTipoArquivo() == MEM) {
        buffer = fopen("../bd/agendamentos.txt", "r");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(TXT);
            agendamentos = getAgendamentos();
            setTipoArquivo(MEM);
            remove("../bd/agendamentos.txt");
            return agendamentos;
        }

        buffer = fopen("../bd/agendamentos.bin", "rb");
        if (buffer != NULL) {
            fclose(buffer);
            setTipoArquivo(BIN);
            agendamentos = getAgendamentos();
            setTipoArquivo(MEM);
            remove("../bd/agendamentos.bin");
            return agendamentos;
        }
    }

    return NULL;
}

// Função para salvar os agendamentos em um arquivo
void setAgendamentos(Agendamento *agendamentos) {
    FILE *buffer;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/agendamentos.txt", "w");
        if (buffer != NULL) {
            escrever_arquivo_txt_agendamento(buffer, agendamentos);
            fclose(buffer);
        }
    } else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/agendamentos.bin", "wb");
        if (buffer != NULL) {
            //            escrever_arquivo_bin_agendamento(buffer, agendamentos);
            fclose(buffer);
        }
    }
}

// Função para obter os agendamentos do arquivo
Agendamento *getAgendamentos() {
    FILE *buffer;
    Agendamento *agendamentos = NULL;

    if (getTipoArquivo() == TXT) {
        buffer = fopen("../bd/agendamentos.txt", "r"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            return NULL;
        }
        agendamentos = ler_arquivo_txt_agendamento(buffer);
        fclose(buffer); // Certifique-se de fechar o arquivo após a leitura
    } else if (getTipoArquivo() == BIN) {
        buffer = fopen("../bd/agendamentos.bin", "rb"); // Abre o arquivo corretamente
        if (buffer == NULL) {
            return NULL;
        }
        //        agendamentos = ler_arquivo_bin_agendamento(buffer);
        fclose(buffer); // Certifique-se de fechar o arquivo após a leitura
    }

    return agendamentos;
}

// Função para ler o arquivo de agendamentos em TXT
Agendamento *ler_arquivo_txt_agendamento(FILE *buffer) {
    int numAgendamento = 0;
    Agendamento *agendamentos = NULL;
    char Linha[200];
    int i = 0;
    int isPrimeiro = 1;

    while (fgets(Linha, sizeof(Linha), buffer) != NULL) {
        if (isPrimeiro) {
            agendamentos = malloc(sizeof(Agendamento) * (numAgendamento + 1));
            if (agendamentos == NULL) {
                printf("Erro ao alocar memória.\n");
                return NULL;
            }
            isPrimeiro = 0;
        } else {
            agendamentos = realloc(agendamentos, (numAgendamento + 1) * sizeof(Agendamento));
            if (agendamentos == NULL) {
                printf("Erro ao realocar memória.\n");
                return NULL;
            }
        }

        if (equalsString(filtrarSoATag(Linha), "<registro>") != TRUE && equalsString(
                filtrarSoATag(Linha), "</registro>") != TRUE) {
            if (equalsString(filtrarSoATag(Linha), "</tabela>") == TRUE) break;
            switch (i) {
                case 0:
                    agendamentos[numAgendamento].codigo = atoi(removeTags(Linha));
                    i++;
                    break;
                case 1:
                    agendamentos[numAgendamento].quantidadeServicos = atoi(removeTags(Linha));
                    i++;
                    break;
                case 2:
                    char * dado = removeTags(Linha);
                    agendamentos[numAgendamento].codigosServicos =separaVetor(
                        dado, agendamentos[numAgendamento].quantidadeServicos);
                    i++;
                    break;
                case 3:
                    agendamentos[numAgendamento].codigoFuncionario = atoi(removeTags(Linha));
                    i++;
                    break;
                case 4:
                    agendamentos[numAgendamento].codigoCliente = atoi(removeTags(Linha));
                    i++;
                    break;
                case 5:
                    agendamentos[numAgendamento].codigoVeiculo = atoi(removeTags(Linha));
                    i++;
                    break;
                case 6:
                    agendamentos[numAgendamento].dataHora = atol(removeTags(Linha));
                    i++;
                    break;
                case 7:
                    agendamentos[numAgendamento].valorPrevisto = atof(removeTags(Linha));
                    i++;
                    break;
                case 8:
                    agendamentos[numAgendamento].ativo = atoi(removeTags(Linha));
                    i = 0;
                    numAgendamento++;
                    break;
            }
        }
    }
    qtdAgendamentos = numAgendamento;
    return agendamentos;
}

// Função para escrever o arquivo de agendamentos em TXT
void escrever_arquivo_txt_agendamento(FILE *buffer, Agendamento *agendamentos) {
    if (getTamanhoAgendamentos() == 0) setTamanhoAgendamentos();

    for (int i = 0; i < getTamanhoAgendamentos(); i++) {
        fprintf(buffer,
                "<registro>\n"
                "<codigo>%d</codigo>\n"
                "<quantidadeServicos>%d</quantidadeServicos>\n",
                agendamentos[i].codigo,
                agendamentos[i].quantidadeServicos
        );

        // Escreve os códigos dos serviços como uma lista separada por vírgulas
        fprintf(buffer, "<codigosServicos>");
        for (int j = 0; j < agendamentos[i].quantidadeServicos; j++) {
            fprintf(buffer, "%d,", agendamentos[i].codigosServicos[j]);
        }
        fprintf(buffer, "</codigosServicos>\n");

        fprintf(buffer,
                "<codigoFuncionario>%d</codigoFuncionario>\n"
                "<codigoCliente>%d</codigoCliente>\n"
                "<codigoVeiculo>%d</codigoVeiculo>\n"
                "<dataHora>%ld</dataHora>\n"
                "<valorPrevisto>%.2f</valorPrevisto>\n"
                "<ativo>%d</ativo>\n"
                "</registro>\n",
                agendamentos[i].codigoFuncionario,
                agendamentos[i].codigoCliente,
                agendamentos[i].codigoVeiculo,
                agendamentos[i].dataHora,
                agendamentos[i].valorPrevisto,
                agendamentos[i].ativo);
    }
}

// Função para ler o arquivo binário de agendamentos
Agendamento *ler_arquivo_bin_agendamento(FILE *buffer) {
    qtdAgendamentos = 0;
    fseek(buffer, 0, SEEK_END); // Move o ponteiro até o fim do arquivo
    qtdAgendamentos = (int) ftell(buffer) / sizeof(Agendamento); // Pega a quantidade de agendamentos
    fseek(buffer, 0, SEEK_SET); // Volta o ponteiro para o início do arquivo
    Agendamento *agendamentos = malloc(sizeof(Agendamento) * qtdAgendamentos); // Aloca a quantidade exata de agendamentos

    if (agendamentos == NULL) { // Verifica se a alocação foi bem-sucedida
        printf("Erro ao alocar memória para os agendamentos.\n");
        return NULL;
    }

    fread(agendamentos, sizeof(Agendamento), qtdAgendamentos, buffer); // Lê todos os agendamentos do arquivo e insere no vetor
    return agendamentos;
}

// Função para escrever o arquivo binário de agendamentos
void escrever_arquivo_bin_agendamento(FILE *buffer, Agendamento *agendamentos) {
    for (int i = 0; i < getTamanhoAgendamentos(); i++) {
        if (fwrite(&agendamentos[i], sizeof(Cliente), 1, buffer)) {
        }
    }
}
