#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/oficina.h"
#include "../bibliotecas/utils.h"

// Função para ler os dados da oficina do sistema
Oficina *readOficina() {
    return getOficina(); // Retorna os dados da oficina através de uma função externa
}

// Função para criar uma nova oficina e salvar os dados no sistema
int createOficina(Oficina **oficina, Oficina *oficina_view) {
    *oficina = oficina_view; // Atualiza o ponteiro da oficina com os dados fornecidos

    // Salva os dados da oficina se o tipo de armazenamento não for apenas em memória
    if (getTipoArquivo() != MEM)
        setOficina(*oficina);

    return TRUE; // Retorna sucesso
}

// Função para atualizar os dados de uma oficina existente
int updateOficina(Oficina **oficina, Oficina *oficina_view) {
    *oficina = oficina_view; // Atualiza o ponteiro da oficina com os novos dados

    // Salva os dados atualizados se o tipo de armazenamento não for apenas em memória
    if (getTipoArquivo() != MEM)
        setOficina(*oficina);

    return TRUE; // Retorna sucesso
}

// Função para deletar (remover) a oficina do sistema
Oficina *deleteOficina() {
    removeOficina();        // Remove os dados da oficina armazenados no sistema
    delete_arq_oficina();   // Exclui o arquivo relacionado à oficina, se existir
    return NULL;            // Retorna NULL indicando que a oficina foi removida
}
