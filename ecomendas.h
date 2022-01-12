/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   ecomendas.h
 * Author: hugo silva
 *
 * Created on 8 de janeiro de 2022, 14:59
 */

#ifndef ECOMENDAS_H
#define ECOMENDAS_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ECOMENDAS_H */

#define ERRO_LISTA_VAZIA_ENCOMENDAS "lista vazia"
#define ERRO_ENCOMENDA_NAO_EXISTE "ecomenda nao existe"
#define ERRO_LISTA_CHEIA_ENCOMENDAS "erro lista cheia"
#define ECOMENDAS_TAM_INICIAL 2
#define OBTER_NUMERO_ENCOMENDA "indique o numero da ecomenda "
#define MAX_NOME 25
#define MSG_OBTER_NOME_ENCOMENDAS "Indique o nome do artigo:"

#define MIN_TAMANHO 34
#define MAX_TAMANHO 48
#define OBTER_TAMANHO "indique o tamanho: "

typedef struct {
    int numero;
    char nome[MAX_NOME ];
    int tamanhoDoArtigo;
}Encomenda;

typedef struct {
    int contadorEncomenda;
    int tamanho;
    Encomenda *encomendas;
}Encomendas;

int carregarEncomendas(Encomendas *encomendas, char* ficheiro);
void inserirEncomendas(Encomendas *encomendas, char *ficheiro);
void procurarEncomendas(Encomendas encomendas);
void editarEncomendas(Encomendas *encomendas, char *ficheiro);
void removerEncomendas(Encomendas *encomendas, char *ficheiro);
void listarEncomendas(Encomendas encomendas);
void libertarEncomendas(Encomendas *encomendas);