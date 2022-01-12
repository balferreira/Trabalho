/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   cliente.h
 * Author: hugo silva
 *
 * Created on 15 de dezembro de 2021, 09:33
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* CLIENTE_H */

#define CLIENTES_TAM_INICIAL      2

#define ERRO_CLIENTES_NAO_EXISTE "O cliente não existe na lista."
#define ERRO_LISTA_VAZIA_CLIENTE "A lista de clientes está vazia."
#define ERRO_LISTA_CHEIA_CLIENTE "A lista de clientes está cheia."
#define ERRO_CLIENTE_EXISTE "O número de cliente já se encontra atribuído."

#define MIN_NIF 100000000
#define MAX_NIF 999999999
#define MSG_OBTER_NUM_CLIENTE "Insira o nif do cliente: "

#define MAX_NOME_CLIENTE 31
#define MSG_OBTER_NOME "Insira o nome do cliente: "

#define MIN_DIA 1
#define MAX_DIA 31
#define OBTER_DIA_NASC "Insira o dia de nascimento: "

#define MIN_MES 1
#define MAX_MES 12
#define OBTER_MES_NASC "Insira o mês de nascimento: "

#define MIN_ANO 1900
#define MAX_ANO 2021
#define OBTER_ANO_NASC "Insira o ano de nascimento: "

#define MAX_PAIS 50
#define MSG_OBTER_PAIS_CLIENTE "inisra o pais do cliente: "

#define MAX_REMOVIDO 10
#define MSG_OBTER_CLIENTE_REMOVIDO "escreva removido: "

#define MAX_PALAVRA_PASS 25
#define MSG_OBTER_PASS "pass do cliente: "

#define MAX_PALAVRA_PASS_ADMIN 25
#define MSG_OBTER_PASS_ADMIN "pass do admin: "
typedef struct {
    int ano, mes, dia;
} Data;

typedef struct {
    int numero;
    char nome[MAX_NOME_CLIENTE];
    char pais[MAX_PAIS];
    Data data_nascimento;
    char clienteRemovido[MAX_REMOVIDO];
    char palavraPass[MAX_PALAVRA_PASS];
    char AdminpalavraPass[MAX_PALAVRA_PASS_ADMIN];
} Cliente;

typedef struct {
    int contador;
    int tamanho;
    Cliente *clientes;
} Clientes;

int carregarClientes(Clientes *clientes, char* ficheiro);
void inserirClientes(Clientes *clientes, char *ficheiro);
void procurarClientes(Clientes clientes);
void editarClientes(Clientes *clientes, char *ficheiro);
void removerClientes(Clientes *clientes, char *ficheiro);
void listarClientes(Clientes clientes);
void libertarClientes(Clientes *clientes);