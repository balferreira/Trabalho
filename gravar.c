/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include "artigo.h"
#include "cliente.h"
#include "input.h"

void gravarDadosClientes (char *msg, char *filename,Cliente *cliente){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(fp,"%d %s" , cliente->numero , cliente->palavraPass);
}


void gravarDadosAdmin (char *filename,Cliente *cliente){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    
    fprintf(fp,"%s ",cliente->AdminpalavraPass);
}