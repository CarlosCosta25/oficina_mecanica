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
    // Configuração inicial: tipo de arquivo (1 - TXT, 2 - BIN, 3 - MEM)
    setTipoArquivo(lerInt("Digite com qual tipo de dados você deseja trabalhar (1 - TXT, 2 - BIN, 3 - MEM): "));

    int opc = 0;

    // Carrega os dados iniciais
    Oficina* oficina_atual = readOficina();
    Peca* pecas = migraDadosPeca();               // Peças disponíveis
    Fornecedor* fornecedores = migraDadosFornecedor(); // Fornecedores disponíveis

    while (opc != 7)
    {
        if (oficina_atual != NULL) // Verifica se a oficina está configurada
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
            case 1: // Menu de Cadastros
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
                        {
                            Cliente* cliente = migraDadosCliente();
                            menuCliente(&cliente);
                        }
                        break;

                    case 2:
                        {
                            Veiculo* veiculo = migraDadosVeiculo();
                            // menuVeiculo(&veiculo);
                        }
                        break;

                    case 3:
                        {
                            // Passa peças e fornecedores para o menu de peças
                            menuPecas(&pecas, fornecedores);
                        }
                        break;

                    case 4:
                        {
                            // Passa os fornecedores para o menu de fornecedores
                            menuFornecedor(&fornecedores);
                        }
                        break;

                    case 5:
                        {
                            Servico* servico = migraDadosServicos();
                            menuServicos(&servico);
                        }
                        break;

                    case 6:
                        {
                            Funcionario* funcionario = migraDadosFuncionario();
                            menuFuncionario(&funcionario);
                        }
                        break;

                    default:
                        break;
                    }
                }
                break;

            case 2: // Agendamentos e Controle
                // Implementar menu de agendamentos
                break;

            case 3: // Estoque
                menuEstoque(pecas, fornecedores); // Passa peças e fornecedores para o menu de estoque
                break;

            case 4: // Financeiro
                // Implementar menu financeiro
                break;

            case 5: // Relatórios
                // Implementar menu de relatórios
                break;

            case 6: // Importação/Exportação
                // Implementar menu de importação/exportação
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
            // Caso a oficina não esteja configurada, solicita cadastro
            Oficina* oficina_nova = migraDadosOficina();
            menuOficina(&oficina_nova);
        }
    }

    return 0;
}
