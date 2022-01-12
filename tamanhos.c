/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tamanhos.h"
#include "input.h"
#include "artigo.h"

void imprimirTamanhos(Tamanho tamanho) {
    printf("%d %s %d ", tamanho.numero, tamanho.nome, tamanho.preco);
}

/*
int procurarTamanho(Tamanhos tamanhos, int numero) {//usado para nas funçoes mais a frente nao ser preciso estar sempre a repetir o for 
    int i;
    for (i = 0; i < tamanhos.contador; i++) {
        if (tamanhos.tamanhos[i].numero == numero) {
            return i;
        }
    }
    return -1;
}
 */

int obtemContadorT(char *ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "r");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

void carregarTamanhos(Tamanhos *tamanhos, char *ficheiro, Artigos *artigos) {
    char ch;
    char line[TAM_LINHA];
    int i, j;
    FILE * fp = fopen(ficheiro, "r");
    if (fp != NULL) {
        if (artigos->ContadorArtigos + 3 > 0) {
            artigos.ContadorArtigos2 = (int*) malloc((artigos.ContadorArtigos + 3) * sizeof (int));
            artigos->tam2 = (artigos->ContadorArtigos + 3);
            if (artigos->tam2 == (artigos->ContadorArtigos + 3)) {
                int *temp = (int*) realloc(artigos.ContadorArtigos2, sizeof (int) * (artigos->tam2 * 2));
                if (temp != NULL) {
                    artigos->tam2 *= 2;
                   artigos.ContadorArtigos2 = temp;
                }
            }
        }
    }

    char guardar[artigos.ContadorArtigos2][45];

    for (i = 0; i < artigos.ContadorArtigos + 3; i++) {
        for (j = 0; j < 45; j++) {
            guardar[i][j] = NULL;
        }
    }
    
    i = 0;
    j = 0;
        while (fgets(line, sizeof (line), fp)) {
            while () {

            }
            i++;
            
        }

}

void libertarTamanhos(Tamanhos *tamanhos) {
    free(tamanhos->tamanhos);
}

void atualizarContadorT(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

void atualizarTamanhoE(Tamanhos tamanhos, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Tamanho) * indice, SEEK_CUR);

    fwrite(&tamanhos.tamanhos[indice], sizeof (Tamanho), 1, fp);
}

void editarTamanho(Tamanho *tamanho) {
    (*tamanho).numero = obterInt2(OBTER_NUMERO);
    lerString((*tamanho).nome, MAX_NOME, MSG_OBTER_NOME_TAMANHOS);
    (*tamanho).preco = obterInt2(OBTER_PRECO);
}

/*
void procurarTamanhos(Tamanhos tamanhos) {
    int numero = procurarTamanho(tamanhos,
            obterInt2(OBTER_NUMERO));
    if (numero != -1) {
        imprimirTamanhos(tamanhos.tamanhos[numero]);
    }
}
 */

void listarTamanhos(Tamanhos tamanhos) {
    if (tamanhos.contador > 0) {
        int i;
        for (i = 0; i < tamanhos.contador; i++) {
            imprimirTamanhos(tamanhos.tamanhos[i]);
        }
    }
}

void editarTamanhos(Tamanhos *tamanhos, char *ficheiro) {
    int numero = procurarTamanho(*tamanhos,
            obterInt2(OBTER_NUMERO));
    if (numero != -1) {
        editarTamanho(&(*tamanhos).tamanhos[numero]);
        atualizarTamanhoE(*tamanhos, numero, ficheiro);
    }
}
