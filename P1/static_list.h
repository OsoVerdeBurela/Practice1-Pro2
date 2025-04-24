/*
* TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Sergio López Fontenla LOGIN 1: sergio.lopez.fontenla@udc.es
 * AUTHOR 2: Jorge Neira Cociña LOGIN 2: jorge.neirac@udc.es
 * GROUP: 2.4
 * DATE: 09 / 04 / 2025
 */
#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <string.h>

/*  Write your code here...  */
#define MAX 25
#define LNULL -1

typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList *L);

/* {Tipo: Generadora.
    Objetivo: Crea una lista vacia y la inicializa.
    Entrada:
        L: Lista donde vamos a insertar.
    Salida: Una lista vacia.
    Poscondicion: La lista queda inicializada. } */

bool isEmptyList(tList L);

/* {Tipo: Observadora.
    Objetivo: Indicar si la lista esta vacia.
    Entrada:
        L: Lista que vamos a comprobar.
    Salida: Un booleano. } */

tPosL first(tList L);

/* {Tipo: Observadora.
    Objetivo: Conocer la primera posicion de la lista.
    Entrada:
        L: Lista donde vamos a mirar la posicion del primer elemento.
    Salida: La primera posicion util de la lista.
    Precondicion: La lista ha de estar inicializada} */

tPosL last(tList L);


/* {Tipo: Observadora.
    Objetivo: Conocer la ultima posicion de la lista.
    Entrada:
        L: Lista donde vamos a mirar la posicion del ultimo elemento.
    Salida: La ultima posicion util de la lista.
    Precondicion: La lista ha de estar inicializada} */


tPosL next(tPosL p, tList L);


/* {Tipo: Observadora.
    Objetivo: Conocer la siguiente posicion de la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a mirar la posicion del siguiente elemento.
        p: Posicion de la cual queremos conocer la siguiente posicion.
    Salida: La siguiente posicion util de la lista (en caso de ser la posterior a la ultima posicion devuelve LNULL).
    Precondicion: La posicion debe de ser valida.} */


tPosL previous(tPosL p, tList L);

/* {Tipo: Observadora.
    Objetivo: Conocer la anterior posicion de la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a mirar la posicion del anterior elemento.
        p: Posicion de la cual queremos conocer la anterior posicion.
    Salida: La anterior posicion util de la lista (en caso de ser la anterior a la primera posicion devuelve LNULL).
    Precondicion: La posicion debe de ser valida.} */

void updateItem(tItemL d, tPosL p, tList *L);

/* {Tipo: Modificadora.
    Objetivo: Modificar el contenido la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a insertar el objeto.
        p: Posicion donde queremos insertar el objeto.
        d: Objeto a insertar en la lista.
    Salida: Lista modificada con el objeto nuevo incorrporado en la posicion indicada.
    Precondicion: La posicion debe de ser valida.
    Postcondicion: La posicion de los objetos de la lista no se ve modificado.} */

bool insertItem(tItemL d, tPosL p, tList *L);

/* {Tipo: Generadora.
    Objetivo: Modificar el contenido la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a insertar el objeto.
        p: Posicion donde queremos insertar el objeto.
        d: Objeto a insertar en la lista.
    Salida: Un booleano indicando si pudo ser intertado o no el objeto.
    Precondicion: La posicion debe de ser valida.
    Postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.} */

void deleteAtPosition(tPosL p, tList *L);

/* {Tipo: Destructora.
    Objetivo: Eliminar el contenido la posicion que nos pasen en la lista.
    Entrada:
        L: Lista donde vamos a eliminar la posicion.
        p: Posicion que queremos eliminar.
    Salida: La lista sin la posicion eliminada.
    Precondicion: La posicion debe de ser valida.
    Postcondicion: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.} */

tItemL getItem(tPosL p, tList L);

/* {Tipo: Observadora.
    Objetivo: Obtener el objeto.
    Entrada:
        L: Lista de donde vamos a obtener el objeto.
        p: Posicion de donde queremos obtener el objeto.
    Salida: El objeto almacenado en la posicion indicada.
    Precondicion: La posicion debe de ser valida.} */

tPosL findItem(tConsoleId c, tList L);


/* {Tipo: Observadora.
    Objetivo: Encontrar la PRIMERA posicion donde se halla el objeto.
    Entrada:
        L: Lista donde vamos a buscar el objeto.
        c: Id del objeto a obtener la posicion en la lista.
    Salida: La posicion del PRIMER objeto con ese Id(En caso de no encontrarlo devuelve LNULL).} */


#endif
