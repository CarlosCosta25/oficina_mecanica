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

int main(void)
{
    setTipoArquivo(lerInt("Digite com qual tipo de dados vc deseja trabalhar: "));

    int opc = 0;

    Oficina* oficina_atual = readOficina();

    while (opc != 7)
    {
        //verifica se a oficina ex
        if (oficina_atual != NULL)
        {
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
            switch (opc)
            {
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
                    "      \t\t\t 7- VOLTAR\n"
                    "=>");
                switch (cadastros)
                {
                case 1:
                    Cliente* cliente = migraDadosCliente();
                    menuCliente(&cliente);
                    break;
                case 2:
                    /* code */
                    Veiculo* veiculo = migraDadosVeiculo();
                //menuVeiculo(&veiculo);
                    break;
                case 3:
                    /* para  pecas preciso passar fornecedor e pecas */
                    Peca* pecas = migraDadosPeca();
                    Fornecedor* fornercedor = migraDadosFornecedor();
                    menuPecas(&pecas,&fornercedor);
                    break;
                case 4:
            
                    menuFornecedor(&fornercedor);
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
                    break;
                }


                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
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
