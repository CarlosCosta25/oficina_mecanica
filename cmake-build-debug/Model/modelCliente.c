#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//#include "trabalho_algoritmos2/funcoes.h"
// Definição de Data
#define TRUE 1
#define FALSE 0

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Definição de Cliente

typedef struct {
    int id;
    char *nome;
    char *endereco;
    char *cpf;
    char *telefone;
    char *email;
    int sexo;
    char *estado_civil;
    Data data;
} Cliente;

// Função para cadastrar cliente no arquivo

void setCliente(Cliente *cliente) {
    FILE *buffer;
    buffer = fopen("./bd/clientes.txt", "a+"); // Abre o arquivo corretamente
    if (buffer == NULL) {
        printf("Erro na abertura do arquivo clientes.txt!\n");
        return;
    }

    int escrevendo = fprintf(buffer, "%d\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n%d/%d/%d\n",
            cliente->id,
            cliente->nome,
            cliente->endereco,
            cliente->cpf,
            cliente->telefone,
            cliente->email,
            cliente->sexo,
            cliente->estado_civil,
            cliente->data.dia,
            cliente->data.mes,
            cliente->data.ano);

    if (escrevendo < 0) {
        printf("Erro na escrita do arquivo clientes.txt\n");
    } else {
        printf("Cliente cadastrado com sucesso\n");
    }

    fclose(buffer);
}

char* removeTags(char* dado) {
    //retorna o onde está o token >
    char *inicio = strchr(dado, '>');
    if (inicio == NULL) {
        return NULL; // Retorna NULL se não encontrar '>'
    }
    //vai para o inicio do dado a ser extraido
    inicio++;
    char *fim = strchr(inicio, '<');
    if (fim == NULL) {
        return NULL;

    }
    int tamanho = fim - inicio;
    char *conteudo = (char*) malloc((tamanho + 1) * sizeof (char));
    if (conteudo == NULL) {
        return NULL;
    }
    strncpy(conteudo, inicio, tamanho);
    conteudo[tamanho] = '\0'; // Adiciona o terminador nulo

    return conteudo; // Retorna o conteúdo extraído
}

Cliente* getClientes() {
    FILE *buffer;
    buffer = fopen("./bd/clientes.txt", "r");
    if (buffer == NULL) {
        printf("Erro na abertura do arquivo clientes.txt!\n");
        return NULL;
    }
    
    
    Cliente *clientes =NULL;
    int numClientes = 0;
    char* dadosRecebidos[11];
    char Linha[100];
    int i = 0;
    
    
    while (i <11/*!feof(buffer)*/) {
        printf("saiu");
        if (i > 11) {
            dadosRecebidos[i] = fgets(Linha, 100, buffer);
            i++;
        } else {
            i = 0;
            clientes = (Cliente *) realloc(clientes, (numClientes + 1) * sizeof (Cliente));
            clientes->id = atoi(removeTags(dadosRecebidos[0]));
            clientes->nome = removeTags(dadosRecebidos[1]);
            clientes->endereco = removeTags(dadosRecebidos[2]);
            clientes->cpf = removeTags(dadosRecebidos[3]);
            clientes->telefone = removeTags(dadosRecebidos[4]);
            clientes->email =removeTags(dadosRecebidos[6]);
            clientes->sexo =atoi(removeTags(dadosRecebidos[7]));
            clientes->estado_civil =removeTags(dadosRecebidos[8]);
            clientes->data.dia = 0;
            clientes->data.mes =0;
            clientes->data.ano= 0;
            numClientes++;

        }

    }
    return clientes;
}

int main() {
    // Alocação dinâmica da struct Cliente
    /* Cliente *cliente = (Cliente *) malloc(sizeof (Cliente));
     if (cliente == NULL) {
         printf("Erro ao alocar memória para o cliente!\n");
         return 1;
     }

     // Inicialização dos dados do cliente
     cliente->id = 1;
     cliente->nome = "João da Silva";
     cliente->endereco = "Rua Exemplo, 123";
     cliente->cpf = "123.456.789-10";
     cliente->telefone = "(11) 98765-4321";
     cliente->email = "joao@example.com";
     cliente->sexo = 1; // 1 para masculino, por exemplo
     cliente->estado_civil = "Solteiro";
     cliente->data.dia = 12;
     cliente->data.mes = 12;
     cliente->data.ano = 2012;

     // Chama a função para gravar os dados do cliente no arquivo
     setCliente(cliente);

     // Libera a memória alocada dinamicamente
     free(cliente);*/

    Cliente *cliente = getClientes();
    return 0;
}
