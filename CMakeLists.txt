cmake_minimum_required(VERSION 3.30)
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
        View/fornecedorView.c
        bibliotecas/peca.h
        Controller/pecaController.c
        Model/modelPeca.c
        View/pecaView.c
        bibliotecas/oficina.h
        Controller/oficinaController.c
        Model/modelOficina.c
        View/oficinaView.c
        View/fornecedorView.c
        View/veiculoView.c
        View/funcionarioView.c
        View/veiculoView.c
        Model/modelVeiculo.c
        Model/modelFuncionario.c
        Controller/veiculoController.c
        Controller/funcionarioController.c
        bibliotecas/servico.h
        bibliotecas/servico.h
        Controller/servicoController.c
        Model/modelServico.c
        View/servicoView.c
        View/estoqueView.c
        Model/modelEstoque.c
        Controller/estoqueController.c
        bibliotecas/estoque.h)
