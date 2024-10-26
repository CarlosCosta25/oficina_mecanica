#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/cliente.h"
#include "../bibliotecas/utils.h"

Cliente* readClientes() {
    Cliente * clientes = NULL;
    clientes = getClientes();
        return clientes;
    }
int createCliente(Cliente *clientes, Cliente *cliente) {
    if (clientes == NULL) {
        clientes = malloc(sizeof(Cliente) * (getTamanhoClientes() + 1));
    } else {
        clientes = realloc(clientes, (getTamanhoClientes() + 1) * sizeof(Cliente));
    }

    int index = getTamanhoClientes();
    clientes[index].codigo = buscaNovoIDCliente(clientes);
    strcpy(clientes[index].nome, cliente->nome);
    strcpy(clientes[index].cpf_cnpj, cliente->cpf_cnpj);
    strcpy(clientes[index].endereco, cliente->endereco);
    strcpy(clientes[index].telefone, cliente->telefone);
    strcpy(clientes[index].email, cliente->email);
    clientes[index].ativo = 1;  // Cliente ativo ao ser criado

    setTamanhoClientes();
    if (getTipoArquivo() != 3) setClientes(clientes);
    return TRUE;
}
int showCliente(Cliente *clientes, int codigo) {
    if (clientes == NULL) return FALSE;

    int posicao = 0;
    int tamanho = getTamanhoClientes();

    // Procura o cliente com o código especificado dentro do limite do array
    while (posicao < tamanho && clientes[posicao].codigo != codigo) {
        posicao++;
    }

    // Verifica se o cliente foi encontrado e se está ativo
    if (posicao == tamanho || clientes[posicao].ativo == FALSE)
        return FALSE;

    return posicao;
}
int updateCliente(Cliente *clientes, Cliente *cliente) {

    int posicao = showCliente(clientes, cliente->codigo);

    if (posicao == FALSE) return FALSE;

    // Atualiza os campos necessários
    clientes[posicao].codigo = cliente->codigo;
    strcpy(clientes[posicao].nome, cliente->nome);
    strcpy(clientes[posicao].cpf_cnpj, cliente->cpf_cnpj);
    strcpy(clientes[posicao].endereco, cliente->endereco);
    strcpy(clientes[posicao].telefone, cliente->telefone);
    strcpy(clientes[posicao].email, cliente->email);
    clientes[posicao].ativo = cliente->ativo; // Atualiza o campo ativo

    if (getTipoArquivo() != 3) setClientes(clientes);
    return TRUE;
}

int deleteCliente(Cliente* clientes, int codigo) {
    int posicao = showCliente(clientes, codigo);

    if (posicao == FALSE) return FALSE; // Verifica se o cliente existe e está ativo

    clientes[posicao].ativo = FALSE; // Marca o cliente como inativo
    setClientes(clientes); // Atualiza a lista de clientes, se necessário
    return TRUE;
}

int buscaNovoIDCliente(Cliente * clientes) {
    int maior = 1;
    if(getTamanhoClientes() == 0 ) return maior;
    for(int i = 0; i < getTamanhoClientes(); i++) {
        if(maior <= clientes[i].codigo) {
            maior = clientes[i].codigo+1;
        }
    }
        return maior;
}
