
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "ecomendas.h"

void imprimirEncomendas(Encomenda encomenda) {
    printf("%d %s %d", encomenda.numero, encomenda.nome, encomenda.tamanhoDoArtigo);
}

int procurarEncomenda(Encomendas encomendas, int numero) {//usado para nas funçoes mais a frente nao ser preciso estar sempre a repetir o for 
    int i;
    for (i = 0; i < encomendas.contadorEncomenda; i++) {
        if (encomendas.encomendas[i].numero == numero) {
            return i;
        }
    }

    return -1;
}

int obtemContadorE(char *ficheiro) {
    int contador;
    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {
        fread(&contador, sizeof (int), 1, fp);
        fclose(fp);
    }
    return contador;
}

int carregarEncomendas(Encomendas *encomendas, char *ficheiro) {
    int sucesso = 0;

    FILE *fp = fopen(ficheiro, "rb");
    if (fp != NULL) {

        fread(&encomendas->encomendas, sizeof (int), 1, fp);

        if (encomendas->contadorEncomenda > 0) {
            encomendas->encomendas = (Encomenda*) malloc(encomendas->contadorEncomenda * sizeof (Encomenda));
            fread(encomendas->encomendas, sizeof (Encomenda), encomendas->contadorEncomenda, fp);

            encomendas->tamanho = encomendas->contadorEncomenda;

            sucesso = 1;
        }
        fclose(fp);
    }

    if (!sucesso) {
        fp = fopen(ficheiro, "wb");
        if (fp != NULL) {
            encomendas->encomendas = (Encomenda*) malloc(ECOMENDAS_TAM_INICIAL * sizeof (Encomenda));
            encomendas->contadorEncomenda = 0;
            encomendas->tamanho = ECOMENDAS_TAM_INICIAL;
            fclose(fp);

            sucesso = 1;
        }
    }

    return sucesso;
}

void libertarEncomendas(Encomendas *encomendas) {
    free(encomendas->encomendas);
}

void atualizarContadorE(int contador, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

void inserirEncomendaE(Encomendas encomendas, char *ficheiro) {
    atualizarContadorE(encomendas.contadorEncomenda, ficheiro);

    FILE *fp = fopen(ficheiro, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&encomendas.encomendas[encomendas.contadorEncomenda - 1], sizeof (Encomenda), 1, fp);

    fclose(fp);
}

void atualizarEncomendaE(Encomendas encomendas, int indice, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "rb+");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fseek(fp, sizeof (int), SEEK_SET);

    fseek(fp, sizeof (Encomenda) * indice, SEEK_CUR);

    fwrite(&encomendas.encomendas[indice], sizeof (Encomenda), 1, fp);
}

void removerEncomendaE(Encomendas encomendas, char *ficheiro) {
    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&encomendas.contadorEncomenda, sizeof (int), 1, fp);
    fwrite(encomendas.encomendas, sizeof (Encomenda), encomendas.contadorEncomenda, fp);
}

int inserirEncomenda(Encomendas *encomendas) {
    int numero = obterInt2(OBTER_NUMERO_ENCOMENDA);
    if (procurarEncomenda(*encomendas, numero) == -1) {
        encomendas->encomendas[encomendas->contadorEncomenda].numero = numero;
        lerString(encomendas->encomendas[encomendas->contadorEncomenda].nome, MAX_NOME, MSG_OBTER_NOME_ENCOMENDAS);
        encomendas->encomendas[encomendas->contadorEncomenda].tamanhoDoArtigo =
                obterInt(MIN_TAMANHO, MAX_TAMANHO, OBTER_TAMANHO);
        return encomendas->contadorEncomenda++;
    }
    return -1;
}

void expandirEncomendas(Encomendas *encomendas) {
    Encomenda *temp = (Encomenda*) realloc(encomendas->encomendas, sizeof (Encomenda) * (encomendas->tamanho * 2));
    if (temp != NULL) {
        encomendas->tamanho *= 2;
        encomendas->encomendas = temp;
    }
}

void editarEncomenda(Encomenda *encomenda) {
    (*encomenda).numero = obterInt2(OBTER_NUMERO_ENCOMENDA);
    lerString((*encomenda).nome, MAX_NOME, MSG_OBTER_NOME_ENCOMENDAS);
    (*encomenda).tamanhoDoArtigo = obterInt(MIN_TAMANHO, MAX_TAMANHO, OBTER_TAMANHO);
}

void apagarEncomenda(Encomenda *encomenda) {
    encomenda->numero = 0;
    strcpy(encomenda->nome, "");
    encomenda->tamanhoDoArtigo = 0;
}

void inserirEncomendas(Encomendas *encomendas, char *ficheiro) {
    if (encomendas->contadorEncomenda == encomendas->tamanho) {
        expandirEncomendas(encomendas);
    }

    if (encomendas->contadorEncomenda < encomendas->tamanho) {
        if (inserirEncomenda(encomendas) == -1) {
            puts(ERRO_ENCOMENDA_NAO_EXISTE);
        } else {
            inserirEncomendaE(*encomendas, ficheiro);
        }
    } else {
        puts(ERRO_LISTA_CHEIA_ENCOMENDAS);
    }
}

    void procurarEncomendas(Encomendas encomendas) {
        int numero = procurarEncomenda(encomendas,
                obterInt2(OBTER_NUMERO_ENCOMENDA));
        if (numero != -1) {
            imprimirEncomendas(encomendas.encomendas[numero]);
        } else {
            puts(ERRO_ENCOMENDA_NAO_EXISTE);
        }
    }

    void listarEncomendas(Encomendas encomendas) {
        if (encomendas.contadorEncomenda > 0) {
            int i;
            for (i = 0; i < encomendas.contadorEncomenda; i++) {
                imprimirEncomendas(encomendas.encomendas[i]);
            }
        } else {
            puts(ERRO_LISTA_VAZIA_ENCOMENDAS);
        }
    }


    void editarEncomendas(Encomendas *encomendas, char *ficheiro) {
        int numero = procurarEncomenda(*encomendas,
                obterInt2(OBTER_NUMERO_ENCOMENDA));
        if (numero != -1) {
            editarEncomenda(&(*encomendas).encomendas[numero]);
            atualizarEncomendaE(*encomendas, numero, ficheiro);
        } else {
            puts(ERRO_ENCOMENDA_NAO_EXISTE);
        }
    }
    
    void removerEncomendas(Encomendas * encomendas, char *ficheiro) {
        int i, numero = procurarEncomenda(*encomendas, obterInt2(OBTER_NUMERO_ENCOMENDA));
        if (numero != -1) {
            for (i = numero; i < encomendas->contadorEncomenda - 1; i++) {
                encomendas->encomendas[i] = encomendas->encomendas[i + 1];
            }

            apagarEncomenda(&encomendas->encomendas[i]);
            encomendas->contadorEncomenda--;
            removerEncomendaE(*encomendas, ficheiro);
        } else {
            puts(ERRO_ENCOMENDA_NAO_EXISTE);
        }
    }  
    