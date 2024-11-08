//
// Created by costa on 06/11/2024.
//

#ifndef OFICINA_H
#define OFICINA_H
typedef struct{
    char nome[100];
    char cpf_cnpj[20];
    char endereco[150];
    char telefone[15];
    char email[100];
    float porcentagem_lucro;
}Oficina;

//modelOficina
int hasOficina();
void addOficina();
int removeOficina();
Oficina *migraDadosOficina();
Oficina *getOficina();
void setOficina(Oficina *oficina);
Oficina *ler_arquivo_txt_oficina(FILE *buffer);
Oficina *ler_arquivo_bin_oficina(FILE *buffer);
void escrever_arquivo_txt_oficina(FILE *buffer, Oficina *oficina);
void escrever_arquivo_bin_oficina(FILE *buffer, Oficina *oficina);
void delete_arq_oficina();

//oficinaController
Oficina *readOficina();
int createOficina(Oficina **oficina, Oficina *oficina_view);
int updateOficina(Oficina **oficina, Oficina *oficina_view);
Oficina *deleteOficina();

//oficinaView
void menuOficina(Oficina **oficina);
void novaOficina(Oficina *oficina);
void mostrarOficina(Oficina *oficina);
void editarOficina(Oficina *oficina);
void apagarOficina(Oficina ** oficina);

#endif //OFICINA_H
