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
    int datatransacao;        // Data da transação (formato YYYYMMDD)
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
void setTamanhoEstoque(int tamanho);
int getTamanhoEstoque();
CompraPeca *migraDadosEstoque();
void setEstoque(CompraPeca *estoque);
CompraPeca *getEstoque();
CompraPeca *lerArquivoTxtEstoque(FILE *buffer);
void escreverArquivoTxtEstoque(FILE *buffer, CompraPeca *estoque);
CompraPeca *lerArquivoBinEstoque(FILE *buffer);
void escreverArquivoBinEstoque(FILE *buffer, CompraPeca *estoque);
int buscarOuCadastrarFornecedor(Fornecedor **fornecedores, char *cnpj); // Função que verifica se foi cadastrado

// Controller Estoque
void registrarCompra();
int atualizarEstoquePeca(Peca *pecas, int codigoPeca, int qtdComprada, float precoCusto, float frete, float imposto, float lucro);
void listarEstoque();
void consultarPeca(int codPeca);
int buscarPecaPorNome(Peca *pecas, char *nome); // Adicionada para buscar peça por nome
int buscarOuCadastrarPeca(Peca **pecas, char *nomePeca, int codFornecedor);  // Adicionada a declaração
// View Estoque
void novaNotaEntrada(Peca *pecas, Fornecedor *fornecedores);
void menuEstoque(Peca *pecas, Fornecedor *fornecedores);
void exibirEstoque();

#endif // ESTOQUE_H