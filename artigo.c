/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "artigo.h"

void imprimirArtigo(Artigo artigo) { //
    printf("\n Numero do Artigo: %d \n Nome do Artigo: %s", artigo.numeroArtigo, artigo.nomeArtigo);
}

int procurarArtigo(Artigos artigos, int numero) {
    int i;
    for (i = 0; i < artigos.ContadorArtigos; i++) {
        if (artigos.artigos[i].numeroArtigo == numero) {
            return i;
        }
    }
    return -1;
}

int obtemContadorAR(char *ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

int carregarArtigos(Artigos *artigos, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&artigos->ContadorArtigos, sizeof (int), 1, fp);

        if (artigos->ContadorArtigos > 0) {
            artigos->artigos = (Artigo*) malloc(artigos->ContadorArtigos * sizeof (Artigo));
            fread(artigos->artigos, sizeof (Artigo), artigos->ContadorArtigos, fp);

            artigos->tamanho = artigos->ContadorArtigos;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            artigos->artigos = (Artigo*) malloc(ARTIGO_TAM_INICIAL * sizeof (Artigos));
            artigos->ContadorArtigos = 0;
            artigos->tamanho = ARTIGO_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}

void libertarArtigos(Artigos * artigo) {
    free(artigo->artigos);
}

void atualizarContadorAR(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

void inserirArtigoAR(Artigos artigos, char *ficheiro) {
    atualizarContadorAR(artigos.ContadorArtigos, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&artigos.artigos[artigos.ContadorArtigos - 1], sizeof (Artigos), 1, fp);

    fclose(fp);
}

void atualizarArtigoAR(Artigos artigos, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Artigo) * indice, SEEK_CUR);

    fwrite(&artigos.artigos[indice], sizeof (Artigo), 1, fp);
}

void removerArtigoAr(Artigos artigos, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&artigos.ContadorArtigos, sizeof (int), 1, fp);
    fwrite(artigos.artigos, sizeof (Artigo), artigos.ContadorArtigos, fp);
}

int criarArtigo(Artigos *artigos) {
    int numero = obterInt2(MSG_OBTER_INT);
    if (procurarArtigo(*artigos, numero) == -1) {
        artigos->artigos[artigos->ContadorArtigos].numeroArtigo = numero;
        lerString(artigos->artigos[artigos->ContadorArtigos].nomeArtigo, MAX_NOME_ARTIGO, MSG_OBTER_NOME_ARTIGO);
        lerString(artigos->artigos->tipoArtigo, MAX_TIPO_ARTIGO, MSG_OBTER_TIPO_ARTIGO);
        return artigos->ContadorArtigos++;
    }
    return -1;
}

void expandirArtigo(Artigos *artigos) {
    Artigo *temp = (Artigo*) realloc(artigos->artigos, sizeof (Artigo) * (artigos->tamanho * 2));
    if (temp != NULL) {
        artigos->tamanho *= 2;
        artigos->artigos = temp;
    }
}

void editarArtigo(Artigo *artigo) {
    (*artigo).numeroArtigo, obterInt2(MSG_OBTER_INT);
    lerString((*artigo).nomeArtigo, MAX_NOME_ARTIGO, MSG_OBTER_NOME_ARTIGO);
    lerString2((*artigo).tipoArtigo, MAX_TIPO_ARTIGO, MSG_OBTER_TIPO_ARTIGO);
}

void apagarArtigo(Artigo *artigo) {
    artigo->numeroArtigo = 0;
    strcpy(artigo->nomeArtigo, "");
    strcpy(artigo->tipoArtigo, "");
}

void inserirArtigos(Artigos *artigos, char *ficheiro) {
    if (artigos->ContadorArtigos == artigos->tamanho) {
        expandirArtigo(artigos);
    }

    if (artigos->ContadorArtigos < artigos->tamanho) {
        if (criarArtigo(artigos) == -1) {
            puts(ERRO_ARTIGO_EXISTE);
        } else {
            inserirArtigoAR(*artigos, ficheiro);
        }
    } else {
        puts(ERRO_LISTA_ARTIGOS_CHEIA);
    }
}

void procurarArtigos(Artigos artigos) {
    int numero = procurarArtigo(artigos,
            obterInt2(MSG_OBTER_INT));
    if (numero != -1) {
        imprimirArtigo(artigos.artigos[numero]);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}

void editarArtigos(Artigos *artigos, char *ficheiro) {
    int numero = procurarArtigo(*artigos,
            obterInt2(MSG_OBTER_INT));
    if (numero != -1) {
        editarArtigo(&(*artigos).artigos[numero]);
        atualizarArtigoAR(*artigos, numero, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}

void removerArtigos(Artigos *artigos, char *ficheiro) {
    int i, numero = procurarArtigo(*artigos, obterInt2(MSG_OBTER_NUMERO_ARTIGO));
    if (numero != -1) {
        for (i = numero; i < artigos->ContadorArtigos - 1; i++) {
            artigos->artigos[i] = artigos->artigos[i + 1];
        }
        apagarArtigo(&artigos->artigos[i]);
        artigos->ContadorArtigos--;
         removerArtigoAr(*artigos, ficheiro);
    } else {
        puts(ERRO_ARTIGO_NAO_EXISTE);
    }
}

void listarArtigos(Artigos artigos) {
    if (artigos.ContadorArtigos > 0) {
        int i;
        for (i = 0; i < artigos.ContadorArtigos; i++) {
            imprimirArtigo(artigos.artigos[i]);
        }
    } else {
        puts(ERRO_LISTA_ARTIGOS_VAZIA);
    }
}
