#ifndef FORNECEDOR_H
#define FORNECEDOR_H
typedef struct {
    int codigo;
    char nome_fantasia[50];
    char razao_social[50];
   int  incricao_estadual;
    char cnpj[19];
    char endereco[60];
    char telefone[20];
    char email[50];
    int ativo;
}Fornecedor;

//Model fornecedor
Fornecedor* getFornecedores();
void setFornecedores(Fornecedor *fornecedores);
int getTamanhoFornecedores();
void setTamanhoFornecedores();

//Controller fornecedores
Fornecedor* readFornecedores();
int createFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor);
int showFornecedor(Fornecedor *fornecedores, int codigo);
int updateFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor);
int deleteFornecedor(Fornecedor* fornecedores, int codigo);
int buscaNovoIDFornecedor(Fornecedor * fornecedores);

//View fornecedor
void menuFornecedor();
void novoFornecedor(Fornecedor *fornecedores);
void mostrarFornecedor(Fornecedor *fornecedores);
void editarFornecedor(Fornecedor *fornecedores);
void apagarFornecedor(Fornecedor *fornecedores);

#endif //FORNECEDOR_H
