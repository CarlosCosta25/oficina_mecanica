#ifndef UTILS_H
#define UTILS_H
#define TRUE 1
#define FALSE -1
#define TXT 1
#define BIN 2
#define MEM 3
int lerInt(char* msg);
float lerFloat(char* msg);
char* lerString(char* msg);
char* removeTags(char* dado);
int equals(char* s1, char* s2);
void setTipoArquivo(int Arquivo);
int getTipoArquivo();
int equalsString(char* s1, char* s2);
#endif //UTILS_H
