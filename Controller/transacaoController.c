#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../bibliotecas/caixa.h"
#include "../bibliotecas/utils.h"
#include "../bibliotecas/moduloTransacao.h"

// Função para ler todas as transações cadastradas
Transacao *readTransacoes() {
    return getTransacoes(); // Retorna o ponteiro para a lista de transações
}

// Função para criar uma nova transação
int createTransacao(Transacao **transacoes, Transacao *transacao, float *valor_em_caixa, ContasPagar **contas_pagar,
                    ContasReceber **contas_receber, int qtd_parcelas) {
    int tamanhoAtual = getTamanhoTransacoes(); // Obtém o tamanho atual da lista de transações

    // Realoca a memória para incluir a nova transação
    Transacao *novoTransacoes = realloc(*transacoes, (tamanhoAtual + 1) * sizeof(Transacao));
    if (novoTransacoes == NULL) {
        printf("Erro ao alocar memória para Transações.\n");
        return FALSE; // Retorna FALSE indicando falha
    }

    *transacoes = novoTransacoes; // Atualiza o ponteiro da lista de transações
    int index = tamanhoAtual; // Define o índice da nova transação como o último da lista

    // Preenche os dados da nova transação no array
    (*transacoes)[index].codigo = buscaNovoIDTransacao(*transacoes); // Gera um novo ID único
    (*transacoes)[index].formaPagamento = transacao->formaPagamento; // Copia a forma de pagamento
    (*transacoes)[index].valorTotal = transacao->valorTotal; // Copia o valor total
    (*transacoes)[index].tipoTransacao = transacao->tipoTransacao;
    time_t dataAtual;
    time(&dataAtual);
    (*transacoes)[index].dataTransacao = dataAtual;
    // Copia o tipo de transação// Marca a transação como ativa

    setTamanhoTransacoes(); // Incrementa o tamanho da lista de transações

    // Salva as transações no arquivo se o tipo de armazenamento não for memória
    if (getTipoArquivo() != MEM) setTransacoes(*transacoes);

    //Se a transao for uma compra
    if (transacao->tipoTransacao == COMPRA) {
        if (transacao->formaPagamento == AVISTA) {
            return removeDinheiroDoCaixa(transacao->valorTotal, valor_em_caixa);// remove o valor da compra do caixa
        } else {
            time_t dataAtualC;
            time(&dataAtualC); // Pega a data atual
            dataAtualC =addtrintaDias( dataAtualC); // aumenta na data atual 30 dias
            createContasPagar(contas_pagar, (*transacoes)[index].codigo, dataAtualC); // cria uma conta a pagar
        }
    }
    //Se a transao for uma venda
    if (transacao->tipoTransacao == VENDA) {
        if (transacao->formaPagamento == AVISTA) {
            return addDinheiroAoCaixa(transacao->valorTotal, valor_em_caixa);
        } else {
            //divide o valor total em parcelas
            float valorDeCadaParcela = transacao->valorTotal / qtd_parcelas;
            time_t dataAtualV;
            time(&dataAtualV); // Pega a data atual
            for (int i = 0; i < qtd_parcelas; i++) {
                dataAtualV = addtrintaDias(dataAtualV); // aumenta na data atual 30 dias
                createContasReceber(contas_receber, (*transacoes)[index].codigo, dataAtualV, valorDeCadaParcela);
            }
        }
    }

    return TRUE; // Retorna TRUE indicando sucesso
}

// Função para localizar uma transação pelo código
int showTransacao(Transacao *transacoes, int codigo) {
    if (transacoes == NULL) return FALSE; // Retorna FALSE se a lista de transações for nula

    int posicao = 0;
    int tamanho = getTamanhoTransacoes(); // Obtém o tamanho atual da lista de transações

    // Procura a transação com o código especificado
    while (posicao < tamanho && transacoes[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se a transação foi encontrada e se está ativa
    if (posicao == tamanho)
        return FALSE;

    return posicao; // Retorna a posição da transação encontrada
}

int deleteTransacao(Transacao *transacoes, int codigo) {
    int posicao = showTransacao(transacoes, codigo); // Localiza a transação pelo código

    if (posicao == FALSE) return FALSE; // Retorna FALSE se a transação não for encontrada

    Transacao *removeTransacao = malloc(sizeof(Transacao) * (getTamanhoTransacoes() - 1));
    int novoTamanho = 0;
    for (int i = 0; i < getTamanhoTransacoes(); i++) {
        if (transacoes[i].codigo != codigo) {
            removeTransacao[novoTamanho] = transacoes[i];
            novoTamanho++;
        }
    }
    transacoes = removeTransacao;
    removeTamanhoTransacoes();
    // Salva as transações no arquivo se o tipo de armazenamento não for memória
    if (getTipoArquivo() != MEM) setTransacoes(transacoes);

    return TRUE; // Retorna TRUE indicando sucesso
}

// Função para gerar um novo ID exclusivo para uma nova transação
int buscaNovoIDTransacao(Transacao *transacoes) {
    int maior = 1;

    // Retorna 1 se não houver transações cadastradas
    if (getTamanhoTransacoes() == 0) return maior;

    // Percorre a lista de transações para encontrar o maior ID existente
    for (int i = 0; i < getTamanhoTransacoes(); i++) {
        if (maior <= transacoes[i].codigo) {
            maior = transacoes[i].codigo + 1; // Define o próximo ID como o maior + 1
        }
    }

    return maior; // Retorna o novo ID gerado
}
