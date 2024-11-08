#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../bibliotecas/oficina.h"
#include "../bibliotecas/utils.h"

void menuOficina(Oficina **oficina) {
    if (getTipoArquivo() != MEM) {
        *oficina = readOficina();
    }
    int opcao = -1;
    while (opcao != 0) {
        printf("==== MENU OFICINA ====\n");
        opcao = lerInt("Digite a opção desejada:\n"
            "1- Cadastrar nova oficina\n"
            "2- Ver oficina\n"
            "3- Editar oficina\n"
            "4- Excluir oficina\n"
            "0- Sair\n");
        switch (opcao) {
            case 1:
                novaOficina(*oficina);
                if (getTipoArquivo() != MEM) *oficina = readOficina();
                opcao = -1;
                break;

            case 2:
                mostrarOficina(*oficina);
                opcao = -1;
                break;

            case 3:
                editarOficina(*oficina);
                opcao = -1;
                break;

            case 4:
                apagarOficina(oficina);
                opcao = -1;
                break;
        }
    }
}

void novaOficina(Oficina *oficina) {
    Oficina *novaOficina = malloc(sizeof(Oficina));
    if (novaOficina == NULL) {
        printf("Erro ao alocar memória para a nova oficina!\n");
        return;
    }

    strcpy(novaOficina->nome, lerString("Digite o nome da oficina: "));
    strcpy(novaOficina->cpf_cnpj, lerString("Digite o CPF ou CNPJ da oficina: "));
    strcpy(novaOficina->endereco, lerString("Digite o endereço completo da oficina: "));
    strcpy(novaOficina->telefone, lerString("Digite o telefone da oficina: "));
    strcpy(novaOficina->email, lerString("Digite o email da oficina: "));
    novaOficina->porcentagem_lucro = lerFloat("Digite a porcentagem de lucro da oficina: ");

    if (createOficina(&oficina, novaOficina) != FALSE) {
        printf("Oficina cadastrada com sucesso!\n");
    } else {
        printf("Erro no cadastro da oficina!\n");
    }

    free(novaOficina); // Libera a memória da oficina após o cadastro
}
void mostrarOficina(Oficina *oficina) {
    if(hasOficina()!=FALSE) {
        printf("Nome: %s\n"
       "CPF/CNPJ: %s\n"
       "Endereço: %s\n"
       "Telefone: %s\n"
       "Email: %s\n"
       "Porcentagem de Lucro: %.2f\n",
       oficina->nome,
       oficina->cpf_cnpj,
       oficina->endereco,
       oficina->telefone,
       oficina->email,
       oficina->porcentagem_lucro
);


    }else {
        printf("Dados da oficina não cadastrados\n");
    }
}

void editarOficina(Oficina *oficina) {
    if (oficina == NULL) {
        printf("Nenhuma oficina cadastrada\n");
        return;
    }

    printf("O nome atual da Oficina é: %s \n",oficina->nome);
    if(lerInt("Deseja editar: (1 - Sim  0 -Não)\n") == TRUE) {
        strcpy(oficina->nome, lerString("Digite o novo nome da oficina: "));
    }
    printf("O CPF/CNPJ atual da Oficina é: %s \n",oficina->cpf_cnpj);
    if (lerInt("Deseja editar o CPF/CNPJ da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(oficina->cpf_cnpj, lerString("Digite o novo CPF/CNPJ da oficina: "));
    }
    printf("O endereço atual da Oficina é: %s \n",oficina->endereco);
    if (lerInt("Deseja editar o endereço da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(oficina->endereco, lerString("Digite o novo endereço da oficina: "));
    }
    printf("O telefone atual da Oficina é: %s \n",oficina->telefone);
    if (lerInt("Deseja editar o telefone da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(oficina->telefone, lerString("Digite o novo telefone da oficina: "));
    }
    printf("O email atual da Oficina é: %s \n",oficina->email);
    if (lerInt("Deseja editar o email da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        strcpy(oficina->email, lerString("Digite o novo email da oficina: "));
    }
    printf("A porcentagem atual da Oficina é: %0.2f \n",oficina->porcentagem_lucro);
    if (lerInt("Deseja editar a porcentagem de lucro da oficina? (1 - Sim, 0 - Não): ") == TRUE) {
        oficina->porcentagem_lucro = lerFloat("Digite a nova porcentagem de lucro da oficina: ");
    }
    if (updateOficina(&oficina,oficina)==FALSE) {
        printf("Erro na edição dos dados da oficina!\n");
    } else {
        printf("Dados da oficina editada com sucesso!\n");
    }

}
void apagarOficina(Oficina **oficina) {
    *oficina = deleteOficina(); // Atualiza o ponteiro para NULL
    if (*oficina != NULL) {
        printf("Erro ao deletar dados da oficina!\n");
    } else {
        printf("Dados apagados com sucesso!\n");
    }
}
