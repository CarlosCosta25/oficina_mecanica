#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/oficina.h"
#include "../bibliotecas/utils.h"

Oficina *readOficina() {
    return getOficina();
}

int createOficina(Oficina **oficina, Oficina *oficina_view) {
    *oficina = oficina_view;

    if (getTipoArquivo() != MEM)
        setOficina(*oficina);
    return TRUE;
}

int updateOficina(Oficina **oficina, Oficina *oficina_view) {
    *oficina = oficina_view;
    if (getTipoArquivo() != MEM)
        setOficina(*oficina);
    return TRUE;
}
Oficina * deleteOficina() {
    removeOficina();
    delete_arq_oficina();
    return NULL;
}
