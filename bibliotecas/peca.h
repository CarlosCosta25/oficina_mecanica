//
// Created by costa on 30/10/2024.
//

#ifndef PECA_H
#define PECA_H

#endif //PECA_H
#include "fornecedor.h"
typedef struct {
    int codigo;
    char descricao[100];
    char fabricante[50];
    int fornecedor;
    float preco_custo;
    float preco_venda;
    int estoque;
    int estoque_min;
    int ativo;
}Peca;

//model Peça
int getTamanhoPecas();
void setTamanhoPecas();
Peca *migraDadosPeca();
Peca *getPecas();
void setPecas(Peca *pecas);
Peca *ler_arquivo_txt_peca(FILE *buffer);
void escrever_arquivo_txt_peca(FILE *buffer, Peca *pecas);
Peca *ler_arquivo_bin_peca(FILE *buffer);
void escrever_arquivo_bin_peca(FILE *buffer, Peca *pecas);
int getTamanhoPecas();
void setTamanhoPecas();

//controller Peças
Peca* readPecas();
int createPeca(Peca **pecas, Peca *peca);
int showPeca(Peca *pecas, int codigo);
int updatePeca(Peca *pecas, Peca *peca);
int deletePeca(Peca* pecas, int codigo);
int buscaNovoIDPeca(Peca * pecas);

//view Peças
void menuPecas(Peca **pecas, Fornecedor *fornecedores);
void novaPeca(Peca **pecas, Fornecedor *fornecedores);
void mostrarPeca(Peca *pecas);
void editarPeca(Peca *pecas, Fornecedor *fornecedores);
void apagarPeca(Peca *pecas);
void mostrarTodasPecas(Peca *pecas);
