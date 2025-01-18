#ifndef MODULOTRANSACAO_H
#define MODULOTRANSACAO_H

typedef struct {
    int codigo;
    int formaPagamento;
    float valorTotal;
    int tipoTransacao;
    time_t dataTransacao;
} Transacao;

typedef struct {
    int codigo;
    int codTransacao;
    time_t dataPagamento;
    time_t dataEfeituacaoPagamento;
    int pago;
} ContasPagar;

typedef struct {
    int codigo;
    int codTransacao;
    float valor;
    time_t dataPagamento;
    time_t recebimento;
    int pago;
}ContasReceber;

#define AVISTA 0 // Forma de pagamento
#define CARTAO 1 // Forma de pagamento
#define COMPRA 0 // Tipo de transação
#define VENDA 1 // Tipo de Transação

// Model transações
Transacao *migraDadosTransacao(); // Função que migra dados entre diferentes tipos de arquivo
Transacao *getTransacoes(); // Função que retorna a lista de transações
void setTransacoes(Transacao *transacoes); // Função que atualiza a lista de transações
int getTamanhoTransacoes(); // Função que retorna o número de transações cadastradas
void setTamanhoTransacoes(); // Função que incrementa o número de transações cadastradas
void removeTamanhoTransacoes(); // Função que decrementa 1 unidade a quantidade de transações
void escrever_arquivo_txt_transacao(FILE *buffer, Transacao *transacoes); // Função para escrever no arquivo txt
Transacao *ler_arquivo_txt_transacao(FILE *buffer); // Função que lê os dados de uma transação do arquivo txt
Transacao *ler_arquivo_bin_transacao(FILE *buffer); // Função que lê os dados de uma transação do arquivo binário
void escrever_arquivo_bin_transacao(FILE *buffer, Transacao *transacoes); // Função para escrever no arquivo binário

// Controller transações
int createTransacao(Transacao **transacoes, Transacao *transacao, float *valor_em_caixa, ContasPagar **contas_pagar,
                    ContasReceber **contas_receber, int qtd_parcelas);
Transacao *readTransacoes(); // Função que retorna todas as transações cadastradas
int showTransacao(Transacao *transacoes, int codigo); // Função que mostra os dados de uma transação baseada no código
int deleteTransacao(Transacao *transacoes, int codigo); // Função que exclui uma transação com base no código
int buscaNovoIDTransacao(Transacao *transacoes); // Função que encontra um ID válido para uma nova transação

// View transação
int novaTransacao(Transacao **transacoes, int tipoTransacao, float valor_Total, ContasPagar **contas_pagar,
                  ContasReceber **contas_receber, float *valor_em_caixa);
void menuTransacoes(Transacao **transacoes); // Menu que exibe as opções de interação com as transações
void mostrarTransacao(Transacao *transacoes); // Função que exibe os dados de uma transação
void apagarTransacao(Transacao *transacoes); // Função que apaga os dados de uma transação
void mostrarTodasTransacoes(Transacao *transacoes); // Função que exibe todas as transações cadastradas


int getTamanhoContasReceber();
void setTamanhoContasReceber();
void removeTamanhoContasReceber();
ContasReceber *migraDadosContasReceber();
void setContasReceber(ContasReceber *contas);
ContasReceber *getContasReceber();
ContasReceber *ler_arquivo_txt_contasReceber(FILE *buffer);
void escrever_arquivo_txt_contasReceber(FILE *buffer, ContasReceber *contas);
ContasReceber *ler_arquivo_bin_contasReceber(FILE *buffer);
void escrever_arquivo_bin_contasReceber(FILE *buffer, ContasReceber *contas);


ContasReceber * readContasReceber();
int createContasReceber(ContasReceber **contas,int codTransacao, time_t dataPagamento, float valor);
int showContasReceber(ContasReceber *contas, int codigo);
int deleteContasReceber(ContasReceber *contas, int codigo);
int contaRecebida(ContasReceber *contas, int codigo, float *valor_em_caixa,time_t dataPagamento);
int buscaNovoIDContasReceber(ContasReceber *contas);
int temContasReceber(ContasReceber * contas);
int temContasRecebidas(ContasReceber * contas);

void receberConta(ContasReceber * contas,float * valor_em_caixa);
void mostrarTodasContasReceber(ContasReceber *contas);
void menuContasReceber(ContasReceber **contas, float *valor_em_caixa);
void mostrarContasReceber(ContasReceber *contas);
void mostrarContasRecebidas(ContasReceber *contas);
void mostrarTodasContasRecebidas(ContasReceber *contas);
void mostrarTodasContasReceber(ContasReceber *contas);
void apagarContaReceber(ContasReceber *contas);
void mostrarTodasContaReceber(ContasReceber *contas);


int getTamanhoContasPagar();
void setTamanhoContasPagar();
void removeTamanhoContasPagar();
ContasPagar *migraDadosContasPagar();
void setContasPagar(ContasPagar *contas);
ContasPagar *getContasPagar();
ContasPagar *ler_arquivo_txt_contasPagar(FILE *buffer);
void escrever_arquivo_txt_contasPagar(FILE *buffer, ContasPagar *contas);
ContasPagar *ler_arquivo_bin_contasPagar(FILE *buffer);
void escrever_arquivo_bin_contasPagar(FILE *buffer, ContasPagar *contas);

ContasPagar *readContasPagar();
int createContasPagar(ContasPagar **contas,int codTransacao, time_t dataPagamento);
int showContasPagar(ContasPagar *contas, int codigo);
int deleteContasPagar(ContasPagar *contas, int codigo);
int contaPaga(ContasPagar *contas, int codigo, Transacao *transacoes, float *valor_em_caixa);
int buscaNovoIDContasPagar(ContasPagar *contas);
int temContasPagar(ContasPagar * contas);
int temContasPagas(ContasPagar * contas);

void menuContasPagar(ContasPagar **contas, Transacao *transacoes, float *valor_em_caixa);
void mostrarContaPagar(ContasPagar *contas, Transacao *transacoes);
void mostrarContasPaga(ContasPagar *contas, Transacao *transacoes);
void mostrarTodasContasPagar(ContasPagar *contas, Transacao *transacoes);
void apagarContaPagar(ContasPagar *contas,Transacao * transacoes);
void mostrarTodasContas(ContasPagar *contas, Transacao *transacoes);
void mostrarTodasContasPagas(ContasPagar *contas, Transacao *transacoes);
void pagarConta(ContasPagar * contas,Transacao * transacoes,float * valor_em_caixa);

#endif //MODULOTRANSACAO_H
