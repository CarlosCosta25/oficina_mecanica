#ifndef UTILS_H
#define UTILS_H
#define TRUE 1
#define FALSE -1
#define TXT 1
#define BIN 2
#define MEM 3
int lerInt(char* msg);//função para facilitar a leitura de inteiros no terminal
float lerFloat(char* msg);//função para facilitar a leitura de float no terminal
char* lerString(char* msg);//função para facilitar a leitura de string no terminal
char* removeTags(char* dado);//função que remove as tags de um xml
int equals(char* s1, char* s2);//função que compara se duas strings são iguais
void setTipoArquivo(int Arquivo);//muda o tipo de arquivo que vai ser trabalhado durante a execução do programa
int getTipoArquivo();// retorna o tipo de arquivo que vai ser trabalhado durante a execução do programa
time_t addtrintaDias(time_t dataAtual); //retorna a partir da data atual, mais 30 dias
void printData(time_t data); //mostra a data já formatada
time_t converteData(int dia, int mes, int ano); //converte a data para o formato time_t
#endif //UTILS_H
