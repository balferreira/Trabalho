/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   tamanhos.h
 * Author: hugo silva
 *
 * Created on 10 de janeiro de 2022, 10:30
 */

#ifndef TAMANHOS_H
#define TAMANHOS_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* TAMANHOS_H */
#define TAM_INICIAL 100
#define MAX_NOME 25
#define MSG_OBTER_NOME_TAMANHOS "Indique o nome do artigo: (em maisculas)"
#define MIN_NUMERO 34
#define MAX_NUMERO 48
#define OBTER_NUMERO "Indique o tamanho que queres"
#define OBTER_PRECO "Indique o preco"
#define TAM_LINHA 10000
typedef struct {
    int numero;
    char nome[MAX_NOME];
    int preco;
    int maoDeObra;
} Tamanho;

typedef struct {
    int contador;
    int tam ;
    Tamanho *tamanhos;
} Tamanhos;
 int carregarTamanhos(Tamanhos *tamanhos, char *ficheiro);
 void editarTamanho(Tamanho *tamanho);
 void procurarTamanhos(Tamanhos tamanhos);
 void listarTamanhos(Tamanhos tamanhos);
 void editarTamanhos(Tamanhos *tamanhos, char *ficheiro);
 