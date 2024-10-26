#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"

int lerInt(char* msg) {
    printf("%s", msg);
    int valor;
    setbuf(stdin, NULL);
    scanf("%d", &valor);
    return valor;
}
float lerFloat(char* msg) {
    printf("%s", msg);
    int valor;
    setbuf(stdin, NULL);
    scanf("%f", &valor);
    return valor;
}
char* lerString(char* msg) {
    printf("%s", msg);
    char* valor = malloc(sizeof(char) * 100);
    setbuf(stdin, NULL);
    gets(valor);
    //fgets(valor, sizeof(valor), stdin);
    setbuf(stdin, NULL);
    return valor;
}
char* removeTags(char* dado) {
    //retorna o onde está o token >
    char* inicio = strchr(dado, '>');
    inicio++;
    char* fim = strchr(inicio, '<');
    int tamanho = fim - inicio;
    char *conteudo = malloc(sizeof (char));
    if (conteudo == NULL) {
        return NULL;
    }
    strncpy(conteudo, inicio, tamanho);
    return conteudo; // Retorna o conteúdo extraído
}
int equals(char* s1, char* s2) {
    //if (strlen(s1) != strlen(s2)) return FALSE;
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] == '\n' && s2[i] == '\n') return TRUE;
        if (s1[i] != s2[i]) return FALSE;
    }
    return FALSE;
}

int tipoArquivo = 0;// variavel global que diz o tipo de arquivo que o usuario deseja salvar os dados

void setTipoArquivo(int Arquivo){//muda o tipo de arquivo que vai ser trabalhado durante a execução do programa
    tipoArquivo = Arquivo;
}
int getTipoArquivo() {// retorna o tipo de arquivo que vai ser trabalhado durante a execução do programa
    return tipoArquivo;
}




