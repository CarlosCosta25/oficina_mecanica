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
Fornecedor *migraDadosFornecedor();
Fornecedor* getFornecedores();
void setFornecedores(Fornecedor *fornecedores);
int getTamanhoFornecedores();
void setTamanhoFornecedores();
void escrever_arquivo_txt_fornecedor(FILE *buffer, Fornecedor *fornecedores);
Fornecedor *ler_arquivo_txt_fornecedor(FILE *buffer);
Fornecedor *ler_arquivo_bin_fornecedor(FILE *buffer);
void escrever_arquivo_bin_fornecedor(FILE *buffer, Fornecedor *fornecedores);

//Controller fornecedores
Fornecedor* readFornecedores();
int createFornecedor(Fornecedor **fornecedores, Fornecedor *fornecedor);
int showFornecedor(Fornecedor *fornecedores, int codigo);
int updateFornecedor(Fornecedor *fornecedores, Fornecedor *fornecedor);
int deleteFornecedor(Fornecedor* fornecedores, int codigo);
int buscaNovoIDFornecedor(Fornecedor * fornecedores);

//View fornecedor
void menuFornecedor(Fornecedor **fornecedores);
void novoFornecedor(Fornecedor **fornecedores);
void mostrarFornecedor(Fornecedor *fornecedores);
void editarFornecedor(Fornecedor *fornecedores);
void apagarFornecedor(Fornecedor *fornecedores);
void mostrarTodosFornecedores(Fornecedor * fornecedores);

#endif //FORNECEDOR_H
