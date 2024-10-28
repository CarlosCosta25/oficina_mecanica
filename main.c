#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/utils.h"
#include "bibliotecas/cliente.h"
#include "bibliotecas/fornecedor.h"

int main(void) {
 setTipoArquivo(lerInt("Digite com qual tipo de dados vc deseja trabalhar: "));
   //menuCliente();
//Cliente* clientes = readClientes();
 menuFornecedor();

/*
 Cliente *cliente = malloc(sizeof(Cliente));
 cliente->id = 1;
 strcpy(cliente->nome, "John");
 strcpy(cliente->endereco, "Rua A, 123");
 strcpy(cliente->cpf,"123.456.789-10");
 strcpy(cliente->telefone,"(11)98765-4321");
 strcpy(cliente->email,"carlos.silva@email.com");
 cliente->sexo = 1;
 strcpy(cliente->estado_civil,"Solteiro");
 cliente->data.dia = 1;
 cliente->data.mes = 1;
 cliente->data.ano = 1;
 setTamanhoClientes();
 setClientes(cliente);
*/
    return 0;
}



/*Cliente *clientes = NULL;
 clientes =readClientes();
 printf("%d",buscaNovoIDCliente(clientes));
 //Fornecedor * fornecedores = malloc(sizeof(Fornecedor));
  /*Fornecedor *fornecedores =getFornecedores();
 printf("Fornecedores:%d\n",getTamanhoFornecedores());
 fornecedores[1].codigo = 1;
 strcpy(fornecedores[1].nome_fantasia,"Fantasia4");
 strcpy(fornecedores[1].razao_social,"Razão Social Fictícia 2 LTDA");
 fornecedores[1].incricao_estadual = 123456789;
 strcpy(fornecedores[1].cnpj,"12.345.678/0001-90");
 strcpy(fornecedores[1].endereco,"Rua Exemplo 123, Cidade A");
 strcpy(fornecedores[1].telefone,"(11) 1234-5678");
 strcpy(fornecedores[1].email,"contato@ficticia1.com");
 fornecedores[1].ativo = 1;
 setFornecedores(fornecedores);
 for(int i =0;i<getTamanhoFornecedores();i++) {
  printf("%s\n",fornecedores[i].nome_fantasia);
 }*/
//novoCliente(clientes);
//mostrarCliente(clientes);
// apagarCliente(clientes);
//editarCLiente(clientes);
/*Cliente *cliente = malloc(sizeof(Cliente));
strcpy(cliente->nome, "John");
strcpy(cliente->endereco, "Rua A, 123");
strcpy(cliente->cpf,"123.456.789-10");
strcpy(cliente->telefone,"(11)98765-4321");
strcpy(cliente->email,"carlos.silva@email.com");
cliente->sexo = 1;
strcpy(cliente->estado_civil,"Solteiro");
cliente->data.dia = 1;
cliente->data.mes = 1;
cliente->data.ano = 1;

createCliente(clientes,cliente);
clientes =readClientes();*/
