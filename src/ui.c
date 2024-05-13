#include "ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int8_t mainMenu() {

    int err;
    int8_t op;

    printf("----- Wilker Trabalho de E.D -----\n");
    printf("1) consultar cidade\n");
    printf("2) cidades vizinhas\n");
    printf("0) ENCERRAR\n");
    printf("-------------------------------\n");
    printf("\nOpção: ");
    err = scanf("%hhd", &op);

    if (err == EOF || (op < UI_EXIT || op > UI_PROXIMITY))
        return UI_ERROR;

    return op;

}

int32_t consultation() {

    int err;
    int32_t codigo_ibge;

    printf("Informe o código IBGE da cidade que deseja buscar: ");
    err = scanf("%d", &codigo_ibge);

    if (err == EOF || codigo_ibge < 0)
        return UI_ERROR;

    return codigo_ibge;

}

int32_t questN(const char *nome, int max) {

    int err;
    int32_t n;

    printf("Informe quantas cidades mais proximas de (%s), deseja buscar: ", nome);
    err = scanf("%d", &n);

    if (err == EOF || (n < 0 || n > max))
        return UI_ERROR;

    return n;

}

void clear() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

}