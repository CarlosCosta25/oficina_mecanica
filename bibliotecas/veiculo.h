#ifndef VEICULO_H
#define VEICULO_H

/*
o Veículos: Este cadastro contém os dados dos veículos dos clientes.
▪ Campos:
➢ Placa
➢ Modelo
➢ Marca
➢ Ano de Fabricação
➢ Chassi

*/
typedef struct {
    int codigo;
    char placa[7];
    char modelo[20];
    char marca[20];
    int anofabricacao;
    char chassi[17];
    int ativo;
} Veiculo;

// Model Veiculos
int getTamanhoVeiculos();

void setTamanhoVeiculos();

Veiculo* migraDadosVeiculo();

void setVeiculos(Veiculo *veiculo);

Veiculo* getVeiculos();

Veiculo *ler_arquivo_txt_veiculo(FILE *buffer);
void escrever_arquivo_txt_veiculo(FILE *buffer, Veiculo *veiculos);
Veiculo *ler_arquivo_bin_veiculo(FILE *buffer);
void *escrever_arquivo_bin_veiculo(FILE *buffer, Veiculo *veiculos);

//Controller Veículos
Veiculo* readVeiculos();

int createVeiculo(Veiculo ** veiculos, Veiculo *veiculo);

int showVeiculo(Veiculo * veiculos, int id);

int  updateVeiculo(Veiculo *veiculos,Veiculo * veiculo);

int deleteVeiculo(Veiculo* veiculos, int id);

//View Veículos

void menuVeiculo();

void novoVeiculo(Veiculo **veiculos);

void mostrarVeiculo(Veiculo *veiculos);

void apagarVeiculo(Veiculo *veiculos);

void editarVeiculo(Veiculo * veiculos);

int buscaNovoIDVeiculo(Veiculo * veiculos);

void mostrarTodosVeiculos(Veiculo *veiculo);
#endif //VEICULO_H
