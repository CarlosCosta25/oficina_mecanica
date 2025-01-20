#ifndef ESTOQUE_H
#define ESTOQUE_H

#include "peca.h"


// Estrutura para registrar compras de peças
typedef struct compraPeca {
    int codigo;               // Código da compra
    int codPeca;              // Código da peça
    int qtdPecas;             // Quantidade de peças compradas
    int codFornecedor;        // Código do fornecedor
    float valorImposto;       // Valor do imposto por peça
    float valorFrete;         // Valor do frete por peça
    float valorTotalPeca;     // Valor total da peça
    int codTransacao;         // Código da transação associada
} CompraPeca;

// Estrutura para transações gerais (compra ou venda)
typedef struct transacao {
    int codTransacao;         // Código da transação
    int formaPagamento;       // Forma de pagamento (1: à vista, 2: parcelado)
    float valorTotal;         // Valor total da transação
    int datatransacao;        // Data da transação (formato YYYYMMDD)
    int TipoTransacao;        // Tipo da transação (1: compra, 2: venda)
} Transacao;

// Model Estoque
void setTamanhoEstoque();                         // Incrementa o contador de estoque
int getTamanhoEstoque();                          // Retorna o número total de itens no estoque
CompraPeca *migraDadosEstoque();                  // Migra dados entre formatos de armazenamento
void setEstoque(CompraPeca *estoque);             // Salva o estoque no formato atual
CompraPeca *getEstoque();                         // Retorna os dados do estoque
CompraPeca *lerArquivoTxtEstoque(FILE *buffer);   // Lê os dados do estoque de um arquivo TXT
//void escreverArquivoTxtEstoque(FILE *buffer, CompraPeca *estoque); // Escreve os dados do estoque em um arquivo TXT
CompraPeca *lerArquivoBinEstoque(FILE *buffer);   // Lê os dados do estoque de um arquivo BIN
void escreverArquivoBinEstoque(FILE *buffer, CompraPeca *estoque); // Escreve os dados do estoque em um arquivo BIN

// Controller Estoque
void registrarCompra();                // Registra uma nova compra de peça
int atualizarEstoquePeca(Peca *pecas, int codigoPeca, int qtdComprada, float precoCusto, float frete, float imposto, float lucro);
// Atualiza o estoque de uma peça

void listarEstoque();                             // Lista todas as peças no estoque
void consultarPeca(int codPeca);                  // Consulta os detalhes de uma peça específica

// View Estoque
void menuEstoque();                    // Exibe o menu do módulo de estoque
void exibirEstoque();                             // Exibe o estoque completo

#endif // ESTOQUE_H
