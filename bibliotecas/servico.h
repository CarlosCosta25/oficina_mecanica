#ifndef SERVICO_H
#define SERVICO_H
typedef struct {
    int codigo;
    char descricao[30];
    float preco;
    float comicao;
    int ativo;
}Servico;
//modelServicos
int getTamanhoServicos();
void setTamanhoServicos();
Servico *ler_arquivo_txt_servico(FILE *buffer);
void escrever_arquivo_txt_servico(FILE *buffer, Servico *servicos);
Servico *ler_arquivo_bin_servico(FILE *buffer);
void escrever_arquivo_bin_servico(FILE *buffer, Servico *servicos);
Servico *getServicos();
void setServicos(Servico *servicos);
Servico *migraDadosServicos();

//servicoController
Servico * readServicos();
int createServico(Servico **servicos, Servico *servico);
int showServico(Servico *servicos, int codigo);
int updateServico(Servico *servicos, Servico *servico);
int deleteServico(Servico *servicos, int codigo);
int buscaNovoIDServico(Servico *servicos);

// servicoView
void menuServicos(Servico **servicos);
void novoServico(Servico **servicos);
void mostrarServico(Servico *servicos);
void editarServico(Servico *servicos);
void apagarServico(Servico *servicos);
void mostrarTodosServicos(Servico *servicos);
#endif //SERVICO_H
