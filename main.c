#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bibliotecas/caixa.h"
#include "bibliotecas/utils.h"
#include "bibliotecas/cliente.h"
#include "bibliotecas/veiculo.h"
#include "bibliotecas/fornecedor.h"
#include "bibliotecas/oficina.h"
#include "bibliotecas/peca.h"
#include "bibliotecas/funcionario.h"
#include "bibliotecas/servico.h"
#include "bibliotecas/moduloTransacao.h"

int main(void) {
    setTipoArquivo(lerInt("Digite com qual tipo de dados vc deseja trabalhar: "));

    int opc = 0;

    Oficina *oficina_atual = migraDadosOficina();
    Cliente *cliente = NULL;
    cliente = migraDadosCliente();
    Veiculo *veiculo = migraDadosVeiculo();
    Peca *pecas = migraDadosPeca();
    Fornecedor *fornercedor = migraDadosFornecedor();
    Servico *servico = migraDadosServicos();
    Funcionario *funcionario = migraDadosFuncionario();
    Transacao *transacoes = migraDadosTransacao();
    ContasPagar *contas_pagar = migraDadosContasPagar();
    ContasReceber *contas_receber = migraDadosContasReceber();
    float valor_em_caixa = 0;
    valor_em_caixa = migraDadosCaixa();

    if(getTipoArquivo() != MEM) {
        oficina_atual = readOficina();
        cliente = readClientes();
        veiculo = readVeiculos();
        pecas = readPecas();
        fornercedor = readFornecedores();
        servico = readServicos();
        funcionario = readFuncionarios();
        transacoes = readTransacoes();
        contas_pagar = readContasPagar();
        contas_receber = readContasReceber();
    }


    while (opc != 7) {
        if (getTipoArquivo() != MEM) oficina_atual = readOficina();
        //verifica se a oficina existe oficina
        if (oficina_atual != NULL) {
            printf("\n===============SISTEMA GERENCIAL DE UMA OFICINA===============\n\n \t\tSeja bem vindo!! %s \n\n",
                   oficina_atual->nome);
            opc = lerInt(
                "\t DIGITE UMA OPÇÃO:\n"
                "      \t\t\t 1- CADASTROS\n"
                "      \t\t\t 2- AGENDAMENTOS E CONTROLE\n"
                "      \t\t\t 3- ESTOQUE\n"
                "      \t\t\t 4- FINANCEIRO\n"
                "      \t\t\t 5- RELATORIOS\n"
                "      \t\t\t 6- IMPORTAÇÃO/EXPORTAÇÃO\n"
                "      \t\t\t 7-SAIR\n"
                "=>");
            switch (opc) {
                //aqui vai chamar para cadastro...
                case 1:
                    int cadastros = lerInt("\n=========MODULOS CADASTROS==============\n"
                        "\t DIGITE UMA OPÇÃO:\n"
                        "      \t\t\t 1- CLIENTES\n"
                        "      \t\t\t 2- VEICULOS\n"
                        "      \t\t\t 3- PEÇAS\n"
                        "      \t\t\t 4- FORNECEDORES\n"
                        "      \t\t\t 5- SERVIÇOS\n"
                        "      \t\t\t 6- FUNCIONARIOS\n"
                        "      \t\t\t 7- OFICINA\n"
                        "      \t\t\t 0- VOLTAR\n"
                        "=>");
                    switch (cadastros) {
                        case 1:
                            menuCliente(&cliente);
                            break;
                        case 2:

                            menuVeiculo(&veiculo);
                            break;
                        case 3:
                            //para  pecas preciso passar fornecedor e pecas

                            menuPecas(&pecas, fornercedor);
                            break;
                        case 4:
                            menuFornecedor(&fornercedor);
                            break;
                        case 5:
                            menuServicos(&servico);
                            break;
                        case 6:
                            menuFuncionario(&funcionario);
                            break;
                        case 7:
                            menuOficina(&oficina_atual);
                            break;
                        default:
                            opc = -1;
                            break;
                    }


                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    int cadastrosF = lerInt("\n=========MODULOS FINANCEIRO==============\n"
                        "\t DIGITE UMA OPÇÃO:\n"
                        "      \t\t\t 1- TRANSAÇÃO\n"
                        "      \t\t\t 2- CONTAS A PAGAR\n"
                        "      \t\t\t 3- CONTAS A RECEBER\n"
                        "       \t\t\t 0 - SAIR\n"
                        "=>");
                    switch (cadastrosF) {
                        case 1:
                            menuTransacoes(&transacoes);
                            break;
                        case 2:
                            menuContasPagar(&contas_pagar, transacoes, &valor_em_caixa);
                            break;
                        case 3:
                            menuContasReceber(&contas_receber, &valor_em_caixa);
                            break;
                    }
                    break;
                case 5:
                    int filtro = lerInt("\n=========MODULOS RELATORIOS==============\n"
                        "\t DIGITE UMA OPÇÃO:\n"
                        "      \t\t\t 1- CLIENTES\n"
                        "      \t\t\t 2- VEICULOS\n"
                        "      \t\t\t 3- PEÇAS\n"
                        "      \t\t\t 4- FORNECEDORES\n"
                        "      \t\t\t 5- SERVIÇOS\n"
                        "      \t\t\t 6- FUNCIONARIOS\n"
                        "      \t\t\t 7- OFICINA\n"
                        "      \t\t\t 8- TRANSAÇÃO\n"
                        "      \t\t\t 9- CONTAS A PAGAR\n"
                        "      \t\t\t 10- CONTAS A RECEBER\n"
                        "      \t\t\t 11- CAIXA\n"
                        "      \t\t\t 0- VOLTAR\n"
                        "=>");
                switch (filtro) {
                    case 1:
                        filtrarClienteIDNome(cliente);
                        break;
                    case 4:
                        filtrarFornecedorIDNomeFantasia(fornercedor);
                        break;
                    case 6:
                        filtrarFuncionarioIDNome(funcionario);
                    break;

                }
                    break;
            }
        } else {
            Oficina *oficina_nova = migraDadosOficina();
            menuOficina(&oficina_nova);
        }
    }

    return 0;
}
