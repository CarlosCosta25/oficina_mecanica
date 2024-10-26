
#ifndef CLIENTE_H
#define CLIENTE_H

// Definição de Cliente
typedef struct {
    int codigo;
    char nome[100];
    char cpf_cnpj[20];
    char endereco[150];
    char telefone[15];
    char email[100];
    int ativo;
} Cliente;
// Model cliente
int getTamanhoClientes();

void setTamanhoClientes();

Cliente* migraDadosCliente();

void setClientes(Cliente *cliente);

Cliente* getClientes();

Cliente *ler_arquivo_txt_cliente(FILE *buffer);
void escrever_arquivo_txt_cliente(FILE *buffer, Cliente *clientes);
Cliente *ler_arquivo_bin_cliente(FILE *buffer);
void *escrever_arquivo_bin_cliente(FILE *buffer, Cliente *clientes);

//Controller cliente
Cliente* readClientes();

int createCliente(Cliente ** clientes, Cliente *cliente);

int showCliente(Cliente * clientes, int id);

int  updateCliente(Cliente *clientes,Cliente * cliente);

int deleteCliente(Cliente* clientes, int id);

//View cliente

void menuCliente();

void novoCliente(Cliente **clientes);

void mostrarCliente(Cliente *clientes);

void apagarCliente(Cliente *clientes);

void editarCLiente(Cliente * clientes);

int buscaNovoIDCliente(Cliente * clientes);
#endif //CLIENTE_H
