#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/utils.h"
#include "bibliotecas/cliente.h"
#include "bibliotecas/veiculo.h"
#include "bibliotecas/fornecedor.h"
#include "bibliotecas/oficina.h"
#include "bibliotecas/estoque.h"
#include "bibliotecas/funcionario.h"
#include "bibliotecas/servico.h"
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/utils.h"
#include "bibliotecas/cliente.h"
#include "bibliotecas/veiculo.h"
#include "bibliotecas/fornecedor.h"
#include "bibliotecas/oficina.h"
#include "bibliotecas/peca.h"
#include "bibliotecas/funcionario.h"
#include "bibliotecas/servico.h"
//include "bibliotecas/agendamento.h"
#include "bibliotecas/estoque.h"

int main(void)
{
    setTipoArquivo(lerInt("Digite com qual tipo de dados você deseja trabalhar (1 - TXT, 2 - BIN, 3 - MEM): "));


    int opc = 0;

    Oficina* oficina_atual = migraDadosOficina();
    //Cliente* cliente = NULL;
    Fornecedor* fornecedor = NULL;
    Peca *pecas = NULL;
    //cliente = migraDadosCliente();
    //Veiculo* veiculo = migraDadosVeiculo();
    pecas = migraDadosPeca();
    fornecedor = migraDadosFornecedor();
    //Servico* servico = migraDadosServicos();
    //Funcionario* funcionario = migraDadosFuncionario();
    //Agendamento *agendamentos = NULL;


    int tamanho = 0;

    // Supondo que você tenha os arrays de clientes, veiculos e funcionarios previamente declarados
    //Cliente* clientes = obterClientes();  // Função que retorna os clientes, exemplo
    //int qtdClientes = contarClientes();  // Função que retorna o número de clientes

    //Veiculo* veiculos = obterVeiculos();  // Função que retorna os veículos
    //int qtdVeiculos = contarVeiculos();  // Função que retorna o número de veículos

    //Funcionario* funcionarios = obterFuncionarios();  // Função que retorna os funcionários
   // int qtdFuncionarios = contarFuncionarios();  // Função que retorna o número de funcionários

    // Loop principal do menu
    while (opc != 7)
    {
        if(getTipoArquivo() != MEM) oficina_atual = readOficina();

        printf("\n===========================================================\n");
        printf("             SISTEMA DE GERENCIAMENTO DA OFICINA             \n");
        printf("=============================================================\n\n");
        printf("Bem-vindo à oficina: %s\n", oficina_atual->nome);

        // Menu principal
        opc = lerInt("\nEscolha uma das opções abaixo:\n"
                     "  1 - Cadastros\n"
                     "  2 - Agendamentos e Controle\n"
                     "  3 - Estoque\n"
                     "  4 - Financeiro\n"
                     "  5 - Relatórios\n"
                     "  6 - Importação/Exportação\n"
                     "  7 - Sair\n"
                     "Digite o número da opção desejada: ");

        switch (opc)
        {
            case 1:
                {
                    printf("\n=========================================\n");
                    printf("         MÓDULOS DE CADASTRO             \n");
                    printf("=========================================\n");

                    int cadastros = lerInt("\nEscolha o módulo que deseja acessar:\n"
                        "  1 - Clientes\n"
                        "  2 - Veículos\n"
                        "  3 - Peças\n"
                        "  4 - Fornecedores\n"
                        "  5 - Serviços\n"
                        "  6 - Funcionários\n"
                        "  7 - Voltar\n"
                        "Insira o número da opção desejada: ");
                    switch (cadastros)
                    {
                        case 1:
                            //menuCliente(&cliente);
                            break;
                        case 2:
                           /// menuVeiculo(&veiculo);
                            break;
                        case 3:
                            menuPecas(&pecas, fornecedor); // Corrigido o ponteiro
                            break;
                        case 4:
                            menuFornecedor(&fornecedor);
                            break;
                        case 5:
                           // menuServicos(&servico);
                            break;
                        case 6:
                           // menuFuncionario(&funcionario);
                            break;
                        case 7:
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        default:
                            printf("\nOpção inválida. Por favor, escolha uma opção válida.\n");
                            break;
                    }
                }
                break;

            case 2:
            //menuAgendamento(&agendamentos, &tamanho, clientes, qtdClientes, veiculos, qtdVeiculos, funcionarios, qtdFuncionarios);                break;

            case 3:
                menuEstoque(pecas, fornecedor);
                //printf("\nA funcionalidade de 'Estoque' ainda não está disponível.\n");
                break;

            case 4:
                printf("\nA funcionalidade de 'Financeiro' ainda não foi implementada.\n");
                break;

            case 5:
                printf("\nA funcionalidade de 'Relatórios' ainda não está disponível.\n");
                break;

            case 6:
                printf("\nA funcionalidade de 'Importação/Exportação' ainda não foi implementada.\n");
                break;

            case 7:
                printf("\nSaindo do sistema. Até logo!\n");
                break;

            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    }
    return 0;
}


