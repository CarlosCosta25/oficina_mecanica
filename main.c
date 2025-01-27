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

int main(void)
{
    setTipoArquivo(lerInt("Digite com qual tipo de dados você deseja trabalhar (1 - TXT, 2 - BIN, 3 - MEM): "));

    int opc = 0;

    Oficina* oficina_atual = readOficina();
    Peca* pecas = migraDadosPeca();


    Fornecedor* fornecedores = migraDadosFornecedor();


    while (opc != 7)
    {
        if (oficina_atual != NULL)
        {
            printf("\n=============== SISTEMA GERENCIAL DE UMA OFICINA ===============\n\n");
            printf("\t\tSeja bem-vindo!! %s \n\n", oficina_atual->nome);

            opc = lerInt(
                "\t DIGITE UMA OPÇÃO:\n"
                "      \t\t\t 1- CADASTROS\n"
                "      \t\t\t 2- AGENDAMENTOS E CONTROLE\n"
                "      \t\t\t 3- ESTOQUE\n"
                "      \t\t\t 4- FINANCEIRO\n"
                "      \t\t\t 5- RELATÓRIOS\n"
                "      \t\t\t 6- IMPORTAÇÃO/EXPORTAÇÃO\n"
                "      \t\t\t 7- SAIR\n"
                "=> ");
            switch (opc)
            {
            case 1:
                {
                    int cadastros = lerInt("\n========= MÓDULOS DE CADASTRO ==========\n"
                        "\t DIGITE UMA OPÇÃO:\n"
                        "      \t\t\t 1- CLIENTES\n"
                        "      \t\t\t 2- VEÍCULOS\n"
                        "      \t\t\t 3- PEÇAS\n"
                        "      \t\t\t 4- FORNECEDORES\n"
                        "      \t\t\t 5- SERVIÇOS\n"
                        "      \t\t\t 6- FUNCIONÁRIOS\n"
                        "      \t\t\t 7- VOLTAR\n"
                        "=> ");
                    switch (cadastros)
                    {
                    case 1:
                        Cliente* cliente = migraDadosCliente();
                        menuCliente(&cliente);
                        break;

                    case 2:
                        Veiculo* veiculo = migraDadosVeiculo();
                        // menuVeiculo(&veiculo);
                        break;

                    case 3:
                        menuPecas(&pecas, fornecedores);
                        break;

                    case 4:
                        menuFornecedor(&fornecedores);
                        break;

                    case 5:
                        Servico* servico = migraDadosServicos();
                        menuServicos(&servico);
                        break;

                    case 6:
                        Funcionario* funcionario = migraDadosFuncionario();
                        menuFuncionario(&funcionario);
                        break;

                    default:
                        printf("Opção inválida!\n");
                        break;
                    }
                }
                break;

            case 2:
                printf("Módulo de Agendamentos e Controle em desenvolvimento.\n");
                break;

            case 3:
                menuEstoque(pecas, &fornecedores);
                break;

            case 4:
                printf("Módulo Financeiro ainda não implementado.\n");
                break;

            case 5:
                printf("Módulo de Relatórios ainda não implementado.\n");
                break;

            case 6:
                printf("Módulo de Importação/Exportação ainda não implementado.\n");
                break;

            case 7:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
            }
        }
        else
        {
            Oficina* oficina_nova = migraDadosOficina();
            menuOficina(&oficina_nova);
        }
    }

    return 0;
}
