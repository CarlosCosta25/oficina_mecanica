cmake_minimum_required(VERSION 3.29)
project(trabalho C)

set(CMAKE_C_STANDARD 11)

add_executable(trabalho main.c
        Model/modelCliente.c
        Utils/util.c
        bibliotecas/utils.h
        bibliotecas/cliente.h
        Controller/clienteController.c
        View/clienteView.c
        Model/modelFornecedor.c
        Model/modelFornecedor.c
        bibliotecas/fornecedor.h
        Controller/fornecedorController.c
        Controller/fornecedorController.c
        View/fornecedorView.c
        View/fornecedorView.c)
