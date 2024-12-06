
#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

/*
o Funcionários: Este cadastro contém os dados dos funcionários da oficina.
▪ Campos:
➢ Nome
➢ CPF
➢ Cargo
➢ Salário
*/
typedef struct {
    int codigo;
    char nome[100];
    char cpf[11];
    char endereco[150];
    char telefone[15];
    char cargo[100];
    float salario;
    int ativo;
} Funcionario;

// Model Funcionario
int getTamanhoFuncionarios();

void setTamanhoFuncionarios();

Funcionario* migraDadosFuncionario();

void setFuncionarios(Funcionario *funcionario);

Funcionario* getFuncionarios();

Funcionario *ler_arquivo_txt_funcionario(FILE *buffer);
void escrever_arquivo_txt_funcionario(FILE *buffer, Funcionario *funcionarios);
Funcionario *ler_arquivo_bin_funcionario(FILE *buffer);
void *escrever_arquivo_bin_funcionario(FILE *buffer, Funcionario *funcionarios);

//Controller Funcionario
Funcionario* readFuncionarios();

int createFuncionario(Funcionario ** funcionarios, Funcionario *funcionario);

int showFuncionario(Funcionario * funcionarios, int id);

int  updateFuncionario(Funcionario *funcionarios,Funcionario * funcionario);

int deleteFuncionario(Funcionario* funcionarios, int id);

//View Funcionario

void menuFuncionario(Funcionario ** funcionarios);

void novoFuncionario(Funcionario **funcionarios);

void mostrarFuncionario(Funcionario *funcionarios);

void apagarFuncionario(Funcionario *funcionarios);

void editarFuncionario(Funcionario * funcionarios);

int buscaNovoIDFuncionario(Funcionario * funcionarios);

void mostrarTodosFuncionarios(Funcionario *funcionarios);
#endif //FUNCIONARIO_H
