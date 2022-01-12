/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   artigo.h
 * Author: hugo silva
 *
 * Created on 29 de dezembro de 2021, 14:35
 */

#ifndef ARTIGO_H
#define ARTIGO_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* ARTIGO_H */
#define ARTIGO_TAM_INICIAL 2
#define ERRO_ARTIGO_NAO_EXISTE "Artigo não existe"
#define ERRO_ARTIGO_EXISTE "O número de artigo já se encontra atribuído."
#define ERRO_LISTA_ARTIGOS_CHEIA "lista cheia"
#define ERRO_LISTA_ARTIGOS_VAZIA "lista vazia"
#define MSG_OBTER_NUMERO_ARTIGO "Insira o número que pretende"
#define MAX_NOME_ARTIGO 25
#define MSG_OBTER_NOME_ARTIGO "Insira o nome do artigo"
#define MSG_OBTER_INT "Insira o número que pretende"
#define MAX_TIPO_ARTIGO 25
#define MSG_OBTER_TIPO_ARTIGO "Insira o tipo do artigo"

typedef struct {
    char nomeArtigo[MAX_NOME_ARTIGO];
    int numeroArtigo;
    char tipoArtigo[MAX_TIPO_ARTIGO];
} Artigo;

/**
Estrutura Artigos
    int ContadorArtigos - Contador de artigos
    int *ContadorArtigos2 - Contador de artigos
    int tamanho - 
    int tam2 - 
    Artigo *artigos - 
**/
typedef struct {
    int ContadorArtigos, *ContadorArtigos2;
    int tamanho;
    int tam2;
    Artigo *artigos;
} Artigos;

/**
 * Carrega os artigos do ficheiro
 * @param Artigos *artigos - Apontador para o artigo
 * @param ficheiro - Apontador para o ficheiro
 * @return 1 Sucesso
 * @return 0 Insucesso
 */
int carregarArtigos(Artigos *artigos, char* ficheiro);
void editarArtigos(Artigos *artigos, char *ficheiro);
void removerArtigos(Artigos *artigos, char *ficheiro);
void procurarArtigos(Artigos artigos);
void inserirArtigos(Artigos *artigos, char *ficheiro);
void listarArtigos(Artigos artigos);
void libertarArtigos(Artigos *artigos);
