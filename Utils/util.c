#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../bibliotecas/utils.h"
//função para facilitar a leitura de int no terminal
int lerInt(char* msg) {
    printf("%s", msg);
    int valor;
    setbuf(stdin, NULL);
    scanf("%d", &valor);
    return valor;
}
//função para facilitar a leitura de float no terminal
float lerFloat(char* msg) {
    printf("%s", msg);
    float valor;
    setbuf(stdin, NULL);
    scanf("%f", &valor);
    return valor;
}
//função para facilitar a leitura de string no terminal
char* lerString(char* msg) {
    printf("%s", msg);
    char* valor = malloc(sizeof(char) * 100);
    setbuf(stdin, NULL);
    //fgets(valor);
    fgets(valor, sizeof(valor), stdin);
    setbuf(stdin, NULL);
    return valor;
}
// remove os tokens do xml
char* removeTags(char* dado) {
    char *stringResult = malloc(1); // Aloca um espaço inicial de 1 byte (para o terminador nulo)
    if (stringResult == NULL) {
        return NULL; // Retorna NULL se a alocação falhar
    }
    stringResult[0] = '\0'; // Inicializa a string vazia

    int i = 0;
    // Ignora o conteúdo antes do primeiro '>'
    while (dado[i] != '>' && dado[i] != '\0') {
        i++;
    }
    i++; // Avança para o caractere após '>'

    // Adiciona os caracteres entre as tags '<' e '>'
    while (dado[i] != '<' && dado[i] != '\0') {
        int tamanhoAtual = strlen(stringResult);
        stringResult = realloc(stringResult, tamanhoAtual + 2); // Realoca memória para adicionar um novo caractere
        if (stringResult == NULL) {
            return NULL; // Retorna NULL em caso de falha de alocação
        }
        strncat(stringResult, &dado[i], 1); // Adiciona o caractere à string resultante
        i++;
    }

    return stringResult; // Retorna o conteúdo extraído entre as tags
}

/*char* removeTags(char* dado) {
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
    inicio = NULL;
    fim = NULL;
    return conteudo; // Retorna o conteúdo extraído
}*/

//funçãoq eu compara se duas strings são iguais
int equals(char* s1, char* s2) {
    //if (strlen(s1) != strlen(s2)) return FALSE;
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] == '\n' && s2[i] == '\n') return TRUE; // esse if serva para ler no txt sem isso, não funciona
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
int equalsString(char* s1, char* s2) {
    if (strlen(s1) != strlen(s2)) return FALSE;
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) return FALSE;
    }
    return TRUE;
}




