#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../bibliotecas/caixa.h"
#include "../bibliotecas/utils.h"
#include "../bibliotecas/moduloTransacao.h"

void menuTransacoes(Transacao **transacoes){
    if (getTipoArquivo() != 3) {
        *transacoes = readTransacoes(); // Se o tipo de armazenamento não for memória, lê as transações do armazenamento
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("\t==== MENU TRANSAÇÃO ====\n");
        opcao = lerInt("DIGITE A OPÇÃO DESEJADA:\n"
            "\t\t\t1- VER TRANSAÇÃO\n"
            "\t\t\t2- EXCLUIR TRANSAÇÃO\n"
            "\t\t\t0- SAIR\n"
            "=>");

        switch (opcao) {
            case 1:
                mostrarTransacao(*transacoes); // Função para exibir uma transação
                opcao = -1;
                break;
            case 4:
                apagarTransacao(*transacoes); // Função para excluir uma transação
                opcao = -1;
                break;
            default: // Opção inválida
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

int novaTransacao(Transacao **transacoes, int tipoTransacao, float valor_Total, ContasPagar **contas_pagar,
                  ContasReceber **contas_receber, float *valor_em_caixa) {
    Transacao *transacao = malloc(sizeof(Transacao));
    if (tipoTransacao == VENDA) {
        transacao->valorTotal = lerFloat("Digite o valor do serviço: ");
    } else transacao->valorTotal = valor_Total;
    transacao->formaPagamento = lerInt("Qual será a forma de pagamento:\n"
        "0 - A VISTA\n"
        "1 - CARTÃO/PARCELADO\n"
        "=>");
    int parcelas = 0;
    transacao->tipoTransacao = tipoTransacao;
    if (tipoTransacao == VENDA) {
        // prestando serviço
        if (transacao->formaPagamento == CARTAO) {
            // prestação de serviço a prazo
            parcelas = lerInt("Em quantas parcelas deseja dividir: ");
            if (createTransacao(transacoes, transacao, valor_em_caixa, contas_pagar, contas_receber, parcelas) == TRUE) {
                printf("Transação de venda criada com sucesso\n");
                return TRUE;
            }
        } else {
            // se a prestação de serviço for a vista
            if (addDinheiroAoCaixa(transacao->valorTotal, valor_em_caixa) == TRUE) {
                printf("Dinheiro adicionado ao caixa\n");
                return TRUE;
            }
        }
    }
    //Compra de peças
    if (tipoTransacao == COMPRA) {
        if (transacao->formaPagamento == CARTAO) {
            // compra a prazo
            if (createTransacao(transacoes, transacao, valor_em_caixa, contas_pagar, contas_receber, 0) == TRUE) {
                printf("Transação de compra criada com sucesso\n");
                return TRUE;
            }
        } else {
            // se a compra for a vista
            if (removeDinheiroDoCaixa(transacao->valorTotal, valor_em_caixa) == FALSE) {
                printf("ATENÇÃO!!!\n");
                printf("DINHEIRO EM CAIXA INSUFICIENTE!\n");
                printf("Dinheiro em caixa: %.2f\n", *valor_em_caixa);
                return FALSE;
            }else {
                printf("Dinheiro removido ao caixa\n");
            }
        }
    }
    return FALSE;
}

void mostrarTransacao(Transacao *transacoes) {
    if (getTamanhoTransacoes() == 0) {
        printf("Nenhuma transação cadastrada até o momento\n");
        return;
    }

    printf("\tTRANSAÇÕES:\n");
    mostrarTodasTransacoes(transacoes);

    int codigo = lerInt("Digite o código da transação que você deseja ver: ");
    int posicao = showTransacao(transacoes, codigo);

    if (posicao != FALSE) {
        printf("Código: %d\n"
               "Valor Total: %.2f\n",
               transacoes[posicao].codigo,
               transacoes[posicao].valorTotal
        ); // Exibe as informações da transação
        printf("Data da Transação: ");
        printData(transacoes[posicao].dataTransacao);
        if (transacoes[posicao].formaPagamento == AVISTA) printf("Forma de Pagamento: A Vista \n");
        else printf("Forma de Pagamento: No Cartão \n");
    } else {
        printf("Transação não encontrada!\n");
    }
}

void apagarTransacao(Transacao *transacoes) {
    if (getTamanhoTransacoes() == 0) {
        printf("Nenhuma transação cadastrada\n");
        return;
    }
    printf("\tTRANSAÇÕES:\n");
    mostrarTodasTransacoes(transacoes);
    int codigo = lerInt("Digite o código da transação que você deseja apagar: ");
    if (deleteTransacao(transacoes, codigo) == TRUE) {
        printf("Transação apagada com sucesso\n");
    } else {
        printf("Transação não existe\n");
    }
}

// Função para exibir todas as transações
void mostrarTodasTransacoes(Transacao *transacoes) {
    for (int i = 0; i < getTamanhoTransacoes(); i++) {
        if (transacoes[i].tipoTransacao == COMPRA) printf("Transação: Compra, ");
        else printf("Transação: Venda, ");
        printf("Codigo: %d\n", transacoes[i].codigo);
        printf("Data da Transação: ");
        printData(transacoes[i].dataTransacao);
    }
}
