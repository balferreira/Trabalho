/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "input.h"

void imprimirCliente(Cliente cliente) {
    printf("\n%3d %-15s %d-%d-%d  %-15s %s", cliente.numero, cliente.nome, cliente.data_nascimento.dia,
            cliente.data_nascimento.mes, cliente.data_nascimento.ano, cliente.pais, cliente.clienteRemovido);
}

int procurarCliente(Clientes clientes, int numero) {//usado para nas funçoes mais a frente nao ser preciso estar sempre a repetir o for 
    int i;
    for (i = 0; i < clientes.contador; i++) {
        if (clientes.clientes[i].numero == numero) {
            return i;
        }
    }
    return -1;
}

int obtemContadorCL(char *ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

int carregarClientes(Clientes *clientes, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&clientes->contador, sizeof (int), 1, fp);

        if (clientes->contador > 0) {
            clientes->clientes = (Cliente*) malloc(clientes->contador * sizeof (Cliente));
            fread(clientes->clientes, sizeof (Cliente), clientes->contador, fp);

            clientes->tamanho = clientes->contador;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            clientes->clientes = (Cliente*) malloc(CLIENTES_TAM_INICIAL * sizeof (Cliente));
            clientes->contador = 0;
            clientes->tamanho = CLIENTES_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}

void libertarClientes(Clientes * clientes) {
    free(clientes->clientes);
}

void atualizarContadorCL(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

void inserirClienteCL(Clientes clientes, char *ficheiro) {
    atualizarContadorCL(clientes.contador, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&clientes.clientes[clientes.contador - 1], sizeof (Cliente), 1, fp);

    fclose(fp);
}

void atualizarClienteCL(Clientes clientes, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Cliente) * indice, SEEK_CUR);

    fwrite(&clientes.clientes[indice], sizeof (Cliente), 1, fp);
}

/*
void removerClienteFX(Clientes clientes, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&clientes.contador, sizeof (int), 1, fp);
    fwrite(clientes.clientes, sizeof (Cliente), clientes.contador, fp);
}
 */

int inserirCliente(Clientes *clientes) {
    int numero = obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NUM_CLIENTE);

    if (procurarCliente(*clientes, numero) == -1) {
        clientes->clientes[clientes->contador].numero = numero;
        lerString(clientes->clientes[clientes->contador].nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);
        clientes->clientes[clientes->contador].data_nascimento.dia =
                obterInt(MIN_DIA, MAX_DIA, OBTER_DIA_NASC);
        clientes->clientes[clientes->contador].data_nascimento.mes =
                obterInt(MIN_MES, MAX_MES, OBTER_MES_NASC);
        clientes->clientes[clientes->contador].data_nascimento.ano =
                obterInt(MIN_ANO, MAX_ANO, OBTER_ANO_NASC);

        lerString(clientes->clientes[clientes->contador].pais, MAX_PAIS, MSG_OBTER_PAIS_CLIENTE);
        return clientes->contador++;
    }
    return -1;
}

void editarCliente(Cliente *cliente) {
    lerString((*cliente).nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);
    (*cliente).data_nascimento.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA_NASC);
    (*cliente).data_nascimento.mes = obterInt(MIN_MES, MAX_MES, OBTER_MES_NASC);
    (*cliente).data_nascimento.ano = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO_NASC);
    lerString((*cliente).pais, MAX_PAIS, MSG_OBTER_PAIS_CLIENTE);
}

void removerCliente(Cliente *cliente) {
    lerString((*cliente).clienteRemovido, MAX_REMOVIDO, MSG_OBTER_CLIENTE_REMOVIDO);
}

void expandirClientes(Clientes *clientes) {
    Cliente *temp = (Cliente*) realloc(clientes->clientes, sizeof (Cliente) * (clientes->tamanho * 2));
    if (temp != NULL) {
        clientes->tamanho *= 2;
        clientes->clientes = temp;
    }
}

void inserirClientes(Clientes *clientes, char *ficheiro) {
    if (clientes->contador == clientes->tamanho) {
        expandirClientes(clientes);
    }

    if (clientes->contador < clientes->tamanho) {
        if (inserirCliente(clientes) == -1) {
            puts(ERRO_CLIENTE_EXISTE);
        } else {
            inserirClienteCL(*clientes, ficheiro);
        }
    } else {
        puts(ERRO_LISTA_CHEIA_CLIENTE);
    }
}

void procurarClientes(Clientes clientes) {
    int numero = procurarCliente(clientes,
            obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NUM_CLIENTE));
    if (numero != -1) {
        imprimirCliente(clientes.clientes[numero]);
    } else {
        puts(ERRO_CLIENTES_NAO_EXISTE);
    }
}

void listarCliente(Clientes clientes) {
    if (clientes.contador > 0) {
        int i;
        for (i = 0; i < clientes.contador; i++) {
            imprimirCliente(clientes.clientes[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA_CLIENTE);
    }
}

void editarClientes(Clientes *clientes, char *ficheiro) {
    int numero = procurarCliente(*clientes,
            obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NUM_CLIENTE));
    if (numero != -1) {
        editarCliente(&(*clientes).clientes[numero]);
        atualizarClienteCL(*clientes, numero, ficheiro);
    } else {
        puts(ERRO_CLIENTES_NAO_EXISTE);
    }
}

void removerClientes(Clientes *clientes, char *ficheiro) {
    int i, numero = procurarCliente(*clientes,
            obterInt(MIN_NIF, MAX_NIF, MSG_OBTER_NUM_CLIENTE));
    if (numero != -1) {
        removerCliente(&(*clientes).clientes[numero]);
        atualizarClienteCL(*clientes, numero, ficheiro);
    }
}
