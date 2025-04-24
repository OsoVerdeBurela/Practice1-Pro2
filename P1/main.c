/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 09 / 04 / 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void strToEnum(const char *original, tConsoleBrand *copy);

void enumToStr(tConsoleBrand original, char *copy);

bool new(tList *L, char *id, char *user, char *brand, char *price);


/* {Tipo: Generadora.
    Objetivo: Añadir una consola a la lista.
    Entrada:
        L: Lista donde vamos a eliminar la posicion.
        id: Id de la consola.
        user: Vendedor de la consola.
        brand: Marca de la consola.
        price: Precio por que que se va a vender inicialmente.
    Salida: La lista sin la posicion eliminada.
    Precondicion: El precio debe ser un valor positivo.
} */


void delete(tList *L, char *id);


/* {Tipo: Destructora.
    Objetivo: Eliminar el contenido la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a eliminar la posicion.
        id: Id de la consola que vamos a eliminar.
    Salida: La lista con la posicion eliminada.} */


void bid(tList *L, char *id, char *user, char *price);


/* {Tipo: Modificadora.
    Objetivo: Pujar en la consola que nos pasen.
    Entrada:
        L: Lista donde vamos a eliminar la posicion.
        id: id de la consola donde queremos pujar.
        user: Usuario que puja en la consola
        price: Precio por el que se puja
    Salida: La consola con la puja realizada.
} */


void stats(tList L);


/* {Tipo: Observadora.
    Objetivo: Mostrar los elementos de la lista, el numero de cada marca la suma de precios y la media.
    Entrada:
        L: Lista de donde vamos a obtener la informacion.
    Salida: Informacion de la lista.
    Precondicion: La posicion debe de ser valida.
    Postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.} */


void processCommand(tList *L, char *commandNumber, char command, char *param1, char *param2, char *param3,
                    char *param4) {
    bool error = false;

    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: console %s seller %s brand %s price %s\n", commandNumber, command, param1, param2,
                   param3, param4);
            error = new(L, param1, param2, param3, param4);
            error
                ? printf("+ Error: New not possible\n")
                : printf("* New: console %s seller %s brand %s price %s\n", param1, param2, param3, param4);
            break;
        case 'D':
            printf("%s %c: console %s\n", commandNumber, command, param1);
            delete(L, param1);
            break;
        case 'B':
            printf("%s %c: console %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(L, param1, param2, param3);
            break;
        case 'S':
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    tList listProducts;

    createEmptyList(&listProducts);

    f = fopen(filename, "r");

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(&listProducts, commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}


void strToEnum(const char *original, tConsoleBrand *copy) {
    if (strcmp(original, "nintendo") == 0) {
        *copy = nintendo;
    } else *copy = sega;
}


void enumToStr(tConsoleBrand original, char *copy) {
    if (original == nintendo) {
        strcpy(copy, "nintendo");
    } else {
        strcpy(copy, "sega");
    }
}


bool new(tList *L, char *id, char *user, char *brand, char *price) {
    bool error = false;
    tItemL item;

    if (!findItem(id,*L)) {
        error = true;
    } else {
        // Copia los parametros que se pasan y se inicializa al tItemL auxiliar
        strcpy(item.seller, user);
        strcpy(item.consoleId, id);
        item.consolePrice = atof(price);
        strToEnum(brand, &item.consoleBrand);
        item.bidCounter = 0;

        error=insertItem(item,LNULL, L);
    }

    return error;
}

void delete(tList *L, char *id) {
    tItemL d;
    char brand[10];
    tPosL p = findItem(id, *L); //Busca si la consola esta en la lista

    if (p != LNULL) { //Si la consola esta en la lista
        d = getItem(p, *L);
        enumToStr(d.consoleBrand, brand);
        //Elimina la consola
        deleteAtPosition(p, L);
        printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n", d.consoleId, d.seller, brand,
               d.consolePrice, d.bidCounter);
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

void bid(tList *L, char *id, char *user, char *price) {
    bool error;
    char brand[10];
    tPosL pAux = findItem(id, *L);
    tItemL dAux;

    if (pAux != LNULL) {
        dAux = getItem(pAux, *L);
        enumToStr(dAux.consoleBrand, brand);
        if (dAux.consolePrice < atof(price) && strcmp(user, dAux.seller) != 0) {
            // Comprueba si se encontro el objeto y el precio a pujar es mayor que su precio actual
            dAux.consolePrice = atof(price);
            dAux.bidCounter++;
            updateItem(dAux, pAux, L);
            error = false;
        } else error = true;
    } else error = true;

    error
        ? printf("+ Error: Bid not possible\n")
        : printf("* Bid: console %s seller %s brand %s price %.2f bids %d\n", dAux.consoleId, dAux.seller, brand,
                 dAux.consolePrice, dAux.bidCounter);
}

void stats(tList L) {
    tPosL i;
    int cntNin = 0, cntSeg = 0;
    float priceNin = 0, priceSeg = 0;

    if (isEmptyList(L)) {
        printf("+ Error: Stats not possible\n");
    } else {
        for (i = first(L); i != LNULL; i = next(i, L)) {
            //Recorre la lista para printear todos los elementos
            tItemL d = getItem(i, L);
            char brand[10];
            enumToStr(d.consoleBrand, brand);
            if (strcmp(brand, "nintendo") == 0) {
                cntNin++;
                priceNin += d.consolePrice;
            } else {
                cntSeg++;
                priceSeg += d.consolePrice;
            }

            printf("Console %s seller %s brand %s price %.2f bids %d\n", d.consoleId, d.seller, brand, d.consolePrice,
                   d.bidCounter);

        }
        printf("\n");

        printf("Brand     Consoles    Price  Average\nNintendo  %8d %8.2f %8.2f\nSega      %8d %8.2f %8.2f\n",
               cntNin, priceNin, cntNin == 0 ? priceNin : priceNin / cntNin, cntSeg, priceSeg,
               cntSeg == 0 ? priceSeg : priceSeg / cntSeg);
    }
}
