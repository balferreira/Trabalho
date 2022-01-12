
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: hugo silva
 *
 * Created on 15 de dezembro de 2021, 09:32
 */

#include <stdio.h>
#include <stdlib.h>
#include "artigo.h"
#include "cliente.h"
#include "ecomendas.h"
#include "input.h"
#include "tamanhos.h"

#define PRECOS "Tabela_Custos"
#define ARTIGOS "artigos"
int main() {
    int opcao;
    Artigos artigos;
    Artigo artigo;
    Clientes clientes;
    Cliente cliente;
    Encomendas encomendas;
    Encomenda encomenda;
    Tamanhos tamanhos = {.contador = 14};
    Tamanho tamanho;
/*
do {
    if (carregarTamanhos(&tamanhos, PRECOS)) {
        printf("\nOpcão: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                break;
            case 1:
                inserirArtigos(&artigos, ARTIGOS);

                break;
            case 2:
                procurarArtigos(artigos);

                break;
            case 3:
                editarArtigos(&artigos, ARTIGOS);

                break;
            case 4:
                removerArtigos(&artigos, ARTIGOS);

                break;
            case 5:
                listarArtigos(artigos);

                break;
            default:
                printf("\nOpcão invalida!");
        }
       
    }
      } while (opcao != 0);
*/
/*
      if (carregarTamanhos(&tamanhos, PRECOS)){
             procurarTamanhos(tamanhos);
      }
         libertarArtigos(&artigos);
         
*/
    return 0;
}


